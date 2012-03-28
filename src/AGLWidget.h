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

protected:
    // opengl related
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    ModelManager* modelManager;
};

#endif // AGLWIDGET_H
