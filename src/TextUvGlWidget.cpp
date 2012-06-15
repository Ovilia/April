#include "TextUvGlWidget.h"

#include <QMouseEvent>
#include <QtOpenGL>

#include <QDebug>

TextUvGlWidget::TextUvGlWidget(Texture* texture, QWidget *parent) :
    QGLWidget(parent),

    isMousePressed(false),

    texture(texture)
{
}

TextUvGlWidget::~TextUvGlWidget()
{
}

void TextUvGlWidget::initializeGL()
{
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void TextUvGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (texture) {
        int cnt = texture->getVertexCount() / 3;
        QPair<double, double>* vertexArr = texture->getVertexArray();
        for (int i = 0; i < cnt; ++i) {
            qDebug()<<vertexArr[3 * i].first<<vertexArr[3 * i].second;
            qDebug()<<vertexArr[3 * i + 1].first<<vertexArr[3 * i + 1].second;
            qDebug()<<vertexArr[3 * i + 2].first<<vertexArr[3 * i + 2].second;
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
    if (width > height) {
        glViewport((width - height) / 2.0, 0.0, height, height);
    } else {
        glViewport(0.0, (height - width) / 2.0, width, width);
    }
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
