#ifndef MATGLWIDGET_H
#define MATGLWIDGET_H

#include <QtOpenGL/qgl.h>

#include "ArcBall.h"
#include "Solid/APrimitive.h"

class MatGlWidget : public QGLWidget
{
public:
    MatGlWidget(APrimitive::PrimitiveType pType, QWidget *parent);
    ~MatGlWidget();

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

#endif // MATGLWIDGET_H
