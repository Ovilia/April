#ifndef APIPE_H
#define APIPE_H

#include "APrimitive.h"

class APipe : public APrimitive
{
public:
    APipe(double radius, int slices, double thickness, double height);
    ~APipe();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    double radius;
    int slices;
    double thickness;
    double height;
};

#endif // APIPE_H
