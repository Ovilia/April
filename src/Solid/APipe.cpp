#include "APipe.h"

APipe::APipe(double radius, int slices, double thickness, double height) :
    APrimitive(radius, radius, height),
    radius(radius),
    slices(slices),
    thickness(thickness),
    height(height)
{
}

APipe::~APipe()
{

}

void APipe::drawWire()
{

}

void APipe::drawSolid()
{

}
