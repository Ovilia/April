#ifndef TextUvGlWidget_H
#define TextUvGlWidget_H

#include <QImage>
#include <QtOpenGL/qgl.h>

#include "Texture.h"

class TextUvGlWidget : public QGLWidget
{
public:
    TextUvGlWidget(Texture* texture, QWidget *parent = 0);
    ~TextUvGlWidget();

    Texture* getTexture();

    void setImage(QImage* image);

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool isMousePressed;

    Texture* texture;

    QImage* image;
    GLuint imageTextId;
};

#endif // TextUvGlWidget_H
