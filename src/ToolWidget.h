#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

#include "ACreateDialog.h"
#include "Solid/APrimitive.h"
#include "MainWindow.h"

class ACreateDialog;

namespace Ui {
class ToolWidget;
}

class MainWindow;

class ToolWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ToolWidget(MainWindow* mainWindow, QWidget *parent = 0);
    ~ToolWidget();

    void updateModelBox();
    
private slots:
    void on_cubeButton_clicked(bool checked);

    void on_sphereButton_clicked(bool checked);

    void on_cylinderButton_clicked(bool checked);

    void on_coneButton_clicked(bool checked);

    void on_prismButton_clicked(bool checked);

    void on_pyramidButton_clicked(bool checked);

private:
    Ui::ToolWidget *ui;

    MainWindow* mainWindow;

    // currently used for create primitives
    ACreateDialog* createDialog;
    void showCreateDialog();

    // used when create primitive
    APrimitive::PrimitiveType createPrmType;
};

#endif // TOOLWIDGET_H
