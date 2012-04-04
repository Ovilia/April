#ifndef ACUBE_H
#define ACUBE_H

#include "APrimitive.h"

class ACube : public APrimitive
{
public:
    ACube(double width, double depth, double height);
    ~ACube();

    double getWidth();
    double getDepth();
    double getHeight();

    void reset(double width, double depth, double height);

protected:
    double width;
    double depth;
    double height;
};

#endif // ACUBE_H
