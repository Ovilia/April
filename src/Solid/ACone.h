#ifndef ACONE_H
#define ACONE_H

#include "APrimitive.h"

class ACone : public APrimitive
{
public:
    ACone(double radius, int slices, double height);
    ~ACone();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    virtual void setOctree();

    double radius;
    int slices;
    double height;
};

#endif // ACONE_H
