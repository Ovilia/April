#include "ToolWidget.h"
#include "ui_ToolWidget.h"

#include <map>

#include <QMessageBox>
#include <QString>

#include "ModelManager.h"
#include "Solid/ASolid.h"
#include "Vector3d.h"

ToolWidget::ToolWidget(MainWindow* mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget),

    mainWindow(mainWindow),

    createDialog(0),
    createPrmType(APrimitive::PT_NONE),

    selectedSolid(0),
    selectedPrimitive(0),

    protectSelectMode(false),

    colorDialog(0),
    matDialog(0)
{
    ui->setupUi(this);
    solidMap = mainWindow->getModelManager()->getSolidMap();
    primitiveMap = mainWindow->getModelManager()->getPrimitiveMap();
}

ToolWidget::~ToolWidget()
{
    delete ui;
    if (createDialog) {
        delete createDialog;
    }
    if (colorDialog) {
        delete colorDialog;
    }
    if (matDialog) {
        delete matDialog;
    }
}

void ToolWidget::showCreateDialog()
{
    if (!createDialog) {
        createDialog = new ACreateDialog(createPrmType,
                                         mainWindow,
                                         this,
                                         this);
    } else {
        createDialog->changePrimitive(createPrmType);
    }
    createDialog->exec();
}

void ToolWidget::on_cubeButton_clicked()
{
    createPrmType = APrimitive::PT_CUBE;
    showCreateDialog();
}

void ToolWidget::on_sphereButton_clicked()
{
    createPrmType = APrimitive::PT_SPHERE;
    showCreateDialog();
}

void ToolWidget::on_cylinderButton_clicked()
{
    createPrmType = APrimitive::PT_CYLINDER;
    showCreateDialog();
}

void ToolWidget::on_coneButton_clicked()
{
    createPrmType = APrimitive::PT_CONE;
    showCreateDialog();
}

void ToolWidget::on_prismButton_clicked()
{
    createPrmType = APrimitive::PT_PRISM;
    showCreateDialog();
}

void ToolWidget::on_pyramidButton_clicked()
{
    createPrmType = APrimitive::PT_PYRAMID;
    showCreateDialog();
}

void ToolWidget::updateModelBox()
{
    // update primitiveBox according to primitiveMap
    ui->primitiveBox->clear();
    map<QString, APrimitive*>::iterator iter;
    for (iter = primitiveMap->begin(); iter != primitiveMap->end(); ++iter) {
        ui->primitiveBox->addItem(iter->first);
    }

    // update boolBox and solidBox according to solidMap
    protectSelectMode = true;
    ui->solidBox->clear();
    ui->boolBox1->clear();
    ui->boolBox2->clear();
    protectSelectMode = false;

    map<QString, ASolid*>::iterator iter2;
    for (iter2 = solidMap->begin(); iter2 != solidMap->end(); ++iter2) {
        // every solid can do bool operation
        ui->boolBox1->addItem(iter2->first);
        ui->boolBox2->addItem(iter2->first);
        if (!iter2->second->isLeave())
        {
            // leave solid can't be delete itself,
            // and transform should be done in primitive part
            ui->solidBox->addItem(iter2->first);
        }
    }
    checkUngroupDelete();

    // set primitiveTab enabled according to count of primitiveBox
    if (ui->primitiveBox->count() > 0) {
        ui->primitiveTab->setEnabled(true);
    } else {
        ui->primitiveTab->setEnabled(false);
    }

    // set solidTab enabled according to count of solidBox
    if (ui->solidBox->count() > 0) {
        ui->solidTab->setEnabled(true);
    } else {
        ui->solidTab->setEnabled(false);
    }

    // set bool operation enabled according to count of boolBox
    if (ui->boolBox1->count() > 1) {
        ui->boolPage->setEnabled(true);
        ui->boolBtn->setEnabled(true);
    } else {
        ui->boolPage->setEnabled(false);
    }
}

void ToolWidget::on_primitiveBox_currentIndexChanged(const QString &arg1)
{
    map<QString, APrimitive*>::iterator iter = primitiveMap->find(arg1);
    if (iter == primitiveMap->end()) {
        return;
    }

    selectedPrimitive = iter->second;

    ASolid* solid = mainWindow->getModelManager()->
            getSolidFromPmt(selectedPrimitive);
    if (solid) {
        // set delete primitive enabled
        if (solid->isRoot()) {
            ui->deletePmtButton->setEnabled(true);
        } else {
            ui->deletePmtButton->setEnabled(false);
        }

        // set selected primitive
        if (!protectSelectMode) {
            mainWindow->getModelManager()->selectSolid(solid);
            mainWindow->getViewManager()->repaintAll();
        }

        ui->visiblePmtBtn->setChecked(solid->getVisible());
    }

    Vector3d scale = selectedPrimitive->getScale();
    ui->xScaleSpin->setValue(scale.x);
    ui->yScaleSpin->setValue(scale.y);
    ui->zScaleSpin->setValue(scale.z);
    Vector3d rotate = selectedPrimitive->getRotate();
    ui->xRotateSpin->setValue(rotate.x);
    ui->yRotateSpin->setValue(rotate.y);
    ui->zRotateSpin->setValue(rotate.z);
    Vector3d trans = selectedPrimitive->getTranslate();
    ui->xTransSpin->setValue(trans.x);
    ui->yTransSpin->setValue(trans.y);
    ui->zTransSpin->setValue(trans.z);

    switch (selectedPrimitive->getType()) {
    case APrimitive::PT_CONE:
    {
        ACone* cone = (ACone*)selectedPrimitive;
        ui->heightSpin->setValue(cone->getHeight());
        ui->radiusSpin->setValue(cone->getRadius());
        ui->slicesSpin->setValue(cone->getSlices());

        ui->widthSpin->setVisible(false);
        ui->heightSpin->setVisible(true);
        ui->depthSpin->setVisible(false);
        ui->radiusSpin->setVisible(true);
        ui->lengthSpin->setVisible(false);
        ui->sideSpin->setVisible(false);
        ui->slicesSpin->setVisible(true);
        ui->stacksSpin->setVisible(false);
        ui->widthLabel->setVisible(false);
        ui->heightLabel->setVisible(true);
        ui->depthLabel->setVisible(false);
        ui->radiusLabel->setVisible(true);
        ui->lengthLabel->setVisible(false);
        ui->sideLabel->setVisible(false);
        ui->slicesLabel->setVisible(true);
        ui->stacksLabel->setVisible(false);
    }
        break;

    case APrimitive::PT_CUBE:
    {
        ACube* cube = (ACube*)selectedPrimitive;
        ui->widthSpin->setValue(cube->getWidth());
        ui->heightSpin->setValue(cube->getHeight());
        ui->depthSpin->setValue(cube->getDepth());

        ui->widthSpin->setVisible(true);
        ui->heightSpin->setVisible(true);
        ui->depthSpin->setVisible(true);
        ui->radiusSpin->setVisible(false);
        ui->lengthSpin->setVisible(false);
        ui->sideSpin->setVisible(false);
        ui->slicesSpin->setVisible(false);
        ui->stacksSpin->setVisible(false);
        ui->widthLabel->setVisible(true);
        ui->heightLabel->setVisible(true);
        ui->depthLabel->setVisible(true);
        ui->radiusLabel->setVisible(false);
        ui->lengthLabel->setVisible(false);
        ui->sideLabel->setVisible(false);
        ui->slicesLabel->setVisible(false);
        ui->stacksLabel->setVisible(false);
    }
        break;

    case APrimitive::PT_CYLINDER:
    {
        ACylinder* cylinder = (ACylinder*)selectedPrimitive;
        ui->heightSpin->setValue(cylinder->getHeight());
        ui->radiusSpin->setValue(cylinder->getRadius());
        ui->slicesSpin->setValue(cylinder->getSlices());

        ui->widthSpin->setVisible(false);
        ui->heightSpin->setVisible(true);
        ui->depthSpin->setVisible(false);
        ui->radiusSpin->setVisible(true);
        ui->lengthSpin->setVisible(false);
        ui->sideSpin->setVisible(false);
        ui->slicesSpin->setVisible(true);
        ui->stacksSpin->setVisible(false);
        ui->widthLabel->setVisible(false);
        ui->heightLabel->setVisible(true);
        ui->depthLabel->setVisible(false);
        ui->radiusLabel->setVisible(true);
        ui->lengthLabel->setVisible(false);
        ui->sideLabel->setVisible(false);
        ui->slicesLabel->setVisible(true);
        ui->stacksLabel->setVisible(false);
    }
        break;

    case APrimitive::PT_PRISM:
    {
        APrism* prism = (APrism*)selectedPrimitive;
        ui->lengthSpin->setValue(prism->getLength());
        ui->sideSpin->setValue(prism->getSideLength());

        ui->widthSpin->setVisible(false);
        ui->heightSpin->setVisible(false);
        ui->depthSpin->setVisible(false);
        ui->radiusSpin->setVisible(false);
        ui->lengthSpin->setVisible(true);
        ui->sideSpin->setVisible(true);
        ui->slicesSpin->setVisible(false);
        ui->stacksSpin->setVisible(false);
        ui->widthLabel->setVisible(false);
        ui->heightLabel->setVisible(false);
        ui->depthLabel->setVisible(false);
        ui->radiusLabel->setVisible(false);
        ui->lengthLabel->setVisible(true);
        ui->sideLabel->setVisible(true);
        ui->slicesLabel->setVisible(false);
        ui->stacksLabel->setVisible(false);
    }
        break;

    case APrimitive::PT_PYRAMID:
    {
        APyramid* pyramid = (APyramid*)selectedPrimitive;
        ui->sideSpin->setValue(pyramid->getSideLength());

        ui->widthSpin->setVisible(false);
        ui->heightSpin->setVisible(false);
        ui->depthSpin->setVisible(false);
        ui->radiusSpin->setVisible(false);
        ui->lengthSpin->setVisible(false);
        ui->sideSpin->setVisible(true);
        ui->slicesSpin->setVisible(false);
        ui->stacksSpin->setVisible(false);
        ui->widthLabel->setVisible(false);
        ui->heightLabel->setVisible(false);
        ui->depthLabel->setVisible(false);
        ui->radiusLabel->setVisible(false);
        ui->lengthLabel->setVisible(false);
        ui->sideLabel->setVisible(true);
        ui->slicesLabel->setVisible(false);
        ui->stacksLabel->setVisible(false);
    }
        break;

    case APrimitive::PT_SPHERE:
    {
        ASphere* sphere = (ASphere*)selectedPrimitive;
        ui->radiusSpin->setValue(sphere->getRadius());
        ui->slicesSpin->setValue(sphere->getSlices());
        ui->stacksSpin->setValue(sphere->getStacks());

        ui->widthSpin->setVisible(false);
        ui->heightSpin->setVisible(false);
        ui->depthSpin->setVisible(false);
        ui->radiusSpin->setVisible(true);
        ui->lengthSpin->setVisible(false);
        ui->sideSpin->setVisible(false);
        ui->slicesSpin->setVisible(true);
        ui->stacksSpin->setVisible(true);
        ui->widthLabel->setVisible(false);
        ui->heightLabel->setVisible(false);
        ui->depthLabel->setVisible(false);
        ui->radiusLabel->setVisible(true);
        ui->lengthLabel->setVisible(false);
        ui->sideLabel->setVisible(false);
        ui->slicesLabel->setVisible(true);
        ui->stacksLabel->setVisible(true);
    }
        break;

    default:
        break;
    }
}

void ToolWidget::on_okButton_clicked()
{
    if (!selectedPrimitive) {
        return;
    }
    switch (selectedPrimitive->getType()) {
    case APrimitive::PT_CONE:
    {
        ACone* cone = (ACone*)selectedPrimitive;
        cone->reset(ui->radiusSpin->value(),
                    ui->slicesSpin->value(),
                    ui->heightSpin->value());
    }
        break;

    case APrimitive::PT_CUBE:
    {
        ACube* cube = (ACube*)selectedPrimitive;
        cube->reset(ui->widthSpin->value(),
                    ui->depthSpin->value(),
                    ui->heightSpin->value());
    }
        break;

    case APrimitive::PT_CYLINDER:
    {
        ACylinder* cylinder = (ACylinder*)selectedPrimitive;
        cylinder->reset(ui->radiusSpin->value(),
                        ui->slicesSpin->value(),
                        ui->heightSpin->value());
    }
        break;

    case APrimitive::PT_PRISM:
    {
        APrism* prism = (APrism*)selectedPrimitive;
        prism->reset(ui->lengthSpin->value(),
                     ui->sideSpin->value());
    }
        break;

    case APrimitive::PT_PYRAMID:
    {
        APyramid* pyramid = (APyramid*)selectedPrimitive;
        pyramid->reset(ui->sideSpin->value());
    }
        break;

    case APrimitive::PT_SPHERE:
    {
        ASphere* sphere = (ASphere*)selectedPrimitive;
        sphere->reset(ui->radiusSpin->value(),
                      ui->slicesSpin->value(),
                      ui->stacksSpin->value());
    }
        break;

    default:
        break;
    }
    mainWindow->getViewManager()->repaintAll();
}

void ToolWidget::on_positionBtn_clicked()
{
    if (!selectedPrimitive) {
        return;
    }
    Vector3d rot(ui->xRotateSpin->value(),
                 ui->yRotateSpin->value(),
                 ui->zRotateSpin->value());
    selectedPrimitive->setRotate(rot);
    Vector3d scale(ui->xScaleSpin->value(),
                   ui->yScaleSpin->value(),
                   ui->zScaleSpin->value());
    selectedPrimitive->setScale(scale);
    Vector3d trans(ui->xTransSpin->value(),
                   ui->yTransSpin->value(),
                   ui->zTransSpin->value());
    selectedPrimitive->setTranslate(trans);
    mainWindow->getViewManager()->repaintAll();
}

void ToolWidget::on_solidBox_currentIndexChanged(const QString &arg1)
{
    map<QString, ASolid*>::iterator iter = solidMap->find(arg1);
    if (iter == solidMap->end()) {
        if (!protectSelectMode) {
            mainWindow->getModelManager()->selectSolid(0);
        }
        return;
    }

    selectedSolid = iter->second;
    mainWindow->getModelManager()->selectSolid(selectedSolid);

    Vector3d scale = selectedSolid->getScale();
    ui->xScaleSolidSpin->setValue(scale.x);
    ui->yScaleSolidSpin->setValue(scale.y);
    ui->zScaleSolidSpin->setValue(scale.z);
    Vector3d rotate = selectedSolid->getRotate();
    ui->xRotateSolidSpin->setValue(rotate.x);
    ui->yRotateSolidSpin->setValue(rotate.y);
    ui->zRotateSolidSpin->setValue(rotate.z);
    Vector3d trans = selectedSolid->getTranslate();
    ui->xTransSolidSpin->setValue(trans.x);
    ui->yTransSolidSpin->setValue(trans.y);
    ui->zTransSolidSpin->setValue(trans.z);

    ui->visibleSldBtn->setChecked(selectedSolid->getVisible());

    checkUngroupDelete();
}

void ToolWidget::on_solidBtn_clicked()
{
    if (!selectedSolid) {
        return;
    }
    selectedSolid->setXScale(ui->xScaleSolidSpin->value());
    selectedSolid->setYScale(ui->yScaleSolidSpin->value());
    selectedSolid->setZScale(ui->zScaleSolidSpin->value());
    selectedSolid->setXRotate(ui->xRotateSolidSpin->value());
    selectedSolid->setYRotate(ui->yRotateSolidSpin->value());
    selectedSolid->setZRotate(ui->zRotateSolidSpin->value());
    selectedSolid->setXTranslate(ui->xTransSolidSpin->value());
    selectedSolid->setYTranslate(ui->yTransSolidSpin->value());
    selectedSolid->setZTranslate(ui->zTransSolidSpin->value());
    mainWindow->getViewManager()->repaintAll();
}

void ToolWidget::on_boolBtn_clicked()
{
    map<QString, ASolid*>::iterator iter1 =
            solidMap->find(ui->boolBox1->currentText());
    map<QString, ASolid*>::iterator iter2 =
            solidMap->find(ui->boolBox2->currentText());
    if (iter1 == solidMap->end() || iter2 == solidMap->end()) {
        return;
    }

    // TODO: currently only union here
    if (!mainWindow->getModelManager()->insertSolid(
                iter1->second, iter2->second, ASolid::BO_UNION)) {
        QMessageBox::critical(this, "Error",
                              "Fail to insert solid because one"\
                              " is the other's decent");
    }
    mainWindow->getViewManager()->repaintAll();
    updateModelBox();
}

void ToolWidget::on_deleteSolidButton_clicked()
{
    QString solidName = ui->solidBox->currentText();
    if (mainWindow->getModelManager()->deleteSolid(solidName)) {
        mainWindow->getViewManager()->repaintAll();
        updateModelBox();
    } else {
        QMessageBox::about(this, "Error",
                           "Fail to delete solid: " + solidName);
    }
}

void ToolWidget::on_ungroupSolidButton_clicked()
{
    QString solidName = ui->solidBox->currentText();
    if (mainWindow->getModelManager()->ungroupSolid(solidName)) {
        mainWindow->getViewManager()->repaintAll();
        updateModelBox();
    } else {
        QMessageBox::about(this, "Error",
                           "Fail to ungroup solid: " + solidName);
    }
}

void ToolWidget::checkUngroupDelete()
{
    if (selectedSolid) {
        if (selectedSolid->isRoot()) {
            ui->deleteSolidButton->setEnabled(true);
            ui->ungroupSolidButton->setEnabled(true);
        } else {
            ui->deleteSolidButton->setEnabled(false);
            ui->ungroupSolidButton->setEnabled(false);
        }
    }
}

void ToolWidget::on_deletePmtButton_clicked()
{
    if (selectedPrimitive) {
        if (mainWindow->getModelManager()->deletePmt(selectedPrimitive)) {
            mainWindow->getViewManager()->repaintAll();
            updateModelBox();
        } else {
            QMessageBox::critical(this, "Error",
                                  "Error in deleting primitive");
        }
    }
}

void ToolWidget::on_tabWidget_currentChanged(QWidget *arg1)
{
    if (arg1 == ui->solidTab) {
        mainWindow->getModelManager()->selectSolid(selectedSolid);
        mainWindow->getViewManager()->repaintAll();
    } else if (arg1 == ui->primitiveTab) {
        ModelManager* model = mainWindow->getModelManager();
        ASolid* solid = model->getSolidFromPmt(selectedPrimitive);
        model->selectSolid(solid);
        mainWindow->getViewManager()->repaintAll();
    }
}

void ToolWidget::on_visiblePmtBtn_clicked()
{
    ModelManager* model = mainWindow->getModelManager();
    ASolid* solid = model->getSolidFromPmt(selectedPrimitive);
    if (solid) {
        solid->setVisible(!solid->getVisible());
        mainWindow->getViewManager()->repaintAll();
        if (ui->visiblePmtBtn->text() == "Hide") {
            ui->visiblePmtBtn->setText("Show");
        } else {
            ui->visiblePmtBtn->setText("Hide");
        }
    }
}

void ToolWidget::on_visibleSldBtn_clicked()
{
    if (selectedSolid) {
        selectedSolid->setVisible(!selectedSolid->getVisible());
        mainWindow->getViewManager()->repaintAll();
        if (ui->visibleSldBtn->text() == "Hide") {
            ui->visibleSldBtn->setText("Show");
        } else {
            ui->visibleSldBtn->setText("Hide");
        }
    }
}

void ToolWidget::on_colorButton_clicked()
{
    if (colorDialog) {
        delete colorDialog;
    }
    colorDialog = new ColorDialog(mainWindow, selectedPrimitive, this);
    colorDialog->show();
}

void ToolWidget::on_matButton_clicked()
{
    if (selectedPrimitive->getType() != APrimitive::PT_NONE) {
        if (matDialog) {
            delete matDialog;
        }
        matDialog = new MaterialDialog(selectedPrimitive, this);
        matDialog->show();
    }
}
