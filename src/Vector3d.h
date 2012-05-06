#ifndef VECTOR3D_H
#define VECTOR3D_H

#define EPSILON 0.0001

struct Vector3d
{
public:
    Vector3d();
    Vector3d(double x, double y, double z);

    friend bool operator == (const Vector3d& vector1,
                             const Vector3d& vector2);
    friend bool operator != (const Vector3d& vector1,
                             const Vector3d& vector2);

    double dotProduct(Vector3d another) const;
    Vector3d crossProduct(Vector3d another) const;

    double getModulus() const;

    // if modulus is larger than EPSILON,
    // make sure x * x + y * y + z * z = 1.0
    // else, x = y = z = 0.0
    void normalize();

    double x;
    double y;
    double z;
};

#endif // VECTOR3D_H
