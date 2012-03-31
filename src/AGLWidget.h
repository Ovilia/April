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
        VM_ZOOM_IN,
        VM_ZOOM_OUT,
        VM_ROTATE
    };

    void setViewMode(ViewMode mode);
    ViewMode getViewMode();

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void enterEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    ModelManager* modelManager;

    ViewMode viewMode;

    // value of width / height
    double widthHeightRatio;

    // if drag mouse from left top corner to right top corner,
    // the view will scale twice as the former one.
    // drag distance is calculated by x+y
    double scaleOnceRatio;

    Vector3d lookEye;
    Vector3d lookCenter;
    Vector3d lookUp;

    double orthoLeft;
    double orthoRight;
    double orthoTop;
    double orthoBottom;
    double orthoNear;
    double orthoFar;

    double viewPortX;
    double viewPortY;

    bool isMousePressed;
    short mousePressX, mousePressY;
    short mouseLastX, mouseLastY;
};

#endif // AGLWIDGET_H
