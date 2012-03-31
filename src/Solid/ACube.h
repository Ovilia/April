#ifndef ACUBE_H
#define ACUBE_H

#include "APrimitive.h"

class ACube : public APrimitive
{
public:
    ACube(double width, double depth, double height);
    ~ACube();

    virtual void drawWire();
    virtual void drawSolid();

protected:
    virtual void setOctree();

    double width;
    double depth;
    double height;
};

#endif // ACUBE_H
