#include <QMouseEvent>
#include <QtOpenGL/qgl.h>
#include <Glut>

#include "AGLWidget.h"

AGLWidget::AGLWidget(ModelManager* modelManager, QWidget *parent) :
    QGLWidget(parent),
    modelManager(modelManager),
    viewMode(VM_NONE),

    widthHeightRatio(1.0),

    lookEye(0.0, 0.0, 0.5),
    lookCenter(0.0, 0.0, 0.0),
    lookUp(0.0, 1.0, 0.0),

    orthoLeft(-1.0),
    orthoRight(1.0),
    orthoTop(1.0),
    orthoBottom(-1.0),
    orthoNear(0.0),
    orthoFar(100.0),

    viewPortX(0),
    viewPortY(0),

    isMousePressed(false),
    mousePressX(0),
    mousePressY(0),
    mouseLastX(0),
    mouseLastY(0)
{
    setMinimumSize(100, 100);
}

AGLWidget::~AGLWidget()
{

}

void AGLWidget::setViewMode(ViewMode mode)
{
    viewMode = mode;
}

AGLWidget::ViewMode AGLWidget::getViewMode()
{
    return viewMode;
}

void AGLWidget::initializeGL()
{
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    gluLookAt(lookEye.getX(), lookEye.getY(), lookEye.getZ(),
              lookCenter.getX(), lookCenter.getY(), lookCenter.getZ(),
              lookUp.getX(), lookUp.getY(), lookUp.getZ());
}

void AGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width() <= height()) {
        glOrtho(orthoLeft, orthoRight,
                orthoBottom / widthHeightRatio, orthoTop / widthHeightRatio,
                orthoNear, orthoFar);
    } else {
        glOrtho(orthoLeft * widthHeightRatio, orthoRight * widthHeightRatio,
                orthoBottom, orthoTop,
                orthoNear, orthoFar);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutSolidSphere(0.5, 20, 16);
    glFlush();
}

void AGLWidget::resizeGL(int width, int height)
{
    // update widthHeightRatio
    if (height != 0) {
        widthHeightRatio = (double)width / height;
    } else {
        widthHeightRatio = 1.0;
    }

    // set view
    glViewport(viewPortX, viewPortY, width, height);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height) {
        glOrtho(orthoLeft, orthoRight,
                orthoBottom / widthHeightRatio, orthoTop / widthHeightRatio,
                orthoNear, orthoFar);
    } else {
        glOrtho(orthoLeft * widthHeightRatio, orthoRight * widthHeightRatio,
                orthoBottom, orthoTop,
                orthoNear, orthoFar);
    }
}

void AGLWidget::enterEvent(QEvent *)
{
    setMouseTracking(true);
}

void AGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMousePressed)
    {
        // move
        switch (viewMode) {
        case VM_MOVE:
        {
            double moveRight = (event->x() - mouseLastX) *
                    (orthoRight - orthoLeft) / width();
            orthoLeft -= moveRight;
            orthoRight -= moveRight;

            double moveUp = (event->y() - mouseLastY) *
                    (orthoTop - orthoBottom) / height();
            orthoTop += moveUp;
            orthoBottom += moveUp;
            break;
        }

        default:
            break;
        }

        // set current position to be last position
        mouseLastX = event->x();
        mouseLastY = event->y();
        paintGL();
        repaint();
    }
}

void AGLWidget::mousePressEvent(QMouseEvent *event)
{
    isMousePressed = true;
    mousePressX = event->x();
    mousePressY = event->y();
    mouseLastX = mousePressX;
    mouseLastY = mousePressY;

    // set mouse cursor
    switch (viewMode) {
    case VM_MOVE:
        setCursor(Qt::SizeAllCursor);
        break;
    default:
        break;
    }
}

void AGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed = false;
    // set mouse cursor
    setCursor(Qt::ArrowCursor);
}