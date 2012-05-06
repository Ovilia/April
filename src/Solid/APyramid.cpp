#include "APyramid.h"

#include <qmath.h>

const double APyramid::DEFAULT_SIDE_LENGTH = 1.0;
const int APyramid::DEFAULT_SIDE_COUNT = 4;

APyramid::APyramid() :
    APrimitive(APrimitive::PT_PRISM),
    sideLength(DEFAULT_SIDE_LENGTH),
    sideCount(DEFAULT_SIDE_LENGTH)
{
    reset(sideLength, sideCount);
}

APyramid::APyramid(double sideLength, int sideCount) :
    APrimitive(APrimitive::PT_PYRAMID),
    sideLength(sideLength),
    sideCount(sideCount)
{
    reset(sideLength, sideCount);
}

APyramid::~APyramid()
{

}

double APyramid::getSideLength()
{
    return sideLength;
}

int APyramid::getSideCount()
{
    return sideCount;
}

void APyramid::reset(double sideLength, int sideCount)
{
    this->sideLength = sideLength;
    this->sideCount = sideCount;

    // TODO: only calculated when sideCount is 4 now
    double height = sideLength * 0.5 * qSqrt(2);
    boundingBox = Vector3d(sideLength, height, sideLength);

    vertexCount = 4;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double tmp = sideLength * qSqrt(3);
    vertexArray[0] = Vector3d(0.0, height, 0.0);
    vertexArray[1] = Vector3d(-0.5 * sideLength, 0.0, tmp / 6.0);
    vertexArray[2] = Vector3d(0.5 * sideLength, 0.0, tmp / 6.0);
    vertexArray[3] = Vector3d(0.0, 0.0, -tmp / 3.0);

    faceCount = 4;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    faceArray[0] = Vector3i(0, 1, 2);
    faceArray[1] = Vector3i(0, 2, 3);
    faceArray[2] = Vector3i(1, 2, 3);
    faceArray[3] = Vector3i(0, 1, 3);
}

QString APyramid::toString(ASolid* solid) const
{
    QString str = toStringCommon(solid);
    if (sideLength - DEFAULT_SIDE_LENGTH > EPSILON) {
        str += QString("sideLength=") + QString::number(sideLength) +
                QString("\n");
    }
    if (sideCount != DEFAULT_SIDE_COUNT) {
        str += QString("sideCount=") + QString::number(sideCount) +
                QString("\n");
    }
    str += QString("\n");
    return str;
}
