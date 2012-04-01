#include "ToolWidget.h"
#include "ui_ToolWidget.h"

ToolWidget::ToolWidget(ViewManager* viewManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget),
    viewManager(viewManager),
    createPrmType(APrimitive::PT_NONE)
{
    ui->setupUi(this);
}

ToolWidget::~ToolWidget()
{
    delete ui;
}

void ToolWidget::on_cubeButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_CUBE;
        // uncheck other buttons
        ui->sphereButton->setChecked(false);
        ui->cylinderButton->setChecked(false);
        ui->coneButton->setChecked(false);
        ui->prismButton->setChecked(false);
        ui->pyramidButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}

void ToolWidget::on_sphereButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_SPHERE;
        // uncheck other buttons
        ui->cubeButton->setChecked(false);
        ui->cylinderButton->setChecked(false);
        ui->coneButton->setChecked(false);
        ui->prismButton->setChecked(false);
        ui->pyramidButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}

void ToolWidget::on_cylinderButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_CYLINDER;
        // uncheck other buttons
        ui->sphereButton->setChecked(false);
        ui->cubeButton->setChecked(false);
        ui->coneButton->setChecked(false);
        ui->prismButton->setChecked(false);
        ui->pyramidButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}

void ToolWidget::on_coneButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_CONE;
        // uncheck other buttons
        ui->sphereButton->setChecked(false);
        ui->cylinderButton->setChecked(false);
        ui->cubeButton->setChecked(false);
        ui->prismButton->setChecked(false);
        ui->pyramidButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}

void ToolWidget::on_prismButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_PRISM;
        // uncheck other buttons
        ui->sphereButton->setChecked(false);
        ui->cylinderButton->setChecked(false);
        ui->coneButton->setChecked(false);
        ui->cubeButton->setChecked(false);
        ui->pyramidButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}

void ToolWidget::on_pyramidButton_clicked(bool checked)
{
    if (checked) {
        createPrmType = APrimitive::PT_PYRAMID;
        // uncheck other buttons
        ui->sphereButton->setChecked(false);
        ui->cylinderButton->setChecked(false);
        ui->coneButton->setChecked(false);
        ui->prismButton->setChecked(false);
        ui->cubeButton->setChecked(false);
    } else {
        createPrmType = APrimitive::PT_NONE;
    }
}
