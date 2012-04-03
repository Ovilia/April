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
    createPrmType(APrimitive::PT_NONE),
    selectedPrimitive(0)
{
    ui->setupUi(this);
    ui->paraWidget->setVisible(false);

    solidMap = mainWindow->getModelManager()->getSolidMap();
    primitiveMap = mainWindow->getModelManager()->getPrimitiveMap();
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
    map<QString, APrimitive*>::iterator iter;
    for (iter = primitiveMap->begin(); iter != primitiveMap->end(); ++iter) {
        ui->modelBox->addItem(iter->first);
    }
    ui->paraWidget->setVisible(true);
}

void ToolWidget::on_modelBox_currentIndexChanged(const QString &arg1)
{
    map<QString, APrimitive*>::iterator iter = primitiveMap->find(arg1);
    if (iter == primitiveMap->end()) {
        return;
    }

    selectedPrimitive = iter->second;
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
