#include "Vector3i.h"

Vector3i::Vector3i() :
    x(0),
    y(0),
    z(0)
{
}

Vector3i::Vector3i(int x, int y, int z) :
    x(x),
    y(y),
    z(z)
{
}

bool operator == (const Vector3i& vector1, const Vector3i& vector2)
{
    return (vector1.x == vector2.x &&
            vector1.y == vector2.y &&
            vector1.z == vector2.z);
}
