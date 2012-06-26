#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QMdiSubWindow>

#include "AGLWidget.h"
#include "ModelManager.h"

class AGLWidget;
class ModelManager;

class ViewWidget : public QMdiSubWindow
{
public:
    ViewWidget(ModelManager* modelManager);
    ~ViewWidget();

    AGLWidget* getAglWidget();

    void viewFront();
    void viewLeft();
    void viewTop();

    void closeEvent(QCloseEvent *closeEvent);

private:
    AGLWidget* aglWidget;

    ModelManager* modelManager;
};

#endif // VIEWWIDGET_H
