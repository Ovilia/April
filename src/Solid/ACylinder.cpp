#include "ACylinder.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.1415926536
#endif

const double ACylinder::DEFAULT_RADIUS = 0.5;
const int ACylinder::DEFAULT_SLICES = 16;
const double ACylinder::DEFAULT_HEIGHT = 1.0;

ACylinder::ACylinder() :
    APrimitive(APrimitive::PT_CYLINDER),
    radius(DEFAULT_RADIUS),
    slices(DEFAULT_SLICES),
    height(DEFAULT_HEIGHT)
{
    reset(radius, slices, height);
}

ACylinder::ACylinder(double radius, int slices, double height) :
    APrimitive(APrimitive::PT_CYLINDER),
    radius(radius),
    slices(slices),
    height(height)
{
    reset(radius, slices, height);
}

ACylinder::~ACylinder()
{

}

double ACylinder::getRadius()
{
    return radius;
}

int ACylinder::getSlices()
{
    return slices;
}

double ACylinder::getHeight()
{
    return height;
}

void ACylinder::reset(double radius, int slices, double height)
{
    this->radius = radius;
    this->slices = slices;
    this->height = height;

    boundingBoxMin = Vector3d(-radius, 0.0, -radius);
    boundingBoxMax = Vector3d(radius, height, radius);

    vertexCount = 2 * slices + 2;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double step = 2 * M_PI / slices;
    for (int i = 0; i < slices; ++i) {
        double alpha = step * i;
        vertexArray[i] = Vector3d(cos(alpha) * radius, height,
                                  sin(alpha) * radius);
        vertexArray[slices + i] = Vector3d(cos(alpha) * radius, 0.0,
                                  sin(alpha) * radius);
    }
    vertexArray[2 * slices] = Vector3d(0.0, height, 0.0);
    vertexArray[2 * slices + 1] = Vector3d(0.0, 0.0, 0.0);

    faceCount = 4 * slices;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    for (int i = 0; i < slices - 1; ++i) {
        // top
        faceArray[i] = Vector3i(i, i + 1, 2 * slices);
        // bottom
        faceArray[slices + i] = Vector3i(slices + i,
                                         2 * slices + 1, slices + i + 1);
        // side
        faceArray[2 * (slices + i)] = Vector3i(i, slices + i, i + 1);
        faceArray[2 * (slices + i) + 1] = Vector3i(i + 1,
                                                 slices + i, slices + i + 1);
    }
    faceArray[slices - 1] = Vector3i(0, 2 * slices, slices - 1);
    faceArray[slices * 2 - 1] = Vector3i(slices,
                                         2 * slices - 1, 2 * slices + 1);
    faceArray[slices * 4 - 2] = Vector3i(0, slices - 1, 2 * slices - 1);
    faceArray[slices * 4 - 1] = Vector3i(0, 2 * slices - 1, slices);

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

QString ACylinder::toString() const
{
    return "radius=" + QString::number(radius) + "\nslices=" +
            QString::number(slices) + "\nheight=" + QString::number(height) +
            "\n";
}

const QPair<double, double>* ACylinder::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    for (int i = 0; i < slices; ++i) {
        double alpha = 2 * i * M_PI / slices;
        double beta;
        if (i != slices - 1) {
            beta = 2 * (i + 1) * M_PI / slices;
        } else {
            beta = 0;
        }
        // top face
        defaultTextVertexPos[3 * i] = QPair<double, double>(
                    0.25 * qCos(alpha) + 0.25, 0.25 * qSin(alpha) + 0.75);
        defaultTextVertexPos[3 * i + 1] = QPair<double, double>(
                    0.25 * qCos(beta) + 0.25, 0.25 * qSin(beta) + 0.75);
        defaultTextVertexPos[3 * i + 2] = QPair<double, double>(
                    0.25, 0.75);
        // bottom face
        defaultTextVertexPos[3 * (i + slices)] = QPair<double, double>(
                    0.25 * qCos(alpha) + 0.75, 0.25 * qSin(alpha) + 0.75);
        defaultTextVertexPos[3 * (i + slices) + 1] = QPair<double, double>(
                    0.25 * qCos(beta) + 0.75, 0.25 * qSin(beta) + 0.75);
        defaultTextVertexPos[3 * (i + slices) + 2] = QPair<double, double>(
                    0.75, 0.75);
        // side faces
        defaultTextVertexPos[6 * (i + slices)] =
                QPair<double, double>((double)i / slices, 0.5);
        defaultTextVertexPos[6 * (i + slices) + 1] =
                QPair<double, double>((double)(i + 1) / slices, 0.5);
        defaultTextVertexPos[6 * (i + slices) + 2] =
                QPair<double, double>((double)i / slices, 0.0);
        defaultTextVertexPos[6 * (i + slices) + 3] =
                QPair<double, double>((double)(i + 1) / slices, 0.5);
        defaultTextVertexPos[6 * (i + slices) + 4] =
                QPair<double, double>((double)i / slices, 0.0);
        defaultTextVertexPos[6 * (i + slices) + 5] =
                QPair<double, double>((double)(i + 1) / slices, 0.0);
    }
    return defaultTextVertexPos;
}

const int* ACylinder::getDefaultPmtId()
{
    if (defaultPmtId) {
        return defaultPmtId;
    }
    int cnt = getTextVertexCount();
    defaultPmtId = new int[cnt];
    for (int i = 0; i < slices; ++i) {
        // top
        defaultPmtId[3 * i] = i;
        defaultPmtId[3 * i + 1] = i + 1;
        defaultPmtId[3 * i + 2] = 2 * slices;
        // bottom
        defaultPmtId[6 * (i + slices)] = i + slices;
        defaultPmtId[6 * (i + slices) + 1] = i + 1 + slices;
        defaultPmtId[6 * (i + slices) + 2] = 2 * slices + 1;
        // side
        defaultPmtId[6 * (i + slices)] = i;
        defaultPmtId[6 * (i + slices) + 1] = i + 1;
        defaultPmtId[6 * (i + slices) + 2] = i + slices;
        defaultPmtId[6 * (i + slices) + 3] = i + 1;
        defaultPmtId[6 * (i + slices) + 4] = i + slices;
        defaultPmtId[6 * (i + slices) + 5] = i + slices + 1;
    }
    return defaultPmtId;
}
