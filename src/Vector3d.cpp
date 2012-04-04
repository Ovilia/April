#include "Vector3d.h"

Vector3d::Vector3d() :
    x(0.0),
    y(0.0),
    z(0.0)
{
}

Vector3d::Vector3d(double x, double y, double z) :
    x(x),
    y(y),
    z(z)
{
}

bool operator == (const Vector3d& vector1, const Vector3d& vector2)
{
    return (vector1.x == vector2.x &&
            vector1.y == vector2.y &&
            vector1.z == vector2.z);
}
