#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>

#include "CreateDialog.h"
#include "Solid/APrimitive.h"
#include "MainWindow.h"

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
    CreateDialog* createDialog;
    void showCreateDialog();

    // used when create primitive
    APrimitive::PrimitiveType createPrmType;
};

#endif // TOOLWIDGET_H
