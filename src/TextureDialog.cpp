#include "TextureDialog.h"
#include "ui_TextureDialog.h"

TextureDialog::TextureDialog(APrimitive* primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog),
    glWidget(new TextGlWidget(primitive->getType(), this)),

    primitive(primitive),
    originText(primitive->getTexture())
{
    ui->setupUi(this);
    ui->glLayout->addWidget(glWidget);
}

TextureDialog::~TextureDialog()
{
    delete ui;
}

void TextureDialog::on_pushButton_clicked()
{
    primitive->setTexture(*originText);
    close();
}
