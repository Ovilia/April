#include <assert.h>
#include <ctime>
#include <cstdlib>

#include "APrimitive.h"

const double APrimitive::RANDOM_COLOR[RANDOM_COLOR_COUNT][RGBA_LENGTH] =
{
    {0.00, 1.00, 1.00, 1.0},
    {1.00, 0.00, 1.00, 1.0},
    {1.00, 1.00, 0.00, 1.0},
    {0.25, 0.75, 0.75, 1.0},
    {0.75, 0.25, 0.75, 1.0},
    {0.75, 0.75, 0.25, 1.0},
    {0.00, 0.75, 1.00, 1.0},
    {0.75, 1.00, 0.00, 1.0},
    {1.00, 0.00, 0.75, 1.0},
    {0.00, 1.00, 0.75, 1.0},
    {0.75, 0.00, 1.00, 1.0},
    {1.00, 0.75, 1.00, 1.0}
};

APrimitive::APrimitive() :
    xRotate(0.0),
    yRotate(0.0),
    zRotate(0.0),
    xScale(1.0),
    yScale(1.0),
    zScale(1.0),
    xTransform(0.0),
    yTransform(0.0),
    zTransform(0.0),
    isSelected(false)
{
    // set random color
    srand((unsigned)time(0));
    int index = rand() % RANDOM_COLOR_COUNT;
    for (int rgba = 0; rgba < RGBA_LENGTH; ++rgba) {
        color[rgba] = RANDOM_COLOR[index][rgba];
    }
}

APrimitive::~APrimitive()
{

}

double APrimitive::getXRotate()
{
    return xRotate;
}

double APrimitive::getYRotate()
{
    return yRotate;
}

double APrimitive::getZRotate()
{
    return zRotate;
}

double APrimitive::getXScale()
{
    return xScale;
}

double APrimitive::getYScale()
{
    return yScale;
}

double APrimitive::getZScale()
{
    return zScale;
}

double APrimitive::getXTransform()
{
    return xTransform;
}

double APrimitive::getYTransform()
{
    return yTransform;
}

double APrimitive::getZTransform()
{
    return zTransform;
}

void APrimitive::setXRotate(double rotate)
{
    assert(rotate >= 0 && rotate < 360);
    xRotate = rotate;
}

void APrimitive::setYRotate(double rotate)
{
    assert(rotate >= 0 && rotate < 360);
    yRotate = rotate;
}

void APrimitive::setZRotate(double rotate)
{
    assert(rotate >= 0 && rotate < 360);
    zRotate = rotate;
}

void APrimitive::setXScale(double scale)
{
    assert(scale > 0);
    xScale = scale;
}

void APrimitive::setYScale(double scale)
{
    assert(scale > 0);
    yScale = scale;
}

void APrimitive::setZScale(double scale)
{
    assert(scale > 0);
    yScale = scale;
}

void APrimitive::setXTransform(double transform)
{
    xTransform = transform;
}

void APrimitive::setYTransform(double transform)
{
    yTransform = transform;
}

void APrimitive::setZTransform(double transform)
{
    zTransform = transform;
}

bool APrimitive::getSelected()
{
    return isSelected;
}

void APrimitive::setSelected(bool value)
{
    isSelected = value;
}
