#include <QMouseEvent>
#include <QtOpenGL/qgl.h>

#include "AGLWidget.h"

AGLWidget::AGLWidget(ModelManager* modelManager, QWidget *parent) :
    QGLWidget(parent),
    modelManager(modelManager),
    viewMode(VM_NONE),

    widthHeightRatio(1.0),

    clearColor(0.7, 0.7, 0.7),

    //scaleOnceRatio(5.0),
    zoomInRatio(0.9),
    zoomOutRatio(1.5),

    orthoLeft(-1.0),
    orthoRight(1.0),
    orthoBottom(-1.0),
    orthoTop(1.0),
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
    resize(600, 800);
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

void AGLWidget::zoomIn()
{
    orthoLeft *= zoomInRatio;
    orthoRight *= zoomInRatio;
    orthoBottom *= zoomInRatio;
    orthoTop *= zoomInRatio;
    paintGL();
}

void AGLWidget::zoomOut()
{
    orthoLeft *= zoomOutRatio;
    orthoRight *= zoomOutRatio;
    orthoBottom *= zoomOutRatio;
    orthoTop *= zoomOutRatio;
    paintGL();
}

void AGLWidget::initializeGL()
{
    glClearColor(clearColor.getX(), clearColor.getY(), clearColor.getZ(), 1.0);
    glEnable(GL_DEPTH_TEST);
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

    glColor3d(0.0, 0.0, 0.3);
    glBegin(GL_LINES);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, -1.0, 0.0);
    glEnd();

    repaint();
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
        switch (viewMode) {
        case VM_MOVE:
        {
            // scene moves with cursor
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

//        case VM_ZOOM_IN:
//        {
//            // currently zoom in with mouse dragging is not implemented
//            break;
//        }

        default:
            break;
        }

        // set current position to be last position
        mouseLastX = event->x();
        mouseLastY = event->y();
        paintGL();
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
