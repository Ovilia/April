#ifndef APRISM_H
#define APRISM_H

#include "APrimitive.h"

class APrism : public APrimitive
{
public:
    APrism(double length, double sideLength, int sideCount = 3);
    ~APrism();

protected:
    double length;
    double sideLength;
    int sideCount;
};

#endif // APRISM_H
