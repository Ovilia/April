#include <qmath.h>

#include "APrism.h"

APrism::APrism(double length, double sideLength, int sideCount) :
    APrimitive(),
    length(length),
    sideLength(sideLength),
    sideCount(sideCount)
{
    reset(length, sideLength, sideCount);
}

APrism::~APrism()
{

}

void APrism::reset(double length, double sideLength, int sideCount)
{
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
