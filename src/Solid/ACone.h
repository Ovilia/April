#ifndef ACONE_H
#define ACONE_H

#include "APrimitive.h"

class ACone : public APrimitive
{
public:
    ACone();
    ACone(double radius, int slices, double height);
    ~ACone();

    double getRadius();
    int getSlices();
    double getHeight();

    void reset(double radius, int slices, double height);

    // default vertex position in texture
    virtual const QPair<double, double>* getDefaultTextVertexPos();
    // default index of vertex in APrimitive with given vertex in texture
    virtual const int* getDefaultPmtId();

    QString virtual toString() const;

protected:
    static const double DEFAULT_RADIUS;
    static const int DEFAULT_SLICES;
    static const double DEFAULT_HEIGHT;

    double radius;
    int slices;
    double height;
};

#endif // ACONE_H
