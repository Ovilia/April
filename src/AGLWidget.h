#ifndef AGLWIDGET_H
#define AGLWIDGET_H

#include <QtOpenGL/qgl.h>
#include <QMdiSubWindow>

#include "ModelManager.h"

class AGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit AGLWidget(ModelManager* modelManager, QWidget *parent = 0);
    ~AGLWidget();

    enum DrawStyle {
        DS_NONE = 0x0,
        DS_WIRE = 0x1,
        DS_SOLID = 0x2
    };

    enum DrawColor {
        // RGB color, used only when it is in special state (e.g.: selected)
        DS_DEFAULT = 0x000000,
        DS_SELECTED = 0xFFFFFF
    };

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    ModelManager* modelManager;

    DrawStyle drawStyle;
};

#endif // AGLWIDGET_H
