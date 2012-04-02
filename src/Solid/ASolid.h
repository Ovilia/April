#ifndef APRILSOLID_H
#define APRILSOLID_H

#include <QString>

#include "APrimitive.h"

class ASolid
{
public:
    enum BoolOperation {
        BO_PRIMITIVE = 0,
        BO_INTERSECTION,
        BO_UNION,
        BO_DIFFERENCE
    };

    ASolid(int primitiveID, APrimitive* primitive,
           const QString& name = "Solid");
    ASolid(ASolid* leftChild, ASolid* rightChild,
           BoolOperation operation, const QString& name = "Solid");
    ~ASolid();

    QString getName() const;
    void setName(const QString& name);

    void drawWire();
    void drawSolid();

    ASolid* getLeftChild();
    ASolid* getRightChild();
    BoolOperation getOperation();

    void setLeftChild(ASolid* leftChild);
    void setRightChild(ASolid* rightChild);
    void setOperation(BoolOperation operation);

private:
    QString name;

    ASolid* leftChild;
    ASolid* rightChild;
    BoolOperation operation;

    // used if is leaf
    APrimitive* primitive;
    // unique! used to identify different primitive, allocated by ModelManager
    // should not be changed within ASolid
    int primitiveID;
};

#endif // APRILSOLID_H
