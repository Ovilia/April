#include "TextureDialog.h"
#include "ui_TextureDialog.h"

#include <QMessageBox>

#include <QDebug>

#include "TextureFile.h"

TextureDialog::TextureDialog(ViewManager *viewManager,
                             APrimitive *primitive, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog),
    uvWidget(new TextUvGlWidget(viewManager, primitive->getTexture(), this)),
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
                APrimitive::PRIMITIVE_TYPE_NAME[primitive->getType()] + ".atxt",
                tr("April Project Texture (*.atxt)"));
    if (!saveName.isNull()) {
        bool isSaved = TextureFile::writeFile(
                    *uvWidget->getTexture(), saveName);
        if (!isSaved) {
            QMessageBox::critical(this, "Save Texture Failed",
                                  "Failed to save texture");
        } else {
            uvWidget->getTexture()->setUvFileName(saveName);
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
            } else {
                primitive->getTexture()->setUvFileName(openName);
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

void TextureDialog::on_checkBox_clicked(bool checked)
{
    uvWidget->setFillVisible(checked);
}

void TextureDialog::on_saveUvButton_clicked()
{
    QString saveName = QFileDialog::getSaveFileName(
                this,
                tr("Save Texture UV"),
                APrimitive::PRIMITIVE_TYPE_NAME[primitive->getType()] + ".png",
                tr("Image files(*.bmp *.jpeg *.jpg *.png *.gif *.tif);;"\
                   "All files (*.*)"));
    if (!saveName.isNull()) {
        QImage* image = uvWidget->getUvImage();
        if (image != 0) {
            image->save(saveName);
        } else {
            QMessageBox::critical(this, "Error",
                                  "Error in saving texture uv");
        }
    }
}
