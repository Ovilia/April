#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d
{
public:
    Vector3d();
    Vector3d(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setXYZ(double x, double y, double z);

    friend bool operator == (const Vector3d& vector1,
                             const Vector3d& vector2);

private:
    double x;
    double y;
    double z;
};

#endif // VECTOR3D_H
