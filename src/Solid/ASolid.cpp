#include "ASolid.h"

#include <qmath.h>
#include <QtOpenGL>

const QString ASolid::BOOL_OPERATION_NAME[BOOL_OPERATION_COUNT] = {
    "none", "intersection", "union", "difference"
};

const Vector3d ASolid::DEFAULT_ROTATE = Vector3d(0.0, 0.0, 0.0);
const Vector3d ASolid::DEFAULT_SCALE = Vector3d(1.0, 1.0, 1.0);
const Vector3d ASolid::DEFAULT_TRANSLATE = Vector3d(0.0, 0.0, 0.0);

const Vector3d ASolid::SELECTED_COLOR = Vector3d(1.0, 0.8, 0.2);

ASolid::ASolid(ASolid* leftChild, ASolid* rightChild,
               BoolOperation operation, const QString& name) :
    name(name),
    leftChild(leftChild),
    rightChild(rightChild),
    operation(operation),
    parent(0),
    primitive(0),
    rotate(DEFAULT_ROTATE),
    scale(DEFAULT_SCALE),
    translate(DEFAULT_TRANSLATE),
    isSelected(false),
    isVisible(true)
{
    // set bounding box
    // TODO: Not considering translate yet
    Vector3d leftMin = leftChild->getBoundingBoxMin();
    Vector3d leftMax = leftChild->getBoundingBoxMax();
    Vector3d rightMin = rightChild->getBoundingBoxMin();
    Vector3d rightMax = rightChild->getBoundingBoxMax();
    boundingBoxMin.x = qMin(leftMin.x, rightMin.x);
    boundingBoxMin.y = qMin(leftMin.y, rightMin.y);
    boundingBoxMin.z = qMin(leftMin.z, rightMin.z);
    boundingBoxMax.x = qMax(leftMax.x, rightMax.x);
    boundingBoxMax.y = qMax(leftMax.y, rightMax.y);
    boundingBoxMax.z = qMax(leftMax.z, rightMax.z);
}

ASolid::ASolid(APrimitive* primitive, const QString& name) :
    name(name),
    leftChild(0),
    rightChild(0),
    operation(BO_PRIMITIVE),
    parent(0),
    primitive(primitive),
    rotate(0.0, 0.0, 0.0),
    scale(1.0, 1.0, 1.0),
    translate(0.0, 0.0, 0.0),
    isSelected(false),
    isVisible(true)
{
    boundingBoxMin = primitive->getBoundingBoxMin();
    boundingBoxMax = primitive->getBoundingBoxMax();
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

ASolid* ASolid::getParent() const
{
    return parent;
}

void ASolid::setParenet(ASolid *parent)
{
    this->parent = parent;
}

bool ASolid::isRoot() const
{
    if (parent == 0) {
        return true;
    } else {
        return false;
    }
}

bool ASolid::isLeave() const
{
    if (leftChild == 0 && rightChild == 0) {
        return true;
    } else {
        return false;
    }
}

bool ASolid::hasDescent(ASolid *descent) const
{
    if (isLeave()) {
        return false;
    } else {
        if (leftChild == descent || rightChild == descent) {
            return true;
        } else {
            return leftChild->hasDescent(descent) ||
                    rightChild->hasDescent(descent);
        }
    }
}

void ASolid::drawBefore() const
{
    glPushMatrix();
    glRotated(rotate.z, 0.0, 0.0, 1.0);
    glRotated(rotate.y, 0.0, 1.0, 0.0);
    glRotated(rotate.x, 1.0, 0.0, 0.0);
    glTranslated(translate.x, translate.y, translate.z);
    glScaled(scale.x, scale.y, scale.z);
}

void ASolid::drawWire() const
{
    if (!isVisible) {
        return;
    }

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

void ASolid::drawSolid() const
{
    if (!isVisible) {
        return;
    }

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

void ASolid::drawAfter() const
{
    glPopMatrix();
}

void ASolid::drawBoundingBox() const
{
    glColor3d(SELECTED_COLOR.x, SELECTED_COLOR.y, SELECTED_COLOR.z);
    glBegin(GL_LINE_STRIP);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
    glEnd();
}

ASolid* ASolid::getLeftChild() const
{
    return leftChild;
}

ASolid* ASolid::getRightChild() const
{
    return rightChild;
}

ASolid::BoolOperation ASolid::getOperation() const
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

APrimitive* ASolid::getPrimitive() const
{
    return primitive;
}

Vector3d ASolid::getBoundingBoxMin() const
{
    return boundingBoxMin;
}

Vector3d ASolid::getBoundingBoxMax() const
{
    return boundingBoxMax;
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

void ASolid::setScale(const Vector3d &scale)
{
    this->scale = scale;
}

void ASolid::setRotate(const Vector3d &rotate)
{
    this->rotate = rotate;
}

void ASolid::setTranslate(const Vector3d &translate)
{
    this->translate = translate;
}

bool ASolid::getSelected() const
{
    return isSelected;
}

void ASolid::setSelected(const bool value, const bool usePmtColor)
{
    isSelected = value;
    if (operation == BO_PRIMITIVE) {
        primitive->setSelected(value, usePmtColor);
    } else {
        leftChild->setSelected(value, false);
        rightChild->setSelected(value, false);
    }
}

QString ASolid::toString() const
{
    // solid name
    QString str = QString("solid \"") + name + QString("\"\n");

    // primitive, children and operation
    if (primitive) {
        // leave solid
        str += QString("primitive=") + primitive->getName() + QString("\n");
    } else {
        if (leftChild) {
            str += QString("left=") + leftChild->getName() + QString("\n");
        }
        if (rightChild) {
            str += QString("right=") + rightChild->getName() + QString("\n");
        }
        str += BOOL_OPERATION_NAME[operation] + QString("\n");
    }

    // transform parameter
    if (rotate != DEFAULT_ROTATE) {
        str += QString("rotate={") + QString::number(rotate.x) +
                QString(", ") + QString::number(rotate.y) + QString(", ") +
                QString::number(rotate.z) + QString("}\n");
    }
    if (scale != DEFAULT_SCALE) {
        str += QString("scale={") + QString::number(scale.x) +
                QString(", ") + QString::number(scale.y) + QString(", ") +
                QString::number(scale.z) + QString("}\n");
    }
    if (translate != DEFAULT_TRANSLATE) {
        str += QString("translate={") + QString::number(translate.x) +
                QString(", ") + QString::number(translate.y) + QString(", ") +
                QString::number(translate.z) + QString("}\n");
    }
    str += QString("\n");
    return str;
}

bool ASolid::getVisible() const
{
    return isVisible;
}

void ASolid::setVisible(const bool visible)
{
    isVisible = visible;
}
