#ifndef APRISM_H
#define APRISM_H

#include "APrimitive.h"

class APrism : public APrimitive
{
public:
    APrism();
    APrism(double length, double sideLength, int sideCount = 3);
    ~APrism();

    double getLength();
    double getSideLength();
    int getSideCount();

    void reset(double length, double sideLength, int sideCount = 3);

    QString virtual toString(ASolid* solid) const;

protected:
    static const double DEFAULT_LENGTH;
    static const double DEFAULT_SIDE_LENGTH;
    static const int DEFAULT_SIDE_COUNT;

    double length;
    double sideLength;
    int sideCount;
};

#endif // APRISM_H
