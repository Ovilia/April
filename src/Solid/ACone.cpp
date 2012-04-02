#include "ACone.h"

ACone::ACone(double radius, int slices, double height) :
    APrimitive(),
    radius(radius),
    slices(slices),
    height(height)
{
    boundingBox = Vector3d(2 * radius, height, 2 * radius);
}

ACone::~ACone()
{

}

void ACone::drawWire()
{

}

void ACone::drawSolid()
{

}

void ACone::setOctree()
{

}
