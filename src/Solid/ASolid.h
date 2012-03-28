#ifndef APRILSOLID_H
#define APRILSOLID_H

#include "APrimitive.h"

class ASolid : public APrimitive
{
public:
    enum BoolOperation {
        BO_NONE,
        BO_INTERSECTION,
        BO_UNION,
        BO_DIFFERENCE
    };

    ASolid(ASolid* leftChild, ASolid* rightChild = 0,
           BoolOperation operation = BO_NONE);
    ~ASolid();

    virtual void drawWire();
    virtual void drawSolid();

    ASolid* getLeftChild();
    ASolid* getRightChild();
    BoolOperation getOperation();

    void setLeftChild(ASolid* leftChild);
    void setRightChild(ASolid* rightChild);
    void setOperation(BoolOperation operation);

private:
    ASolid* leftChild;
    ASolid* rightChild;
    BoolOperation operation;
};

#endif // APRILSOLID_H
