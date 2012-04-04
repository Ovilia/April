#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <map>

#include <QString>
#include <QWidget>

#include "ACreateDialog.h"
#include "Solid/ASolid.h"
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

    void on_modelBox_currentIndexChanged(const QString &arg1);

    void on_okButton_clicked();

    void on_positionBtn_clicked();

    void on_solidBox_currentIndexChanged(const QString &arg1);

    void on_solidBtn_clicked();

    void on_boolBtn_clicked();

private:
    Ui::ToolWidget *ui;

    MainWindow* mainWindow;

    // currently used for create primitives
    ACreateDialog* createDialog;
    void showCreateDialog();

    // used when create primitive
    APrimitive::PrimitiveType createPrmType;

    map<QString, ASolid*>* solidMap;
    map<QString, APrimitive*>* primitiveMap;

    ASolid* selectedSolid;
    APrimitive* selectedPrimitive;
};

#endif // TOOLWIDGET_H
