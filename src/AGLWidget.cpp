#include <QKeyEvent>
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
    orthoXRotate(0.0),
    orthoYRotate(0.0),
    orthoZRotate(0.0),
    rotateRatio(5),

    viewPortX(0),
    viewPortY(0),

    isMousePressed(false),
    mousePressX(0),
    mousePressY(0),
    mouseLastX(0),
    mouseLastY(0),

    mainPlainSize(0.5),
    mainGridCount(10),
    mainPlainColor(0.3, 0.3, 0.3),
    mainGridColor(0.9, 0.9, 0.9)
{
    setMinimumSize(100, 100);
    resize(600, 800);
    setMouseTracking(true);
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

void AGLWidget::rotateX()
{
    orthoXRotate += rotateRatio;
    if (orthoXRotate > 360.0) {
        orthoXRotate -= 360.0;
    }
    paintGL();
}

void AGLWidget::rotateY()
{
    orthoYRotate += rotateRatio;
    if (orthoYRotate > 360.0) {
        orthoYRotate -= 360.0;
    }
    paintGL();
}

void AGLWidget::rotateZ()
{
    orthoZRotate += rotateRatio;
    if (orthoZRotate > 360.0) {
        orthoZRotate -= 360.0;
    }
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
    glOrtho(orthoLeft, orthoRight,
            orthoBottom, orthoTop,
            orthoNear, orthoFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // rotate ortho view
    glPushMatrix();
    if (orthoXRotate) {
        glRotated(orthoXRotate, 1.0, 0.0, 0.0);
        glRotated(orthoYRotate, 0.0, 1.0, 0.0);
        glRotated(orthoZRotate, 0.0, 0.0, 1.0);
    }

    drawMainPlain();

    glColor3d(0.0, 0.0, 0.3);
    glBegin(GL_LINES);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, -1.0, 0.0);
    glEnd();

    // pop rotate ortho view
    glPopMatrix();

    repaint();
}

void AGLWidget::drawMainPlain()
{
    // plain
    glColor3d(mainPlainColor.getX(), mainPlainColor.getY(),
              mainPlainColor.getZ());
    glBegin(GL_QUADS);
    glVertex3d(-mainPlainSize, 0, -mainPlainSize);
    glVertex3d(mainPlainSize, 0, -mainPlainSize);
    glVertex3d(mainPlainSize, 0, mainPlainSize);
    glVertex3d(-mainPlainSize, 0, mainPlainSize);
    glEnd();

    // grid
    glColor4d(mainGridColor.getX(), mainGridColor.getY(),
              mainGridColor.getZ(), 0.5);
    glBegin(GL_LINES);
    double sum = 0;
    for (int i = 0; i <= mainGridCount; ++i) {
        glVertex3d(-mainPlainSize, 0, -mainPlainSize + sum);
        glVertex3d(mainPlainSize, 0, -mainPlainSize + sum);
        glVertex3d(-mainPlainSize + sum, 0, -mainPlainSize);
        glVertex3d(-mainPlainSize + sum, 0, mainPlainSize);
        sum += mainPlainSize / mainGridCount;
    }
    glEnd();
}

void AGLWidget::resizeGL(int width, int height)
{
    // update widthHeightRatio
    if (height != 0 && width != 0) {
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
        orthoTop = orthoBottom + (orthoRight - orthoLeft) / widthHeightRatio;
    } else {
        orthoRight = orthoLeft + (orthoTop - orthoBottom) * widthHeightRatio;
    }
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

void AGLWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;
    // set mouse cursor
    setCursor(Qt::ArrowCursor);
}

void AGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_X:
        rotateX();
        break;

    case Qt::Key_Y:
        rotateY();
        break;

    case Qt::Key_Z:
        rotateZ();
        break;

    default:
        break;
    }
}

void AGLWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    rotateX();
}
