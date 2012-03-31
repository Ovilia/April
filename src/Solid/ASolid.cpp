#include "ASolid.h"

ASolid::ASolid(ASolid* leftChild, ASolid* rightChild,
               BoolOperation operation) :
    leftChild(leftChild),
    rightChild(rightChild),
    operation(operation)
{
}

ASolid::~ASolid()
{

}

void ASolid::drawWire()
{

}

void ASolid::drawSolid()
{
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
