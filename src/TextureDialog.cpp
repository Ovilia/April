#include "TextureDialog.h"
#include "ui_TextureDialog.h"

#include <QMessageBox>

#include <QDebug>

#include "TextureFile.h"

TextureDialog::TextureDialog(ViewManager *viewManager,
                             APrimitive *primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog),
    uvWidget(new TextUvGlWidget(primitive->getTexture(), this)),
    viewManager(viewManager),

    primitive(primitive),
    originText(primitive->getTexture())
{
    ui->setupUi(this);
    ui->glLayout->addWidget(uvWidget);
}

TextureDialog::~TextureDialog()
{
    delete ui;

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

void TextureDialog::on_openButton_clicked()
{
    QString openName = QFileDialog::getOpenFileName(
                this,
                tr("Open Texture"),
                ".",
                tr("April Project Texture (*.atxt)"));
    if (!openName.isNull()) {
        Texture* texture = new Texture();
        bool isOpened = TextureFile::readFile(texture, openName);
        if (!isOpened) {
            QMessageBox::critical(this, "Open Texture Failed",
                                  "Failed to open texture");
        } else {
            if (!primitive->setTexture(*texture)) {
                QMessageBox::critical(this, "Open Texture Failed",
                                      "Texture doesn\'t match with "\
                                      "current primitive");
            }
        }
        delete texture;
    }
}

void TextureDialog::on_SetImageButton_clicked()
{
    QString openName = QFileDialog::getOpenFileName(
                this,
                tr("Open Image"),
                ".",
                tr("Image files(*.bmp *.jpeg *.jpg *.png *.gif *.tif);;"\
                   "All files (*.*)"));
    if (!openName.isNull()) {
        // primitive in main view
        Texture* texture = primitive->getTexture();
        texture->setFileName(openName);
        viewManager->repaintAll();
        uvWidget->textChanged();
        uvWidget->repaint();
    }
}
