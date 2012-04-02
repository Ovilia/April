#include "ACylinder.h"

ACylinder::ACylinder(double radius, int slices, double height) :
    APrimitive(),
    radius(radius),
    slices(slices),
    height(height)
{
    boundingBox = Vector3d(2 * radius, height, 2 * radius);
}

ACylinder::~ACylinder()
{

}
