#ifndef ACYLINDER_H
#define ACYLINDER_H

#include "APrimitive.h"

class ACylinder : APrimitive
{
public:
    ACylinder(double radius, int slices, double height);
    ~ACylinder();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    virtual void setOctree();

    double radius;
    int slices;
    double height;
};

#endif // ACYLINDER_H
