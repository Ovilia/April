#ifndef ACYLINDER_H
#define ACYLINDER_H

#include "APrimitive.h"

class ACylinder : public APrimitive
{
public:
    ACylinder(double radius, int slices, double height);
    ~ACylinder();

protected:
    double radius;
    int slices;
    double height;
};

#endif // ACYLINDER_H
