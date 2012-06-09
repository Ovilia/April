#ifndef APRILPRIMITIVE_H
#define APRILPRIMITIVE_H

#include <QString>

#include "ASolid.h"
#include "MatrixD.h"
#include "Solid/Material.h"
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

    PrimitiveType getType() const;

    // draw model with certain style
    void drawWire() const;
    void drawSolid() const;
    // draw help functions dealing with rotate and so on
    // to be called before and after drawWire and drawSolid
    void drawBefore() const;
    void drawAfter() const;
    void drawBoundingBox() const;

    QString getName() const;
    void setName(const QString& name);

    Vector3d getBoundingBoxMin();
    Vector3d getBoundingBoxMax();

    Vector3d getRotate() const;
    Vector3d getScale() const;
    Vector3d getTranslate() const;

    // rotate within [0, 360)
    void setXRotate(const double rotate);
    void setYRotate(const double rotate);
    void setZRotate(const double rotate);
    void setRotate(const Vector3d& rotate);

    // scale within (0, infinity)
    void setXScale(const double scale);
    void setYScale(const double scale);
    void setZScale(const double scale);
    void setScale(const Vector3d& scale);

    // translate within (-infinity, infinity)
    void setXTranslate(const double translate);
    void setYTranslate(const double translate);
    void setZTranslate(const double translate);
    void setTranslate(const Vector3d& translate);

    Vector3d getColor() const;
    void setColor(Vector3d color);

    bool getSelected() const;
    void setSelected(const bool value, const bool usePmtColor);

    unsigned int getMaterialId() const;
    void setMaterialId(unsigned int id);

    QString virtual toString() const = 0;

protected:
    QString name;
    PrimitiveType primitiveType;

    // bounding box to hold it
    Vector3d boundingBoxMin;
    Vector3d boundingBoxMax;

    static const Vector3d DEFAULT_ROTATE;
    static const Vector3d DEFAULT_SCALE;
    static const Vector3d DEFAULT_TRANSLATE;

    Vector3d rotate;
    Vector3d scale;
    Vector3d translate;

    // rgba color within [0, 1], with index of RGB_INDEX
    // it is originally set to be random
    Vector3d color;
    // color used when drawWire
    Vector3d wireColor;
    // random color to be used when init
    static const int RANDOM_COLOR_COUNT = 16;
    static const double RANDOM_COLOR[RANDOM_COLOR_COUNT][3];
    static const Vector3d SELECTED_PMT_COLOR;
    static const Vector3d SELECTED_SLD_COLOR;

    // vertex position
    int vertexCount;
    Vector3d* vertexArray;

    // vertex pair to make triangle faces, not the real face count
    int faceCount;
    Vector3i* faceArray;

    // common part of toString
    QString toStringCommon(ASolid* solid) const;

    // reset bounding box according to vertex and current rotate, scale
    // and translate
    void resetBoundBoxRotate();
    void resetBoundBoxScale(Vector3d newScale);
    void resetBoundBoxTrans(Vector3d newTrans);
    Vector3d oldScale;
    Vector3d oldTrans;
    // get transformed vertex from transform matrix
    Vector3d transform(Vector3d vertex, const MatrixD& mat) const;

    bool isSelected;
    // different color if is selected primitive or solid
    Vector3d selectColor;

    // material
    unsigned int materialId;
};

#endif // APRILPRIMITIVE_H
