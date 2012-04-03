#ifndef APYRAMID_H
#define APYRAMID_H

#include "APrimitive.h"

class APyramid : public APrimitive
{
public:
    APyramid(double sideLength, int sideCount = 3);
    ~APyramid();

    double getSideLength();
    int getSideCount();

    void reset(double sideLength, int sideCount = 3);

protected:
    double sideLength;
    int sideCount;
};

#endif // APYRAMID_H
