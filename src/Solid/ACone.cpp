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

    boundingBoxMin = Vector3d(-radius, 0, -radius);
    boundingBoxMax = Vector3d(radius, height, radius);

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

    // init parameters
    if (defaultTextVertexPos) {
        delete []defaultTextVertexPos;
        defaultTextVertexPos = 0;
    }
    if (defaultPmtId) {
        delete []defaultPmtId;
        defaultPmtId = 0;
    }
    if (defaultTextFaceVertex) {
        delete []defaultTextFaceVertex;
        defaultTextFaceVertex = 0;
    }

    // texture
    texture = new Texture((APrimitive*)this);
}

QString ACone::toString() const
{
    return "radius=" + QString::number(radius) + "\nslices=" +
            QString::number(slices) + "\nheight=" + QString::number(height)
            + "\n";
}

const QPair<double, double>* ACone::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    for (int i = 0; i < slices; ++i) {
        // side faces
        int index = 3 * i;
        defaultTextVertexPos[index] = QPair<double, double>(
                    0.5 / (slices + 0.5) + i / (slices + 0.5), 0.0);
        defaultTextVertexPos[++index] = QPair<double, double>(
                    i / (slices + 0.5), 1.0);
        defaultTextVertexPos[++index] = QPair<double, double>(
                    (i + 1) / (slices + 0.5), 1.0);
        // bottom faces
        index = 3 * (i + slices);
        defaultTextVertexPos[index] = QPair<double, double>(
                    (i + 1) / (slices + 0.5), 1.0);
        defaultTextVertexPos[++index] = QPair<double, double>(
                    0.5 / (slices + 0.5) + i / (slices + 0.5), 0.0);
        defaultTextVertexPos[++index] = QPair<double, double>(
                    0.5 / (slices + 0.5) + (i + 1) / (slices + 0.5), 0.0);
    }
    return defaultTextVertexPos;
}

const int* ACone::getDefaultPmtId()
{
    if (defaultPmtId) {
        return defaultPmtId;
    }
    int cnt = getTextVertexCount();
    defaultPmtId = new int[cnt];
    for (int i = 0; i < slices - 1; ++i) {
        // side faces
        int index = 3 * i;
        defaultPmtId[index] = slices;
        defaultPmtId[++index] = i;
        defaultPmtId[++index] = i + 1;
        // bottom faces
        index = 3 * (i + slices);
        defaultPmtId[index] = slices + 1;
        defaultPmtId[++index] = i;
        defaultPmtId[++index] = i + 1;
    }
    // last slice
    int index = 3 * slices - 1;
    defaultPmtId[index] = slices;
    defaultPmtId[++index] = slices - 1;
    defaultPmtId[++index] = 0;
    index = 6 * slices - 1;
    defaultPmtId[index] = slices + 1;
    defaultPmtId[++index] = slices - 1;
    defaultPmtId[++index] = 0;
    return defaultPmtId;
}
