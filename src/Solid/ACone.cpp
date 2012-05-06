#include "ACone.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.1415926536
#endif

const double ACone::DEFAULT_RADIUS = 0.5;
const int ACone::DEFAULT_SLICES = 16;
const double ACone::DEFAULT_HEIGHT = 1.0;

ACone::ACone() :
    APrimitive(APrimitive::PT_CONE),
    radius(DEFAULT_RADIUS),
    slices(DEFAULT_SLICES),
    height(DEFAULT_HEIGHT)
{
    reset(radius, slices, height);
}

ACone::ACone(double radius, int slices, double height) :
    APrimitive(APrimitive::PT_CONE),
    radius(radius),
    slices(slices),
    height(height)
{
    reset(radius, slices, height);
}

ACone::~ACone()
{

}

double ACone::getRadius()
{
    return radius;
}

int ACone::getSlices()
{
    return slices;
}

double ACone::getHeight()
{
    return height;
}

void ACone::reset(double radius, int slices, double height)
{
    this->radius = radius;
    this->slices = slices;
    this->height = height;

    boundingBox = Vector3d(2 * radius, height, 2 * radius);

    vertexCount = slices + 2;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double step = 2 * M_PI / slices;
    for (int i = 0; i < slices; ++i) {
        double alpha = step * i;
        vertexArray[i] = Vector3d(cos(alpha) * radius, 0.0,
                                  sin(alpha) * radius);
    }
    vertexArray[slices] = Vector3d(0.0, height, 0.0);
    vertexArray[slices + 1] = Vector3d(0.0, 0.0, 0.0);

    faceCount = 2 * slices;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    for (int i = 0; i < slices - 1; ++i) {
        faceArray[i] = Vector3i(i, i + 1, slices);
        faceArray[slices + i] = Vector3i(i, slices + 1, i + 1);
    }
    faceArray[slices - 1] = Vector3i(0, slices, slices - 1);
    faceArray[slices * 2 - 1] = Vector3i(0, slices - 1, slices + 1);
}

QString ACone::toString(ASolid* solid) const
{
    QString str = toStringCommon(solid);
    if (radius - DEFAULT_RADIUS > EPSILON) {
        str += QString("radius=") + QString::number(radius) + QString("\n");
    }
    if (slices != DEFAULT_SLICES) {
        str += QString("slices=") + QString::number(slices) + QString("\n");
    }
    if (height - DEFAULT_HEIGHT > EPSILON) {
        str += QString("height=") + QString::number(height) + QString("\n");
    }
    str += QString("\n");
    return str;
}
