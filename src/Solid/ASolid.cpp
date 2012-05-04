#include <QtOpenGL>

#include "ASolid.h"

ASolid::ASolid(ASolid* leftChild, ASolid* rightChild,
               BoolOperation operation, const QString& name) :
    name(name),
    leftChild(leftChild),
    rightChild(rightChild),
    operation(operation),
    parent(0),
    primitive(0),
    rotate(0.0, 0.0, 0.0),
    scale(1.0, 1.0, 1.0),
    translate(0.0, 0.0, 0.0),
    isSelected(false)
{
    // TODO: set bounding box here
}

ASolid::ASolid(unsigned int primitiveID, APrimitive* primitive,
               const QString& name) :
    name(name),
    leftChild(0),
    rightChild(0),
    operation(BO_PRIMITIVE),
    parent(0),
    primitive(primitive),
    primitiveID(primitiveID),
    rotate(0.0, 0.0, 0.0),
    scale(1.0, 1.0, 1.0),
    translate(0.0, 0.0, 0.0),
    isSelected(false)
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

ASolid* ASolid::getParent()
{
    return parent;
}

void ASolid::setParenet(ASolid *parent)
{
    this->parent = parent;
}

bool ASolid::isRoot()
{
    if (parent == 0) {
        return true;
    } else {
        return false;
    }
}

bool ASolid::isLeave()
{
    if (leftChild == 0 && rightChild == 0) {
        return true;
    } else {
        return false;
    }
}

void ASolid::drawBefore()
{
    glPushMatrix();

    glRotated(rotate.x, 1.0, 0.0, 0.0);
    glRotated(rotate.y, 0.0, 1.0, 0.0);
    glRotated(rotate.z, 0.0, 0.0, 1.0);
    glScaled(scale.x, scale.y, scale.z);
    glTranslated(translate.x, translate.y, translate.z);
}

void ASolid::drawWire()
{
    drawBefore();

    switch (operation) {
    case BO_PRIMITIVE:
        primitive->drawWire();
        break;

    case BO_UNION:
        leftChild->drawWire();
        rightChild->drawWire();
        break;

    default:
        break;
    }

    drawAfter();
}

void ASolid::drawSolid()
{
    drawBefore();

    switch (operation) {
    case BO_PRIMITIVE:
        primitive->drawSolid();
        break;

    case BO_UNION:
        leftChild->drawSolid();
        rightChild->drawSolid();
        break;

    default:
        break;
    }

    drawAfter();
}

void ASolid::drawAfter()
{
    glPopMatrix();
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
