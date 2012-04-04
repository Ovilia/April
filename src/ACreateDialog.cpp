#include "ACreateDialog.h"
#include "ui_ACreateDialog.h"

ACreateDialog::ACreateDialog(APrimitive::PrimitiveType primitiveType,
                           ModelManager* modelManager,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ACreateDialog),
    modelManager(modelManager),
    primitiveType(primitiveType)
{
    ui->setupUi(this);
    changePrimitive(primitiveType);
}

ACreateDialog::~ACreateDialog()
{
    delete ui;
}

void ACreateDialog::changePrimitive(APrimitive::PrimitiveType primitiveType)
{
    if (primitiveType == APrimitive::PT_NONE) {
        primitiveType = APrimitive::PT_CUBE;
    }
    // APrimitive::PT_NONE is 0
    ui->tabWidget->setCurrentIndex(primitiveType - 1);
}

void ACreateDialog::on_cancelButton_clicked()
{
    close();
}

void ACreateDialog::on_tabWidget_currentChanged(int index)
{
    // APrimitive::PT_NONE is 0
    primitiveType = APrimitive::PrimitiveType(index + 1);
}

void ACreateDialog::on_okButton_clicked()
{
    switch (primitiveType) {
    case APrimitive::PT_CUBE:
        modelManager->insertCube(ui->cubeWidthSpin->value(),
                                 ui->cubeDepthSpin->value(),
                                 ui->cubeHeightSpin->value());
        break;

    case APrimitive::PT_CONE:
        modelManager->insertCone(ui->coneRadiusSpin->value(),
                                 ui->coneSlicesSpin->value(),
                                 ui->coneHeightSpin->value());
        break;

    case APrimitive::PT_CYLINDER:
        modelManager->insertCylinder(ui->cylinderRadiusSpin->value(),
                                     ui->cylinderSlicesSpin->value(),
                                     ui->cylinderHeightSpin->value());
        break;

    case APrimitive::PT_PRISM:
        modelManager->insertPrism(ui->prismLengthSpin->value(),
                                  ui->prismSideSpin->value());
        break;

    case APrimitive::PT_PYRAMID:
        modelManager->insertPyramid(ui->pyramidSideSpin->value());
        break;

    case APrimitive::PT_SPHERE:
        modelManager->insertSphere(ui->sphereRadiusSpin->value(),
                                   ui->sphereSlicesSpin->value(),
                                   ui->sphereStacksSpin->value());
        break;

    default:
        break;
    }
    close();
}
