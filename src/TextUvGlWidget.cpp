#include "TextUvGlWidget.h"

#include <QMouseEvent>
#include <QtOpenGL>

TextUvGlWidget::TextUvGlWidget(Texture* texture, QWidget *parent) :
    QGLWidget(parent),

    isMousePressed(false),

    texture(texture),

    image(0),
    imageTextId(0)
{
}

TextUvGlWidget::~TextUvGlWidget()
{
}

void TextUvGlWidget::initializeGL()
{
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glViewport(0.0, 0.0, this->width(), this->height());

    glEnable(GL_TEXTURE_2D);
}

void TextUvGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (image) {
        glEnable(GL_BLEND);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, imageTextId);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 1.0, 0.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.0, 1.0, 0.0);
        glEnd();
    } else
    if (texture) {
        int cnt = texture->getVertexCount() / 3;
        QPair<double, double>* vertexArr = texture->getVertexArray();
        for (int i = 0; i < cnt; ++i) {
            // triangers
            glColor3d(0.4, 0.1, 0.1);
            glBegin(GL_TRIANGLES);
            glVertex3d(vertexArr[3 * i].first, vertexArr[3 * i].second, 0.0);
            glVertex3d(vertexArr[3 * i + 1].first,
                       vertexArr[3 * i + 1].second, 0.0);
            glVertex3d(vertexArr[3 * i + 2].first,
                       vertexArr[3 * i + 2].second, 0.0);
            glEnd();

            // borders of triangles
            glColor3d(1.0, 1.0, 0.0);
            glBegin(GL_LINE_LOOP);
            glVertex3d(vertexArr[3 * i].first,
                       vertexArr[3 * i].second, 0.0);
            glVertex3d(vertexArr[3 * i + 1].first,
                       vertexArr[3 * i + 1].second, 0.0);
            glVertex3d(vertexArr[3 * i + 2].first,
                       vertexArr[3 * i + 2].second, 0.0);
            glEnd();
        }
    }
}

void TextUvGlWidget::resizeGL(int width, int height)
{
    glViewport(0.0, 0.0, width, height);
}

void TextUvGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMousePressed)
    {
        repaint();
    }
}

void TextUvGlWidget::mousePressEvent(QMouseEvent *event)
{
    isMousePressed = true;
    setCursor(Qt::CrossCursor);
}

void TextUvGlWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;
    setCursor(Qt::ArrowCursor);
}

Texture* TextUvGlWidget::getTexture()
{
    return texture;
}

void TextUvGlWidget::setImage(QImage *image)
{
    this->image = image;

    glGenTextures(1, &imageTextId);
    glBindTexture(GL_TEXTURE_2D, imageTextId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 image->width(), image->height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image->bits());
}
