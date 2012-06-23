#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <map>

#include <QString>
#include <QWidget>

#include "ACreateDialog.h"
#include "ColorDialog.h"
#include "Solid/ASolid.h"
#include "Solid/APrimitive.h"
#include "MainWindow.h"
#include "TextureDialog.h"

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
    void on_cubeButton_clicked();

    void on_sphereButton_clicked();

    void on_cylinderButton_clicked();

    void on_coneButton_clicked();

    void on_prismButton_clicked();

    void on_pyramidButton_clicked();

    void on_primitiveBox_currentIndexChanged(const QString &arg1);

    void on_okButton_clicked();

    void on_positionBtn_clicked();

    void on_solidBox_currentIndexChanged(const QString &arg1);

    void on_solidBtn_clicked();

    void on_boolBtn_clicked();

    void on_deleteSolidButton_clicked();

    void on_ungroupSolidButton_clicked();

    void on_deletePmtButton_clicked();

    void on_tabWidget_currentChanged(QWidget *arg1);

    void on_visiblePmtBtn_clicked();

    void on_visibleSldBtn_clicked();

    void on_colorButton_clicked();

    void on_textButton_clicked();

    void on_ambientButton_clicked();

    void on_litOkButton_clicked();

    void on_lightBox_currentIndexChanged(const QString &arg1);

    void on_hideLight_clicked();

    void on_deleteLight_clicked();

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
    Lighting* selectedLighting;

    void updateLightBox();
    void updateLightCanOpen();

    // protect from selecting solid when clearing box
    bool protectSelectMode;

    // set ungroup and delete button enabling according to selected solid
    // enabled if is root
    void checkUngroupDelete();

    class ColorDialog* colorDialog;
    class TextureDialog* textureDialog;
};

#endif // TOOLWIDGET_H
