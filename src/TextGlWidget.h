#ifndef TextGlWidget_H
#define TextGlWidget_H

#include <QtOpenGL/qgl.h>

#include "ArcBall.h"
#include "Solid/APrimitive.h"

class TextGlWidget : public QGLWidget
{
public:
    TextGlWidget(APrimitive::PrimitiveType pType, QWidget *parent);
    ~TextGlWidget();

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    double orthoLeft;
    double orthoRight;
    double orthoBottom;
    double orthoTop;

    // rotate by mouse dragging
    ArcBall arcBall;
    bool isMousePressed;

    APrimitive* primitive;
};

#endif // TextGlWidget_H
