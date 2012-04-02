#include "ASphere.h"

ASphere::ASphere(double radius, int slices, int stacks) :
    APrimitive(),
    radius(radius),
    slices(slices),
    stacks(stacks)
{
    boundingBox = Vector3d(2 * radius, 2 * radius, 2 * radius);
}

ASphere::~ASphere()
{

}
