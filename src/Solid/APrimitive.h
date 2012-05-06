#ifndef APRILPRIMITIVE_H
#define APRILPRIMITIVE_H

#include <QString>

#include "ASolid.h"
#include "Vector3d.h"
#include "Vector3i.h"

class ASolid;

class APrimitive
{
public:
    enum PrimitiveType {
        PT_NONE = 0,
        PT_CONE,
        PT_CUBE,
        PT_CYLINDER,
        PT_PRISM,
        PT_PYRAMID,
        PT_SPHERE
    };
    static const int PRIMITIVE_TYPE_COUNT = 7;
    static const QString PRIMITIVE_TYPE_NAME[PRIMITIVE_TYPE_COUNT];

    APrimitive(PrimitiveType type, const QString& name = "Primitive");
    // virtual destructor to make this class abstract
    virtual ~APrimitive() = 0;

    PrimitiveType getType();

    // draw model with certain style
    void drawWire();
    void drawSolid();
    // draw help functions dealing with rotate and so on
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

    QString virtual toString(ASolid* solid) const = 0;

protected:
    QString name;
    PrimitiveType primitiveType;

    // min box to hold it
    Vector3d boundingBox;

    static const Vector3d DEFAULT_ROTATE;
    static const Vector3d DEFAULT_SCALE;
    static const Vector3d DEFAULT_TRANSLATE;

    Vector3d rotate;
    Vector3d scale;
    Vector3d translate;

    bool isSelected;

    // rgba color within [0, 1], with index of RGB_INDEX
    // it is originally set to be random
    Vector3d color;
    // color used when drawWire
    Vector3d wireColor;
    // random color to be used when init
    static const int RANDOM_COLOR_COUNT = 12;
    static const double RANDOM_COLOR[RANDOM_COLOR_COUNT][3];

    // vertex position
    int vertexCount;
    Vector3d* vertexArray;

    // vertex pair to make triangle faces, not the real face count
    int faceCount;
    Vector3i* faceArray;

    // common part of toString
    QString toStringCommon(ASolid* solid) const;
};

#endif // APRILPRIMITIVE_H
