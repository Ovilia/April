#ifndef VECTOR3D_H
#define VECTOR3D_H

struct Vector3d
{
public:
    Vector3d();
    Vector3d(double x, double y, double z);

    friend bool operator == (const Vector3d& vector1,
                             const Vector3d& vector2);
    double x;
    double y;
    double z;
};

#endif // VECTOR3D_H
