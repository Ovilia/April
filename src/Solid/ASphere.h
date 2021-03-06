#ifndef ASPHERE_H
#define ASPHERE_H

#include "APrimitive.h"

class ASphere : public APrimitive
{
public:
    ASphere();
    ASphere(double radius, int slices, int stacks);
    ~ASphere();

    double getRadius();
    int getSlices();
    int getStacks();

    void reset(double radius, int slices, int stacks);

    // default vertex position in texture
    virtual const QPair<double, double>* getDefaultTextVertexPos();
    // default index of vertex in APrimitive with given vertex in texture
    virtual const int* getDefaultPmtId();

    QString virtual toString() const;

protected:
    static const double DEFAULT_RADIUS;
    static const int DEFAULT_SLICES;
    static const int DEFAULT_STACKS;

    double radius;
    int slices;
    int stacks;
};

#endif // ASPHERE_H
