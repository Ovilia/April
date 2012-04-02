#ifndef AGLWIDGET_H
#define AGLWIDGET_H

#include <QtOpenGL/qgl.h>
#include <QMdiSubWindow>

#include "ModelManager.h"
#include "Vector3d.h"

class AGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit AGLWidget(ModelManager* modelManager, QWidget *parent = 0);
    ~AGLWidget();

    enum DrawColor {
        // RGB color, used only when it is in special state (e.g.: selected)
        DS_DEFAULT = 0x000000,
        DS_SELECTED = 0xFFFFFF
    };

    enum ViewMode {
        VM_NONE = 0,
        VM_MOVE,
//        VM_ZOOM_IN,
//        VM_ZOOM_OUT,
        VM_ROTATE,
        VM_CREATE
    };

    void setViewMode(ViewMode mode);
    ViewMode getViewMode();

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

    ViewMode viewMode;

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
