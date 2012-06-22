#include "ASphere.h"

#include "cmath"
#ifndef M_PI
#define M_PI 3.1415926536
#endif

const double ASphere::DEFAULT_RADIUS = 0.5;
const int ASphere::DEFAULT_SLICES = 16;
const int ASphere::DEFAULT_STACKS = 8;

ASphere::ASphere() :
    APrimitive(APrimitive::PT_SPHERE),
    radius(DEFAULT_RADIUS),
    slices(DEFAULT_SLICES),
    stacks(DEFAULT_STACKS)
{
    reset(radius, slices, stacks);
}

ASphere::ASphere(double radius, int slices, int stacks) :
    APrimitive(APrimitive::PT_SPHERE),
    radius(radius),
    slices(slices),
    stacks(stacks)
{
    reset(radius, slices, stacks);
}

ASphere::~ASphere()
{

}

double ASphere::getRadius()
{
    return radius;
}

int ASphere::getSlices()
{
    return slices;
}

int ASphere::getStacks()
{
    return stacks;
}

void ASphere::reset(double radius, int slices, int stacks)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;

    boundingBoxMin = Vector3d(-radius, -radius, -radius);
    boundingBoxMax = Vector3d(radius, radius, radius);

    vertexCount = (stacks - 1) * slices + 2;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    vertexArray[0] = Vector3d(0.0, radius, 0.0);
    int index = 1;
    double tStep = 2 * radius / stacks;
    double sStep = 2 * M_PI / slices;
    for (int t = 1; t < stacks; ++t) {
        double y = radius - tStep * t;
        double newRadius = sqrt(radius * radius - y * y);
        for (int s = 0; s < slices; ++s) {
            double alpha = sStep * s;
            vertexArray[index] = Vector3d(cos(alpha) * newRadius,
                                          y,
                                          sin(alpha) * newRadius);
            ++index;
        }
    }
    vertexArray[index] = Vector3d(0.0, -radius, 0.0);

    faceCount = 2 * (stacks - 1) * slices;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    int bottom = 2 * slices * stacks - 3 * slices;
    for (int i = 0; i < slices - 1; ++i) {
        // top
        faceArray[i] = Vector3i(0, i + 1, i + 2);
        // bottom
        faceArray[bottom + i] = Vector3i((stacks - 2) * slices + i + 1,
                                         (stacks - 2) * slices + i + 2,
                                         (stacks - 1) * slices + 1);
    }
    // last piece of top and bottom
    faceArray[slices - 1] = Vector3i(0, slices, 1);
    faceArray[faceCount - 1] = Vector3i(stacks * slices - slices,
                                        stacks * slices - 2 * slices + 1,
                                        (stacks - 1) * slices + 1);
    index = slices;
    for (int t = 1; t < stacks - 1; ++t) {
        for (int s = 0; s < slices - 1; ++s) {
            faceArray[index] = Vector3i((t - 1) * slices + s + 1,
                                        t * slices + s + 1,
                                        (t - 1) * slices + s + 2);
            ++index;
            faceArray[index] = Vector3i((t - 1) * slices + s + 2,
                                        t * slices + s + 1,
                                        t * slices + s + 2);
            ++index;
        }
        // last piece of each stack
        faceArray[index] = Vector3i((t - 1) * slices + 1,
                                    t * slices,
                                    (t + 1) * slices);
        ++index;
        faceArray[index] = Vector3i((t - 1) * slices + 1,
                                    (t + 1) * slices,
                                    t * slices + 1);
        ++index;
    }

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

QString ASphere::toString() const
{
    return "radius=" + QString::number(radius) + "\nslices=" +
            QString::number(slices) + "\nstacks=" + QString::number(stacks)
            + "\n";
}

const QPair<double, double>* ASphere::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    for (int i = 0; i < slices; ++i) {
        // top
        defaultTextVertexPos[3 * i] = QPair<double, double>(
                    (double)i / slices + 0.5 / slices, 1.0);
        defaultTextVertexPos[3 * i + 1] = QPair<double, double>(
                    (double)i / slices, 1.0 - 1.0 / stacks);
        defaultTextVertexPos[3 * i + 2] = QPair<double, double>(
                    (double)(i + 1) / slices, 1.0 - 1.0 / stacks);
        // center
        for (int j = 1; j < stacks - 1; ++j) {
            int index = 3 * slices + ((j - 1) * slices + i) * 6;
            defaultTextVertexPos[index] = QPair<double, double>(
                        (double)i / slices, 1.0 - (double)j / stacks);
            defaultTextVertexPos[index + 1] = QPair<double, double>(
                        (double)(i + 1) / slices, 1.0 - (double)j / stacks);
            defaultTextVertexPos[index + 2] = QPair<double, double>(
                        (double)i / slices, 1.0 - (double)(j + 1) / stacks);
            defaultTextVertexPos[index + 3] = QPair<double, double>(
                        (double)(i + 1) / slices, 1.0 - (double)j / stacks);
            defaultTextVertexPos[index + 4] = QPair<double, double>(
                        (double)i / slices, 1.0 - (double)(j + 1) / stacks);
            defaultTextVertexPos[index + 5] = QPair<double, double>(
                        (double)(i + 1) / slices,
                        1.0 - (double)(j + 1) / stacks);
        }
        // bottom
        int index = 6 * slices * stacks - 9 * slices;
        defaultTextVertexPos[3 * i + index] = QPair<double, double>(
                    1.0 * i / slices + 0.5 / slices, 0.0);
        defaultTextVertexPos[3 * i + 1 + index] = QPair<double, double>(
                    1.0 * i / slices, 1.0 / stacks);
        defaultTextVertexPos[3 * i + 2 + index] = QPair<double, double>(
                    1.0 * (i + 1) / slices, 1.0 / stacks);
    }
    return defaultTextVertexPos;
}

const int* ASphere::getDefaultPmtId()
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
