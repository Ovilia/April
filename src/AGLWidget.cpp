#include <QKeyEvent>
#include <QMouseEvent>
#include <QtOpenGL>

#include "AGLWidget.h"

AGLWidget::AGLWidget(ModelManager* modelManager, QWidget *parent) :
    QGLWidget(parent),
    modelManager(modelManager),
    viewMode(StateEnum::VM_NONE),

    widthHeightRatio(1.0),

    clearColor(0.9, 0.9, 0.9),

    zoomInRatio(0.9),
    zoomOutRatio(1.2),

    orthoLeft(-1.2),
    orthoRight(1.2),
    orthoBottom(-0.84),
    orthoTop(1.56),
    orthoNear(-100.0),
    orthoFar(100.0),
    orthoXRotate(45.0),
    orthoYRotate(-45.0),
    orthoZRotate(0.0),
    rotateRatio(10.0),

    arcBall(this->width(), this->height()),

    viewPortX(0),
    viewPortY(0),

    isMousePressed(false),
    mousePressX(0),
    mousePressY(0),
    mouseLastX(0),
    mouseLastY(0),

    mainPlainSize(1.0),
    mainPlainColor(0.7, 0.7, 0.7),
    axisLength(0.8),
    arrowLength(0.05)
{
    setMinimumSize(100, 100);
    setMouseTracking(true);
}

AGLWidget::~AGLWidget()
{

}

void AGLWidget::setViewMode(StateEnum::ViewMode mode)
{
    viewMode = mode;
}

StateEnum::ViewMode AGLWidget::getViewMode()
{
    return viewMode;
}

void AGLWidget::zoomIn()
{
    orthoLeft *= zoomInRatio;
    orthoRight *= zoomInRatio;
    orthoBottom *= zoomInRatio;
    orthoTop *= zoomInRatio;
    repaint();
}

void AGLWidget::zoomOut()
{
    orthoLeft *= zoomOutRatio;
    orthoRight *= zoomOutRatio;
    orthoBottom *= zoomOutRatio;
    orthoTop *= zoomOutRatio;
    repaint();
}

void AGLWidget::rotateX()
{
    orthoXRotate += rotateRatio;
    if (orthoXRotate > 360.0) {
        orthoXRotate -= 360.0;
    }
    repaint();
}

void AGLWidget::rotateY()
{
    orthoYRotate += rotateRatio;
    if (orthoYRotate > 360.0) {
        orthoYRotate -= 360.0;
    }
    repaint();
}

void AGLWidget::rotateZ()
{
    orthoZRotate += rotateRatio;
    if (orthoZRotate > 360.0) {
        orthoZRotate -= 360.0;
    }
    repaint();
}

void AGLWidget::initializeGL()
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);
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

    glPushMatrix();
    glLoadIdentity();

    // rotate ortho view
    glRotated(orthoXRotate, 1.0, 0.0, 0.0);
    glRotated(orthoYRotate, 0.0, 1.0, 0.0);
    glRotated(orthoZRotate, 0.0, 0.0, 1.0);

    // rotate by mouse dragging
    arcBall.doRotate();

    if (modelManager->getLightChanged()) {
        setLighting();
    }
    if (modelManager->allLightOff()) {
        glDisable(GL_LIGHTING);
    } else {
        glEnable(GL_LIGHTING);
    }

    if (modelManager->getIsDrawSolid()) {
        modelManager->drawSolid();
    }
    if (modelManager->getIsDrawWire()) {
        modelManager->drawWire();
    }

    glDisable(GL_LIGHTING);
    drawMainPlain();
    drawAxis();

    // pop rotate ortho view
    glPopMatrix();
}

void AGLWidget::drawMainPlain()
{
    // plain
    glColor3d(mainPlainColor.x, mainPlainColor.y, mainPlainColor.z);
    glBegin(GL_QUADS);
    glVertex3d(-mainPlainSize, 0, -mainPlainSize);
    glVertex3d(mainPlainSize, 0, -mainPlainSize);
    glVertex3d(mainPlainSize, 0, mainPlainSize);
    glVertex3d(-mainPlainSize, 0, mainPlainSize);
    glEnd();
}

void AGLWidget::drawAxis()
{
    // disable depth test to always draw axis
    glDisable(GL_DEPTH_TEST);

    // x axis
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(axisLength, 0.0, 0.0);
    glVertex3d(axisLength, 0.0, 0.0);
    glVertex3d(axisLength - arrowLength, 0.0, -arrowLength);
    glVertex3d(axisLength, 0.0, 0.0);
    glVertex3d(axisLength - arrowLength, 0.0, arrowLength);
    glEnd();

    // y axis
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, axisLength, 0.0);
    glVertex3d(0.0, axisLength, 0.0);
    glVertex3d(0.0, axisLength - arrowLength, -arrowLength);
    glVertex3d(0.0, axisLength, 0.0);
    glVertex3d(0.0, axisLength - arrowLength, arrowLength);
    glEnd();

    // z axis
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, axisLength);
    glVertex3d(0.0, 0.0, axisLength);
    glVertex3d(-arrowLength, 0.0, axisLength - arrowLength);
    glVertex3d(0.0, 0.0, axisLength);
    glVertex3d(arrowLength, 0.0, axisLength - arrowLength);
    glEnd();

    glEnable(GL_DEPTH_TEST);
}

void AGLWidget::resizeGL(int width, int height)
{
    arcBall.resize(width, height);

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
        double orthoHeight = (orthoRight - orthoLeft) / widthHeightRatio;
        orthoBottom = (orthoBottom + orthoTop - orthoHeight) / 2.0;
        orthoTop = orthoBottom + orthoHeight;
    } else {
        double orthoWidth = (orthoTop - orthoBottom) * widthHeightRatio;
        orthoLeft = (orthoLeft + orthoRight - orthoWidth) / 2.0;
        orthoRight = orthoLeft + orthoWidth;
    }
}

void AGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMousePressed)
    {
        switch (viewMode) {
        case StateEnum::VM_MOVE:
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

        case StateEnum::VM_ROTATE:
            arcBall.mouseMove(event->x(), event->y());

        default:
            break;
        }

        // set current position to be last position
        mouseLastX = event->x();
        mouseLastY = event->y();
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
    case StateEnum::VM_MOVE:
        setCursor(Qt::SizeAllCursor);
        break;

    case StateEnum::VM_ROTATE:
        setCursor(Qt::CrossCursor);
        arcBall.mousePress(mousePressX, mousePressY);
        break;

    default:
        break;
    }
}

void AGLWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;

    switch (viewMode) {
    case StateEnum::VM_ROTATE:
        arcBall.mouseRelease();
        break;

    default:
        break;
    }

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

void AGLWidget::setLighting()
{
    for (int i = 0; i < ModelManager::MAX_LIGHT_COUNT; ++i) {
        Lighting* light = modelManager->getLight(i);
        GLenum id = GL_LIGHT0 + i;
        if (light && light->getIsOn()) {
            glEnable(id);
            glLightfv(id, GL_POSITION, light->getPosition());
            glLightfv(id, GL_DIFFUSE, light->getDiffuse());
            glLightfv(id, GL_SPECULAR, light->getSpecular());
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light->getAmbient());

            glLightf(id, GL_SPOT_CUTOFF, light->getCutOff());
            glLightfv(id, GL_SPOT_DIRECTION, light->getDirection());
        } else {
            glDisable(id);
        }
    }
}
