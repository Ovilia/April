#include "TextureDialog.h"
#include "ui_TextureDialog.h"

#include <QMessageBox>

#include "TextureFile.h"

TextureDialog::TextureDialog(APrimitive* primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog),
    pmtWidget(new TextGlWidget(primitive, this)),
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

void TextureDialog::on_saveButton_clicked()
{
    QString saveName = QFileDialog::getSaveFileName(
                this,
                tr("Save Texture"),
                QDateTime::currentDateTime().
                toString("yyyy_MM_dd_hh_mm_ss").append(".atxt"),
                tr("April Project Texture (*.atxt)"));
    if (!saveName.isNull()) {
        bool isSaved = TextureFile::writeFile(
                    *uvWidget->getTexture(), saveName);
        if (!isSaved) {
            QMessageBox::critical(this, "Save Texture Failed",
                                  "Failed to save texture");
        }
    }

}
