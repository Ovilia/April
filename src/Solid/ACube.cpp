#include <QtOpenGL>

#include "ACube.h"

ACube::ACube(double width, double depth, double height) :
    APrimitive(),
    width(width),
    depth(depth),
    height(height)
{
    boundingBox = Vector3d(width, height, depth);
}

ACube::~ACube()
{

}

void ACube::drawWire()
{

}

void ACube::drawSolid()
{
    drawBefore();

    glBegin(GL_LINES);
    glVertex3d(0.0, 0.2, 0.8);
    glVertex3d(0.0, -0.2, -0.8);

    drawAfter();
}

void ACube::setOctree()
{

}
