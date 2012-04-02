#include <qmath.h>

#include "APyramid.h"

APyramid::APyramid(double sideLength, int sideCount) :
    APrimitive(),
    sideLength(sideLength),
    sideCount(sideCount)
{
    // TODO: only calculated when sideCount is 4 now
    boundingBox = Vector3d(sideLength, sideLength * 0.5 * qSqrt(2), sideLength);
}

APyramid::~APyramid()
{

}
