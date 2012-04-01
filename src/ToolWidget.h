#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

#include "Solid/APrimitive.h"
#include "ViewManager.h"

namespace Ui {
class ToolWidget;
}

class ViewManager;

class ToolWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ToolWidget(ViewManager* viewManager, QWidget *parent = 0);
    ~ToolWidget();
    
private slots:
    void on_cubeButton_clicked(bool checked);

    void on_sphereButton_clicked(bool checked);

    void on_cylinderButton_clicked(bool checked);

    void on_coneButton_clicked(bool checked);

    void on_prismButton_clicked(bool checked);

    void on_pyramidButton_clicked(bool checked);

private:
    Ui::ToolWidget *ui;

    ViewManager* viewManager;

    // used when create primitive
    APrimitive::PrimitiveType createPrmType;
};

#endif // TOOLWIDGET_H
