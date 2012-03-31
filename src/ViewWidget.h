#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QMdiSubWindow>

#include "AGLWidget.h"
#include "ModelManager.h"

class ViewWidget : public QMdiSubWindow
{
public:
    ViewWidget(ModelManager* modelManager);
    ~ViewWidget();

    AGLWidget* getAglWidget();

private:
    AGLWidget* aglWidget;
};

#endif // VIEWWIDGET_H
