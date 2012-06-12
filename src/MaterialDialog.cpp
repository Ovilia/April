#include "MaterialDialog.h"
#include "ui_MaterialDialog.h"

MaterialDialog::MaterialDialog(APrimitive* primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaterialDialog),
    glWidget(new MatGlWidget(primitive->getType(), this)),

    primitive(primitive),
    originMat(primitive->getMaterial())
{
    ui->setupUi(this);
    ui->glLayout->addWidget(glWidget);
}

MaterialDialog::~MaterialDialog()
{
    delete ui;
}

void MaterialDialog::on_pushButton_clicked()
{
    primitive->setMaterial(*originMat);
    close();
}
