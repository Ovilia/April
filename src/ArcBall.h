#ifndef ARCBALL_H
#define ARCBALL_H

#include "MatrixD.h"
#include "Vector3d.h"

class ArcBall
{
public:
    ArcBall(int screenWidth, int screenHeight);

    void resize(int screenWidth, int screenHeight);

    void mousePress(int x, int y);
    void mouseRelease();
    void mouseMove(int x, int y);

    void doRotate();

private:
    int width;
    int height;

    // 4x4 rotate matrix since mouse pressed to current
    MatrixD newRot;
    // 4x4 rotate matrix since origin to mouse pressed
    MatrixD oldRot;
    // 4x4 rotate matrix since origin to current
    MatrixD curRot;

    bool isMousePressed;
    int mousePressX;
    int mousePressY;
    int mouseCurX;
    int mouseCurY;

    Vector3d pressVector;

    // map a point on screen to a vector on the arc ball
    Vector3d screenToArcBall(int x, int y);
    // get rotate angle(in radian) from two normalized vectors
    double getRotateAngle(Vector3d vec1, Vector3d vec2);
    // get rotate axis from two normalized vectors
    Vector3d getRotateAxis(Vector3d vec1, Vector3d vec2);
    // get rotate matrix from rotate angle and axis
    MatrixD getRotateMatrix(double angle, Vector3d axis);
};

#endif // ARCBALL_H
