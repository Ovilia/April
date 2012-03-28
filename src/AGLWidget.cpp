#include <QtOpenGL/qgl.h>

#include "AGLWidget.h"

AGLWidget::AGLWidget(ModelManager* modelManager, QWidget *parent) :
    QGLWidget(parent),
    modelManager(modelManager)
{
    setMinimumSize(100, 100);
}

AGLWidget::~AGLWidget()
{

}

void AGLWidget::initializeGL()
{
    glClearColor(0.0, 1.0, 0.0, 0.0 );
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 3.0);
}

void AGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 3.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(0, 0, 0.5, 0, 0, 0, 0, 1, 0);

    glColor3d(1.0,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3d(-0.2, 0.2, -0.2);
    glVertex3d(0.2, 0.2, -0.2);
    glVertex3d(0.2, -0.2, -0.2);
    glEnd();
}

void AGLWidget::resizeGL(int width, int height)
{
    // view center part of the window
    if (width <= height) {
        int top = (height - width) / 2;
        glViewport(0, top, width, width);
    } else {
        int left = (width - height) / 2;
        glViewport(left, 0, height, height);
    }
}
