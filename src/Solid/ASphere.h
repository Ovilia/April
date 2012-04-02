#ifndef ASPHERE_H
#define ASPHERE_H

#include "APrimitive.h"

class ASphere : public APrimitive
{
public:
    ASphere(double radius, int slices, int stacks);
    ~ASphere();

protected:
    double radius;
    int slices;
    int stacks;
};

#endif // ASPHERE_H
