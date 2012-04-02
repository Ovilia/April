#ifdef _DEBUG
#include <assert.h>
#endif

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

APrimitive::APrimitive(const QString& name) :
    name(name),
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

QString APrimitive::getName() const
{
    return name;
}

void APrimitive::setName(const QString& name)
{
    this->name = name;
}

double APrimitive::getXRotate() const
{
    return xRotate;
}

double APrimitive::getYRotate() const
{
    return yRotate;
}

double APrimitive::getZRotate() const
{
    return zRotate;
}

double APrimitive::getXScale() const
{
    return xScale;
}

double APrimitive::getYScale() const
{
    return yScale;
}

double APrimitive::getZScale() const
{
    return zScale;
}

double APrimitive::getXTransform() const
{
    return xTransform;
}

double APrimitive::getYTransform() const
{
    return yTransform;
}

double APrimitive::getZTransform() const
{
    return zTransform;
}

void APrimitive::setXRotate(const double rotate)
{
#ifdef _DEBUG
    assert(rotate >= 0 && rotate < 360);
#endif
    xRotate = rotate;
}

void APrimitive::setYRotate(const double rotate)
{
#ifdef _DEBUG
    assert(rotate >= 0 && rotate < 360);
#endif
    yRotate = rotate;
}

void APrimitive::setZRotate(const double rotate)
{
#ifdef _DEBUG
    assert(rotate >= 0 && rotate < 360);
#endif
    zRotate = rotate;
}

void APrimitive::setXScale(const double scale)
{
#ifdef _DEBUG
    assert(scale > 0);
#endif
    xScale = scale;
}

void APrimitive::setYScale(const double scale)
{
#ifdef _DEBUG
    assert(scale > 0);
#endif
    yScale = scale;
}

void APrimitive::setZScale(const double scale)
{
#ifdef _DEBUG
    assert(scale > 0);
#endif
    yScale = scale;
}

void APrimitive::setXTransform(const double transform)
{
    xTransform = transform;
}

void APrimitive::setYTransform(const double transform)
{
    yTransform = transform;
}

void APrimitive::setZTransform(const double transform)
{
    zTransform = transform;
}

bool APrimitive::getSelected() const
{
    return isSelected;
}

void APrimitive::setSelected(const bool value)
{
    isSelected = value;
}
