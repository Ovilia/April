#include "ArcBall.h"

#include <qmath.h>
#include <QtOpenGL>

#define PI 3.14159265

ArcBall::ArcBall(int screenWidth, int screenHeight) :
    width(screenWidth),
    height(screenHeight),
    newRot(4),
    oldRot(4),
    curRot(4),
    isMousePressed(false),
    mousePressX(0),
    mousePressY(0),
    mouseCurX(0),
    mouseCurY(0),
    pressVector()
{
    oldRot.setIdentity();
    newRot.setIdentity();
    curRot.setIdentity();
}

void ArcBall::resize(int screenWidth, int screenHeight)
{
    width = screenWidth;
    height = screenHeight;
}

void ArcBall::doRotate()
{
    glMultMatrixd(curRot.getPointer());
}

void ArcBall::mousePress(int x, int y)
{
    isMousePressed = true;
    mousePressX = x;
    mousePressY = y;
    pressVector = screenToArcBall(x, y);
}

void ArcBall::mouseMove(int x, int y)
{
    if (isMousePressed) {
        mouseCurX = x;
        mouseCurY = y;

        // vector on arc ball of current mouse position
        Vector3d curVector = screenToArcBall(x, y);
        // rotate axis and angle(in radian)
        // from press position to current position
        Vector3d axis = getRotateAxis(pressVector, curVector);
        double angle = getRotateAngle(pressVector, curVector);

        // rotate matrix from origin to current
        newRot = getRotateMatrix(angle, axis);
        curRot = oldRot.multiply(newRot);
    }
}

void ArcBall::mouseRelease()
{
    isMousePressed = false;
    oldRot = curRot;
}

Vector3d ArcBall::screenToArcBall(int x, int y)
{
    Vector3d vec;
    if (width == 0 || height == 0)
    {
        return vec;
    }

    // map (x, y) to [-1.0, 1.0]
    vec.x = 2.0 * x / width - 1.0;
    // y is set to be opposite since the coordinates of screen and
    // opengl are different
    vec.y = 1.0 - 2.0 * y / height;

    double square = vec.x * vec.x + vec.y * vec.y;
    if (square <= 1.0) {
        // if (x, y) is within the circle of radius 1
        // calculate z so that the modulus of vector is 1
        vec.z = qSqrt(1.0 - square);
    } else {
        // if is out of the circle, do nomarlization
        // this vector is the nearest position on the circle
        // so that z is 0
        double length = qSqrt(square);
        vec.x /= length;
        vec.y /= length;
        vec.z = 0.0;
    }
    return vec;
}

double ArcBall::getRotateAngle(Vector3d vec1, Vector3d vec2)
{
    return qAcos(vec1.dotProduct(vec2));
}

Vector3d ArcBall::getRotateAxis(Vector3d vec1, Vector3d vec2)
{
    return vec1.crossProduct(vec2);
}

MatrixD ArcBall::getRotateMatrix(double angle, Vector3d axis)
{
    axis.normalize();

    // 4x4 rotate matrix
    MatrixD result(4);

    double cos = qCos(angle);
    double sin = qSin(angle);
    result.setElement(0, cos + axis.x * axis.x * (1.0 - cos));
    result.setElement(4, axis.x * axis.y * (1.0 - cos) - axis.z * sin);
    result.setElement(8, axis.x * axis.z * (1.0 - cos) + axis.y * sin);
    result.setElement(12, 0.0);
    result.setElement(1, axis.y * axis.x * (1.0 - cos) + axis.z * sin);
    result.setElement(5, cos + axis.y * axis.y * (1.0 - cos));
    result.setElement(9, axis.y * axis.z * (1.0 - cos) - axis.x * sin);
    result.setElement(13, 0.0);
    result.setElement(2, axis.z * axis.x * (1.0 - cos) - axis.y * sin);
    result.setElement(6, axis.z * axis.y * (1.0 - cos) + axis.x * sin);
    result.setElement(10, cos + axis.z * axis.z * (1.0 - cos));
    result.setElement(14, 0.0);
    result.setElement(3, 0.0);
    result.setElement(7, 0.0);
    result.setElement(11, 0.0);
    result.setElement(15, 1.0);
    return result;
}
