#include "Vector3d.h"

#include <qmath.h>

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
    return (qAbs(vector1.x - vector2.x) < EPSILON &&
            qAbs(vector1.y - vector2.y) < EPSILON &&
            qAbs(vector1.z - vector2.z) < EPSILON);
}

bool operator != (const Vector3d& vector1, const Vector3d& vector2)
{
    return !(vector1 == vector2);
}

Vector3d operator - (const Vector3d& vector1, const Vector3d& vector2)
{
    return Vector3d(vector1.x - vector2.x,
                    vector1.y - vector2.y,
                    vector1.z - vector2.z);
}

Vector3d operator + (const Vector3d& vector1, const Vector3d& vector2)
{
    return Vector3d(vector1.x + vector2.x,
                    vector1.y + vector2.y,
                    vector1.z + vector2.z);
}

double Vector3d::dotProduct(Vector3d another) const
{
    return this->x * another.x +
            this->y * another.y +
            this->z * another.z;
}

Vector3d Vector3d::crossProduct(Vector3d another) const
{
    return Vector3d(this->y * another.z - this->z * another.y,
                    this->z * another.x - this->x * another.z,
                    this->x * another.y - this->y * another.x);
}

double Vector3d::getModulus() const
{
    return qSqrt(x * x + y * y + z * z);
}

void Vector3d::normalize()
{
    double modulus = getModulus();
    if (modulus < EPSILON) {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    } else {
        x /= modulus;
        y /= modulus;
        z /= modulus;
    }
}
