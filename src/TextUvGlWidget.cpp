#include "TextUvGlWidget.h"

#include <QMouseEvent>
#include <QtOpenGL>

TextUvGlWidget::TextUvGlWidget(Texture* texture, QWidget *parent) :
    QLabel(parent),
    texture(texture)
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
    //painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

    painter.setPen(Qt::red);
    //painter.setBrush(QBrush("#DDAA33"));

    if (texture) {
        int cnt = texture->getVertexCount() / 3;
        QPair<double, double>* vertexArr = texture->getVertexArray();
        for (int i = 0; i < cnt; ++i) {
            int aX = vertexArr[3 * i].first * image.width();
            int aY = vertexArr[3 * i].second * image.height();
            int bX = vertexArr[3 * i + 1].first * image.width();
            int bY = vertexArr[3 * i + 1].second * image.height();
            int cX = vertexArr[3 * i + 2].first * image.width();
            int cY = vertexArr[3 * i + 2].second * image.height();
            painter.drawLine(aX, aY, bX, bY);
            painter.drawLine(bX, bY, cX, cY);
            painter.drawLine(cX, cY, aX, aY);
        }
    }

    setPixmap(QPixmap::fromImage(image));
}
