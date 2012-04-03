#ifndef APRISM_H
#define APRISM_H

#include "APrimitive.h"

class APrism : public APrimitive
{
public:
    APrism(double length, double sideLength, int sideCount = 3);
    ~APrism();

    double getLength();
    double getSideLength();
    int getSideCount();

    void reset(double length, double sideLength, int sideCount = 3);

protected:
    double length;
    double sideLength;
    int sideCount;
};

#endif // APRISM_H
