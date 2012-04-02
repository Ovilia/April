#include <qmath.h>

#include "APrism.h"

APrism::APrism(double length, double sideLength, int sideCount) :
    APrimitive(),
    length(length),
    sideLength(sideLength),
    sideCount(sideCount)
{
    boundingBox = Vector3d(sideLength, length, sideLength * 0.5 * qSqrt(3));
}

APrism::~APrism()
{

}

void APrism::drawWire()
{

}

void APrism::drawSolid()
{

}
