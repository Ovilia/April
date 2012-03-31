#ifndef APRISM_H
#define APRISM_H

#include "APrimitive.h"

class APrism : public APrimitive
{
public:
    APrism(double length, double sideLength, int sideCount);
    ~APrism();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    double length;
    double sideLength;
    int sideCount;
};

#endif // APRISM_H
