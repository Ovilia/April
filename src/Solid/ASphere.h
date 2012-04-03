#ifndef ASPHERE_H
#define ASPHERE_H

#include "APrimitive.h"

class ASphere : public APrimitive
{
public:
    ASphere(double radius, int slices, int stacks);
    ~ASphere();

    double getRadius();
    int getSlices();
    int getStacks();

    void reset(double radius, int slices, int stacks);

protected:
    double radius;
    int slices;
    int stacks;
};

#endif // ASPHERE_H
