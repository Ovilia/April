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

    ASolid(unsigned int primitiveID, APrimitive* primitive,
           const QString& name = "Solid");
    ASolid(ASolid* leftChild, ASolid* rightChild,
           BoolOperation operation, const QString& name = "Solid");
    ~ASolid();

    QString getName() const;
    void setName(const QString& name);

    ASolid* getParent();
    void setParenet(ASolid* parent);

    bool isRoot();
    bool isLeave();

    void drawWire() const;
    void drawSolid() const;

    ASolid* getLeftChild();
    ASolid* getRightChild();
    BoolOperation getOperation();

    void setLeftChild(ASolid* leftChild);
    void setRightChild(ASolid* rightChild);
    void setOperation(BoolOperation operation);

    APrimitive* getPrimitive();

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

    QString toString() const;

private:
    QString name;

    ASolid* leftChild;
    ASolid* rightChild;
    BoolOperation operation;
    ASolid* parent;

    // used if is leaf
    APrimitive* primitive;
    // unique! used to identify different primitive, allocated by ModelManager
    // should not be changed within ASolid
    unsigned int primitiveID;

    // min box to hold it
    Vector3d boundingBox;

    static const Vector3d DEFAULT_ROTATE;
    static const Vector3d DEFAULT_SCALE;
    static const Vector3d DEFAULT_TRANSLATE;

    Vector3d rotate;
    Vector3d scale;
    Vector3d translate;

    bool isSelected;

    void drawBefore() const;
    void drawAfter() const;
};

#endif // APRILSOLID_H
