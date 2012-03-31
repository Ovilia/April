#include "Vector3d.h"

Vector3d::Vector3d() :
    x(0),
    y(0),
    z(0)
{
}

Vector3d::Vector3d(double x, double y, double z) :
    x(x),
    y(y),
    z(z)
{
}

double Vector3d::getX() const
{
    return x;
}

double Vector3d::getY() const
{
    return y;
}

double Vector3d::getZ() const
{
    return z;
}

void Vector3d::setX(double x)
{
    this->x = x;
}

void Vector3d::setY(double y)
{
    this->y = y;
}

void Vector3d::setZ(double z)
{
    this->z = z;
}

void Vector3d::setXYZ(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

bool operator == (const Vector3d& vector1, const Vector3d& vector2)
{
    return (vector1.x == vector2.x &&
            vector1.y == vector2.y &&
            vector1.z == vector2.z);
}
