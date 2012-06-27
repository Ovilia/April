#include "TextUvGlWidget.h"

#include <QMouseEvent>
#include <QtOpenGL>

TextUvGlWidget::TextUvGlWidget(ViewManager *viewManager,
                               Texture *texture, QWidget *parent) :
    QLabel(parent),
    texture(texture),
    viewManager(viewManager),
    isMousePressed(false),
    selectedVertex(NOT_SELECTED),
    selectedFace(NOT_SELECTED),
    fillVisible(true)
{
    resize(500, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    textChanged();
}

TextUvGlWidget::~TextUvGlWidget()
{
}

Texture* TextUvGlWidget::getTexture() const
{
    return texture;
}

void TextUvGlWidget::textChanged()
{
    bool ok = false;
    if (texture->getFileName() != "") {
        QImage buf;
        if (buf.load(texture->getFileName())) {
            image = buf.scaled(this->size(), Qt::KeepAspectRatio);
            ok = true;
        }
    }
    if (!ok) {
        image = QImage(this->size(), QImage::Format_RGB32);
    }
}

void TextUvGlWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);

    if (texture) {
        if (fillVisible) {
            painter.setBrush(QBrush("#ccffcc"));
        } else {
            painter.setBrush(QBrush(Qt::transparent));
        }
        painter.setPen(Qt::red);
        int cnt = texture->getVertexCount();
        QPair<double, double>* vertexArr = texture->getVertexArray();

        QPoint* points = new QPoint[cnt];
        for (int i = 0; i < cnt; ++i) {
            points[i].setX(vertexArr[i].first * image.width());
            points[i].setY(vertexArr[i].second * image.height());
        }
        int faceCnt = cnt / 3;
        for (int i = 0; i < faceCnt; ++i) {
            painter.drawPolygon(points + 3 * i, 3);
        }
        delete[] points;

        if (selectedVertex != NOT_SELECTED) {
            int x = vertexArr[selectedVertex].first * image.width();
            int y = vertexArr[selectedVertex].second * image.height();
            int radius = 6;
            int left = x - radius;
            if (left < 0) {
                left = 0;
            }
            int right = 2 * radius;
            if (left + right > image.width()) {
                right = image.width() - left;
            }
            int top = y - radius;
            if (top < 0) {
                top = 0;
            }
            int bottom = 2 * radius;
            if (top + bottom > image.height()) {
                bottom = image.height() - top;
            }
            painter.setBrush(Qt::yellow);
            painter.setPen(Qt::yellow);
            painter.drawRect(left, top, right, bottom);
        }
    }

    setPixmap(QPixmap::fromImage(image));
}

QImage* TextUvGlWidget::getUvImage()
{
    QPainter painter(&image);
    painter.drawImage(0, 0, image);

    if (texture) {
        painter.setBrush(QBrush("#ccffcc"));
        painter.setPen(Qt::red);
        int cnt = texture->getVertexCount();
        QPair<double, double>* vertexArr = texture->getVertexArray();

        QPoint* points = new QPoint[cnt];
        for (int i = 0; i < cnt; ++i) {
            points[i].setX(vertexArr[i].first * image.width());
            points[i].setY(vertexArr[i].second * image.height());
        }
        int faceCnt = cnt / 3;
        for (int i = 0; i < faceCnt; ++i) {
            painter.drawPolygon(points + 3 * i, 3);
        }
        delete[] points;
    }
    if (image.isNull()) {
        return 0;
    } else {
        return &image;
    }
}

void TextUvGlWidget::mousePressEvent(QMouseEvent *ev)
{
    selectedVertex = getClickedVertex(ev->x(), ev->y());
    selectedFace = getClickedFace(ev->x(), ev->y());
    repaint();
}

void TextUvGlWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if (selectedVertex != NOT_SELECTED) {
        QPair<double, double>* vertexArr = texture->getVertexArray();
        vertexArr[selectedVertex].first = (double)(ev->x()) / image.width();
        vertexArr[selectedVertex].second = (double)(ev->y()) / image.height();
        repaint();
        viewManager->repaintAll();
    }
}

void TextUvGlWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    isMousePressed = false;
}

int TextUvGlWidget::getClickedVertex(int x, int y) const
{
    if (texture) {
        int cnt = texture->getVertexCount();
        QPair<double, double>* vertexArr = texture->getVertexArray();

        double tolerance = 0.02;
        double xPos = (double)x / image.width();
        double yPos = (double)y / image.height();
        for (int i = 0; i < cnt; ++i) {
            if (qAbs(vertexArr[i].first - xPos) < tolerance &&
                    qAbs(vertexArr[i].second - yPos) < tolerance) {
                return i;
            }
        }
        return NOT_SELECTED;
    } else {
        return NOT_SELECTED;
    }
}

int TextUvGlWidget::getClickedFace(int x, int y) const
{
    if (texture) {
        int cnt = texture->getVertexCount() / 3;
        QPair<double, double>* vertexArr = texture->getVertexArray();
        QPair<double, double> point = QPair<double, double>(x / image.width(),
                                                            y / image.height());

        for (int i = 0; i < cnt; ++i) {
            if (isInsideTriangle(vertexArr + 3 * i, point)) {
                return i;
            }
        }
        return NOT_SELECTED;
    } else {
        return NOT_SELECTED;
    }
}

bool TextUvGlWidget::isInsideTriangle(QPair<double, double>* triangle,
                                      QPair<double, double> point) const
{
    QPair<double, double> ma = QPair<double, double>(
                point.first - triangle[0].first,
                point.second - triangle[0].second);
    QPair<double, double> mb = QPair<double, double>(
                point.first - triangle[1].first,
                point.second - triangle[1].second);
    QPair<double, double> mc = QPair<double, double>(
                point.first - triangle[2].first,
                point.second - triangle[2].second);

    double ab = crossProduct(ma, mb);
    double bc = crossProduct(mb, mc);
    double ca = crossProduct(mc, ma);
    if ((ab > 0 && bc > 0 && ca > 0) ||
            (ab < 0 && bc < 0 && ca < 0)) {
        return true;
    } else {
        return false;
    }
}

double TextUvGlWidget::crossProduct(
        QPair<double, double> vec1, QPair<double, double> vec2) const
{
    return vec1.first * vec2.second - vec1.second * vec2.first;
}

void TextUvGlWidget::setFillVisible(bool visible)
{
    fillVisible = visible;
    repaint();
}
