#include <map>

#include <QString>

#include "ToolWidget.h"
#include "ui_ToolWidget.h"

#include "ModelManager.h"
#include "Solid/ASolid.h"

ToolWidget::ToolWidget(MainWindow* mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget),
    mainWindow(mainWindow),
    createDialog(0),
    createPrmType(APrimitive::PT_NONE)
{
    ui->setupUi(this);
}

ToolWidget::~ToolWidget()
{
    delete ui;
    if (createDialog) {
        delete createDialog;
    }
}

void ToolWidget::showCreateDialog()
{
    // TODO: currently use CreateDialog to create primitives,
    // improve later with dragging
    if (!createDialog) {
        createDialog = new ACreateDialog(createPrmType,
                                        mainWindow->getModelManager(),
                                        this);
    } else {
        createDialog->changePrimitive(createPrmType);
    }
    createDialog->exec();
}

void ToolWidget::on_cubeButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_CUBE;
//    if (checked) {
//        // uncheck other buttons
//        ui->sphereButton->setChecked(false);
//        ui->cylinderButton->setChecked(false);
//        ui->coneButton->setChecked(false);
//        ui->prismButton->setChecked(false);
//        ui->pyramidButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::on_sphereButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_SPHERE;
//    if (checked) {
//        // uncheck other buttons
//        ui->cubeButton->setChecked(false);
//        ui->cylinderButton->setChecked(false);
//        ui->coneButton->setChecked(false);
//        ui->prismButton->setChecked(false);
//        ui->pyramidButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::on_cylinderButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_CYLINDER;
//    if (checked) {
//        // uncheck other buttons
//        ui->sphereButton->setChecked(false);
//        ui->cubeButton->setChecked(false);
//        ui->coneButton->setChecked(false);
//        ui->prismButton->setChecked(false);
//        ui->pyramidButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::on_coneButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_CONE;
//    if (checked) {
//        // uncheck other buttons
//        ui->sphereButton->setChecked(false);
//        ui->cylinderButton->setChecked(false);
//        ui->cubeButton->setChecked(false);
//        ui->prismButton->setChecked(false);
//        ui->pyramidButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::on_prismButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_PRISM;
//    if (checked) {
//        // uncheck other buttons
//        ui->sphereButton->setChecked(false);
//        ui->cylinderButton->setChecked(false);
//        ui->coneButton->setChecked(false);
//        ui->cubeButton->setChecked(false);
//        ui->pyramidButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::on_pyramidButton_clicked(bool checked)
{
    createPrmType = APrimitive::PT_PYRAMID;
//    if (checked) {
//        // uncheck other buttons
//        ui->sphereButton->setChecked(false);
//        ui->cylinderButton->setChecked(false);
//        ui->coneButton->setChecked(false);
//        ui->prismButton->setChecked(false);
//        ui->cubeButton->setChecked(false);
//    } else {
//        createPrmType = APrimitive::PT_NONE;
//    }
    showCreateDialog();
}

void ToolWidget::updateModelBox()
{
    ui->modelBox->clear();
    ModelManager* modelManager = mainWindow->getModelManager();
    map<QString, ASolid*>* solid = modelManager->getSolidMap();
    map<QString, ASolid*>::iterator iter;
    for (iter = solid->begin(); iter != solid->end(); ++iter) {
        ui->modelBox->addItem(iter->first);
    }
}
