#ifndef ACUBE_H
#define ACUBE_H

#include "APrimitive.h"

class ACube : public APrimitive
{
public:
    ACube();
    ACube(double width, double depth, double height);
    ~ACube();

    double getWidth();
    double getDepth();
    double getHeight();

    void reset(double width, double depth, double height);

    // default vertex position in texture
    virtual const QPair<double, double>* getDefaultTextVertexPos();
    // default index of vertex in APrimitive with given vertex in texture
    virtual const int* getDefaultPmtId();

    QString virtual toString() const;

protected:
    double width;
    double depth;
    double height;

    static const double DEFAULT_WIDTH;
    static const double DEFAULT_DEPTH;
    static const double DEFAULT_HEIGHT;
};

#endif // ACUBE_H
