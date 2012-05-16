#ifndef ACYLINDER_H
#define ACYLINDER_H

#include "APrimitive.h"

class ACylinder : public APrimitive
{
public:
    ACylinder();
    ACylinder(double radius, int slices, double height);
    ~ACylinder();

    double getRadius();
    int getSlices();
    double getHeight();

    void reset(double radius, int slices, double height);

    QString virtual toString() const;

protected:
    static const double DEFAULT_RADIUS;
    static const int DEFAULT_SLICES;
    static const double DEFAULT_HEIGHT;

    double radius;
    int slices;
    double height;
};

#endif // ACYLINDER_H
