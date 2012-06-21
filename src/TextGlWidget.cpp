#include "TextGlWidget.h"

#include <QMouseEvent>
#include <QtOpenGL>

#include "Solid/ACone.h"
#include "Solid/ACube.h"
#include "Solid/ACylinder.h"
#include "Solid/APrism.h"
#include "Solid/APyramid.h"
#include "Solid/ASphere.h"

TextGlWidget::TextGlWidget(APrimitive* primitive, QWidget *parent) :
    QGLWidget(parent),

    orthoLeft(-1.5),
    orthoRight(1.5),
    orthoBottom(-0.5),
    orthoTop(1.75),

    arcBall(this->width(), this->height()),
    isMousePressed(false)
{
    switch (primitive->getType()) {
    case APrimitive::PT_CONE:
    {
        ACone* cone = (ACone*)primitive;
        this->primitive = new ACone(cone->getRadius(), cone->getSlices(),
                                    cone->getHeight());
    }
        break;

    case APrimitive::PT_CUBE:
    {
        ACube* cube = (ACube*)primitive;
        this->primitive = new ACube(cube->getWidth(), cube->getDepth(),
                                    cube->getHeight());
    }
        break;

    case APrimitive::PT_CYLINDER:
    {
        ACylinder* cyl = (ACylinder*)primitive;
        this->primitive = new ACylinder(cyl->getRadius(), cyl->getSlices(),
                                        cyl->getHeight());
    }
        break;

    case APrimitive::PT_PRISM:
    {
        APrism* prism = (APrism*)primitive;
        this->primitive = new APrism(prism->getLength(),
                                     prism->getSideLength());
    }
        break;

    case APrimitive::PT_PYRAMID:
    {
        APyramid* pym = (APyramid*)primitive;
        this->primitive = new APyramid(pym->getSideLength());
    }
        break;

    case APrimitive::PT_SPHERE:
    {
        ASphere* sph = (ASphere*)primitive;
        this->primitive = new ASphere(sph->getRadius(), sph->getSlices(),
                                      sph->getStacks());
    }
        break;

    default:
        break;
    }

    // set ortho para by primitive bounding box
    if (primitive) {
        orthoLeft = primitive->getBoundingBoxMin().x - 0.25;
        orthoRight = primitive->getBoundingBoxMax().x + 0.25;
        orthoBottom = primitive->getBoundingBoxMin().y - 0.25;
        orthoTop = primitive->getBoundingBoxMax().y + 0.25;
    }
}

TextGlWidget::~TextGlWidget()
{
    if (primitive) {
        delete primitive;
    }
}

void TextGlWidget::initializeGL()
{
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void TextGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(orthoLeft, orthoRight,
            orthoBottom, orthoTop,
            -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // rotate by mouse dragging
    arcBall.doRotate();

    if (primitive) {
        primitive->drawSolid();
    }
}

void TextGlWidget::resizeGL(int width, int height)
{
    arcBall.resize(width, height);

    double widthHeightRatio;
    if (height != 0 && width != 0) {
        widthHeightRatio = (double)width / height;
    } else {
        widthHeightRatio = 1.0;
    }

    if (width <= height) {
        double orthoHeight = (orthoRight - orthoLeft) / widthHeightRatio;
        orthoBottom = (orthoBottom + orthoTop - orthoHeight) / 2.0;
        orthoTop = orthoBottom + orthoHeight;
    } else {
        double orthoWidth = (orthoTop - orthoBottom) * widthHeightRatio;
        orthoLeft = (orthoLeft + orthoRight - orthoWidth) / 2.0;
        orthoRight = orthoLeft + orthoWidth;
    }

    glViewport(0.0, 0.0, width, height);
}

void TextGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMousePressed)
    {
        arcBall.mouseMove(event->x(), event->y());
        repaint();
    }
}

void TextGlWidget::mousePressEvent(QMouseEvent *event)
{
    isMousePressed = true;
    setCursor(Qt::CrossCursor);
    arcBall.mousePress(event->x(), event->y());
}

void TextGlWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;
    arcBall.mouseRelease();
    setCursor(Qt::ArrowCursor);
}

APrimitive* TextGlWidget::getPrimitive() const
{
    return primitive;
}
