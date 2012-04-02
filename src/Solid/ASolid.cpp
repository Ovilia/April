#include "ASolid.h"

ASolid::ASolid(ASolid* leftChild, ASolid* rightChild,
               BoolOperation operation, const QString& name) :
    leftChild(leftChild),
    rightChild(rightChild),
    operation(operation),
    primitive(0)
{
}

ASolid::ASolid(int primitiveID, APrimitive* primitive, const QString& name) :
    leftChild(0),
    rightChild(0),
    operation(BO_PRIMITIVE),
    primitive(primitive),
    primitiveID(primitiveID)
{

}

ASolid::~ASolid()
{

}

QString ASolid::getName() const
{
    return name;
}

void ASolid::setName(const QString& name)
{
    this->name = name;
}

void ASolid::drawWire()
{
    if (operation == BO_PRIMITIVE) {
        leftChild->drawWire();
    }
}

void ASolid::drawSolid()
{
    if (operation == BO_PRIMITIVE) {
        leftChild->drawSolid();
    }
}

ASolid* ASolid::getLeftChild()
{
    return leftChild;
}

ASolid* ASolid::getRightChild()
{
    return rightChild;
}

ASolid::BoolOperation ASolid::getOperation()
{
    return operation;
}

void ASolid::setLeftChild(ASolid* leftChild)
{
    this->leftChild = leftChild;
}

void ASolid::setRightChild(ASolid* rightChild)
{
    this->rightChild = rightChild;
}

void ASolid::setOperation(BoolOperation operation)
{
    this->operation = operation;
}
