#ifndef APRILPRIMITIVE_H
#define APRILPRIMITIVE_H

#include <QString>

class APrimitive
{
public:
    APrimitive(const QString& name = "Primitive");
    virtual ~APrimitive();

    enum PrimitiveType {
        PT_NONE = 0,
        PT_CUBE,
        PT_SPHERE,
        PT_CYLINDER,
        PT_CONE,
        PT_PRISM,
        PT_PYRAMID
    };

    enum RGB_Index {
        INDEX_RED = 0,
        INDEX_GREEN,
        INDEX_BLUE,
        INDEX_ALPHA
    };
    static const int RGBA_LENGTH = 4;

    // draw model with certain style
    virtual void drawWire() = 0;
    virtual void drawSolid() = 0;

    QString getName() const;
    void setName(const QString& name);

    double getXRotate() const;
    double getYRotate() const;
    double getZRotate() const;

    double getXScale() const;
    double getYScale() const;
    double getZScale() const;

    double getXTransform() const;
    double getYTransform() const;
    double getZTransform() const;

    // rotate within [0, 360)
    void setXRotate(const double rotate);
    void setYRotate(const double rotate);
    void setZRotate(const double rotate);

    // scale within (0, infinity)
    void setXScale(const double scale);
    void setYScale(const double scale);
    void setZScale(const double scale);

    // transform within (-infinity, infinity)
    void setXTransform(const double transform);
    void setYTransform(const double transform);
    void setZTransform(const double transform);

    bool getSelected() const;
    void setSelected(const bool value);

protected:
    QString name;

    double xRotate;
    double yRotate;
    double zRotate;

    double xScale;
    double yScale;
    double zScale;

    double xTransform;
    double yTransform;
    double zTransform;

    bool isSelected;

    // rgba color within [0, 1], with index of RGB_INDEX
    // it is originally set to be random
    double color[RGBA_LENGTH];
    // random color to be used when init
    static const int RANDOM_COLOR_COUNT = 12;
    static const double RANDOM_COLOR[RANDOM_COLOR_COUNT][RGBA_LENGTH];

};

#endif // APRILPRIMITIVE_H
