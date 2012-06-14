#include "TextureDialog.h"
#include "ui_TextureDialog.h"

TextureDialog::TextureDialog(APrimitive* primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog),
    pmtWidget(new TextGlWidget(primitive->getType(), this)),
    uvWidget(new TextUvGlWidget(primitive->getTexture(), this)),

    primitive(primitive),
    originText(primitive->getTexture())
{
    ui->setupUi(this);
    ui->glLayout->addWidget(pmtWidget);
    ui->glLayout->addWidget(uvWidget);
}

TextureDialog::~TextureDialog()
{
    delete ui;

    delete pmtWidget;
    delete uvWidget;
}

void TextureDialog::on_pushButton_clicked()
{
    primitive->setTexture(*originText);
    close();
}
