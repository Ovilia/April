#include "APrism.h"

#include <qmath.h>

const double APrism::DEFAULT_LENGTH = 1.0;
const double APrism::DEFAULT_SIDE_LENGTH = 1.0;
const int APrism::DEFAULT_SIDE_COUNT = 3;

APrism::APrism() :
    APrimitive(APrimitive::PT_PRISM),
    length(DEFAULT_LENGTH),
    sideLength(DEFAULT_SIDE_LENGTH),
    sideCount(DEFAULT_SIDE_COUNT)
{
    reset(length, sideLength, sideCount);
}

APrism::APrism(double length, double sideLength, int sideCount) :
    APrimitive(APrimitive::PT_PRISM),
    length(length),
    sideLength(sideLength),
    sideCount(sideCount)
{
    reset(length, sideLength, sideCount);
}

APrism::~APrism()
{

}

double APrism::getLength()
{
    return length;
}

double APrism::getSideLength()
{
    return sideLength;
}

int APrism::getSideCount()
{
    return sideCount;
}

void APrism::reset(double length, double sideLength, int sideCount)
{
    this->length = length;
    this->sideLength = sideLength;
    this->sideCount = sideCount;

    double zLength = sideLength * 0.5 * qSqrt(3);
    boundingBox = Vector3d(sideLength, length, zLength);

    vertexCount = 6;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    vertexArray[0] = Vector3d(sideLength / 2.0, length, 0.0);
    vertexArray[1] = Vector3d(0, length, zLength);
    vertexArray[2] = Vector3d(-sideLength / 2.0, length, 0.0);
    vertexArray[3] = Vector3d(sideLength / 2.0, 0.0, 0.0);
    vertexArray[4] = Vector3d(0.0, 0.0, zLength);
    vertexArray[5] = Vector3d(-sideLength / 2.0, 0.0, 0.0);

    faceCount = 8;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    faceArray[0] = Vector3i(0, 1, 3);
    faceArray[1] = Vector3i(1, 4, 3);
    faceArray[2] = Vector3i(1, 2, 4);
    faceArray[3] = Vector3i(2, 5, 4);
    faceArray[4] = Vector3i(0, 2, 5);
    faceArray[5] = Vector3i(0, 5, 3);
    faceArray[6] = Vector3i(0, 2, 1);
    faceArray[7] = Vector3i(3, 4, 5);
}

QString APrism::toString() const
{
    return "length=" + QString::number(length) + "\nsideLength=" +
            QString::number(sideLength) + "\nsideCount=" +
            QString::number(sideCount) + "\n";
}
