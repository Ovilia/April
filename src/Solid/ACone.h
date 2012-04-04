#ifndef ACONE_H
#define ACONE_H

#include "APrimitive.h"

class ACone : public APrimitive
{
public:
    ACone(double radius, int slices, double height);
    ~ACone();

    double getRadius();
    int getSlices();
    double getHeight();

    void reset(double radius, int slices, double height);

protected:
    double radius;
    int slices;
    double height;
};

#endif // ACONE_H
