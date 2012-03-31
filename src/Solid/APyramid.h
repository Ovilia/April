#ifndef APYRAMID_H
#define APYRAMID_H

#include "APrimitive.h"

class APyramid : public APrimitive
{
public:
    APyramid(double sideLength, int sideCount);
    ~APyramid();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    double sideLength;
    int sideCount;
};

#endif // APYRAMID_H
