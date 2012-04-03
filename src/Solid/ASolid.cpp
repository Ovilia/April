#include "ASolid.h"

ASolid::ASolid(ASolid* leftChild, ASolid* rightChild,
               BoolOperation operation, const QString& name) :
    name(name),
    leftChild(leftChild),
    rightChild(rightChild),
    operation(operation),
    primitive(0)
{
    // TODO: set bounding box here
}

ASolid::ASolid(unsigned int primitiveID, APrimitive* primitive,
               const QString& name) :
    name(name),
    leftChild(0),
    rightChild(0),
    operation(BO_PRIMITIVE),
    primitive(primitive),
    primitiveID(primitiveID)
{
    boundingBox = primitive->getBoundingBox();
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
        primitive->drawWire();
    }
}

void ASolid::drawSolid()
{
    if (operation == BO_PRIMITIVE) {
        primitive->drawSolid();
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

APrimitive* ASolid::getPrimitive()
{
    return primitive;
}

Vector3d ASolid::getBoundingBox()
{
    return boundingBox;
}

Vector3d ASolid::getRotate() const
{
    return rotate;
}

Vector3d ASolid::getScale() const
{
    return scale;
}

Vector3d ASolid::getTranslate() const
{
    return translate;
}

void ASolid::setXRotate(const double rotate)
{
    this->rotate.x = rotate;
}

void ASolid::setYRotate(const double rotate)
{
    this->rotate.y = rotate;
}

void ASolid::setZRotate(const double rotate)
{
    this->rotate.z = rotate;
}

void ASolid::setXScale(const double scale)
{
    this->scale.x = scale;
}

void ASolid::setYScale(const double scale)
{
    this->scale.y = scale;
}

void ASolid::setZScale(const double scale)
{
    this->scale.z = scale;
}

void ASolid::setXTranslate(const double translate)
{
    this->translate.x = translate;
}

void ASolid::setYTranslate(const double translate)
{
    this->translate.y = translate;
}

void ASolid::setZTranslate(const double translate)
{
    this->translate.z = translate;
}

bool ASolid::getSelected() const
{
    return isSelected;
}

void ASolid::setSelected(const bool value)
{
    isSelected = value;
}
