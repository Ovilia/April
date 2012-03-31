#include "ASphere.h"

ASphere::ASphere(double radius, int slices, int stacks) :
    APrimitive(radius, radius, radius),
    radius(radius),
    slices(slices),
    stacks(stacks)
{
}

ASphere::~ASphere()
{

}

void ASphere::drawWire()
{

}

void ASphere::drawSolid()
{

}
