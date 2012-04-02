#include "CreateDialog.h"
#include "ui_CreateDialog.h"

CreateDialog::CreateDialog(APrimitive::PrimitiveType primitiveType,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog),
    primitiveType(primitiveType)
{
    ui->setupUi(this);
    changePrimitive(primitiveType);
}

CreateDialog::~CreateDialog()
{
    delete ui;
}

void CreateDialog::changePrimitive(APrimitive::PrimitiveType primitiveType)
{
    if (primitiveType == APrimitive::PT_NONE) {
        primitiveType = APrimitive::PT_CUBE;
    }
    // APrimitive::PT_NONE is 0
    ui->tabWidget->setCurrentIndex(primitiveType - 1);
}

void CreateDialog::on_cancelButton_clicked()
{
    close();
}

void CreateDialog::on_tabWidget_currentChanged(int index)
{
    // APrimitive::PT_NONE is 0
    primitiveType = APrimitive::PrimitiveType(index + 1);
}
