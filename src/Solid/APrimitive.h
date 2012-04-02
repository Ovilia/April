#ifndef APRILPRIMITIVE_H
#define APRILPRIMITIVE_H

#include <QString>

#include "Vector3d.h"

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

    // draw model with certain style
    virtual void drawWire() = 0;
    virtual void drawSolid() = 0;
    // draw help functions dealing with color, rotate and so on
    // to be called before and after drawWire and drawSolid
    void drawBefore();
    void drawAfter();

    QString getName() const;
    void setName(const QString& name);

    Vector3d getBoundingBox();

    Vector3d getRotate() const;
    Vector3d getScale() const;
    Vector3d getTranslate() const;

    // rotate within [0, 360)
    void setXRotate(const double rotate);
    void setYRotate(const double rotate);
    void setZRotate(const double rotate);

    // scale within (0, infinity)
    void setXScale(const double scale);
    void setYScale(const double scale);
    void setZScale(const double scale);

    // translate within (-infinity, infinity)
    void setXTranslate(const double translate);
    void setYTranslate(const double translate);
    void setZTranslate(const double translate);

    bool getSelected() const;
    void setSelected(const bool value);

protected:
    QString name;

    // min box to hold it
    Vector3d boundingBox;

    Vector3d rotate;
    Vector3d scale;
    Vector3d translate;

    bool isSelected;

    // rgba color within [0, 1], with index of RGB_INDEX
    // it is originally set to be random
    Vector3d color;
    // random color to be used when init
    static const int RANDOM_COLOR_COUNT = 12;
    static const double RANDOM_COLOR[RANDOM_COLOR_COUNT][3];

};

#endif // APRILPRIMITIVE_H
