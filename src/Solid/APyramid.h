#ifndef APYRAMID_H
#define APYRAMID_H

#include "APrimitive.h"

class APyramid : public APrimitive
{
public:
    APyramid();
    APyramid(double sideLength, int sideCount = 3);
    ~APyramid();

    double getSideLength();
    int getSideCount();

    void reset(double sideLength, int sideCount = 3);

    QString virtual toString(ASolid* solid) const;

protected:
    static const double DEFAULT_SIDE_LENGTH;
    static const int DEFAULT_SIDE_COUNT;

    double sideLength;
    int sideCount;
};

#endif // APYRAMID_H
