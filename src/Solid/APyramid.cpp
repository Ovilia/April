#include "APyramid.h"

APyramid::APyramid(double sideLength, int sideCount) :
    APrimitive(sideLength, sideLength),
    sideLength(sideLength),
    sideCount(sideCount)
{
    // TODO: calculate and set height according to sideCount here
}

APyramid::~APyramid()
{

}

void APyramid::drawWire()
{

}

void APyramid::drawSolid()
{

}
