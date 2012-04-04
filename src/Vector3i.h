#ifndef VECTOR3I_H
#define VECTOR3I_H

struct Vector3i
{
public:
    Vector3i();
    Vector3i(int x, int y, int z);

    friend bool operator == (const Vector3i& vector1,
                             const Vector3i& vector2);
    int x;
    int y;
    int z;
};

#endif // VECTOR3I_H
