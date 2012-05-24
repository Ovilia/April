#ifndef APRILSOLID_H
#define APRILSOLID_H

#include <QString>

#include "APrimitive.h"
#include "Vector3d.h"

class APrimitive;

class ASolid
{
public:
    enum BoolOperation {
        BO_PRIMITIVE = 0,
        BO_INTERSECTION,
        BO_UNION,
        BO_DIFFERENCE
    };
    static const int BOOL_OPERATION_COUNT = 4;
    static const QString BOOL_OPERATION_NAME[BOOL_OPERATION_COUNT];

    ASolid(APrimitive* primitive, const QString& name = "Solid");
    ASolid(ASolid* leftChild, ASolid* rightChild,
           BoolOperation operation, const QString& name = "Solid");
    ~ASolid();

    QString getName() const;
    void setName(const QString& name);

    ASolid* getParent() const;
    void setParenet(ASolid* parent);

    bool isRoot() const;
    bool isLeave() const;

    bool hasDescent(ASolid* descent) const;

    void drawWire() const;
    void drawSolid() const;

    ASolid* getLeftChild() const;
    ASolid* getRightChild() const;
    BoolOperation getOperation() const;

    void setLeftChild(ASolid* leftChild);
    void setRightChild(ASolid* rightChild);
    void setOperation(BoolOperation operation);

    APrimitive* getPrimitive() const;

    Vector3d getBoundingBoxMin() const;
    Vector3d getBoundingBoxMax() const;

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

    bool getSelected() const;
    void setSelected(const bool value, const bool usePmtColor = true);

    bool getVisible() const;
    void setVisible(const bool visible);

    QString toString() const;

private:
    QString name;

    ASolid* leftChild;
    ASolid* rightChild;
    BoolOperation operation;
    ASolid* parent;

    // used if is leaf
    APrimitive* primitive;

    // bounding box to hold it
    Vector3d boundingBoxMin;
    Vector3d boundingBoxMax;

    static const Vector3d DEFAULT_ROTATE;
    static const Vector3d DEFAULT_SCALE;
    static const Vector3d DEFAULT_TRANSLATE;

    static const Vector3d SELECTED_COLOR;

    Vector3d rotate;
    Vector3d scale;
    Vector3d translate;

    bool isSelected;
    bool isVisible;

    void drawBefore() const;
    void drawAfter() const;
    void drawBoundingBox() const;
};

#endif // APRILSOLID_H
