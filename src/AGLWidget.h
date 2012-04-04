#ifndef AGLWIDGET_H
#define AGLWIDGET_H

#include <QtOpenGL/qgl.h>
#include <QMdiSubWindow>

#include "ModelManager.h"
#include "StateEnum.h"
#include "Vector3d.h"

class ModelManager;

class AGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit AGLWidget(ModelManager* modelManager, QWidget *parent = 0);
    ~AGLWidget();

    void setViewMode(StateEnum::ViewMode mode);
    StateEnum::ViewMode getViewMode();

    void zoomIn();
    void zoomOut();

    void rotateX();
    void rotateY();
    void rotateZ();

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    ModelManager* modelManager;

    StateEnum::ViewMode viewMode;

    // value of width / height
    double widthHeightRatio;

    Vector3d clearColor;

    // if drag mouse from left top corner to right top corner,
    // the view will scale twice as the former one.
    // drag distance is calculated by x+y
    // double scaleOnceRatio;

    // previous / new ortho size if zoom in once
    double zoomInRatio;
    // previous / new ortho size if zoom out once
    double zoomOutRatio;

    double orthoLeft;
    double orthoRight;
    double orthoBottom;
    double orthoTop;
    double orthoNear;
    double orthoFar;
    // view rotate, within [0, 360)
    double orthoXRotate;
    double orthoYRotate;
    double orthoZRotate;
    // angle of each rotate
    double rotateRatio;

    double viewPortX;
    double viewPortY;

    bool isMousePressed;
    short mousePressX, mousePressY;
    short mouseLastX, mouseLastY;

    // main xOz plain, used to draw scene center location
    double mainPlainSize;
    Vector3d mainPlainColor;
    void drawMainPlain();

    // x y z axis
    double axisLength;
    double arrowLength;
    void drawAxis();
};

#endif // AGLWIDGET_H
