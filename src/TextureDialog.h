#ifndef TextureDIALOG_H
#define TextureDIALOG_H

#include <QDialog>

#include "Texture.h"
#include "TextUvGlWidget.h"
#include "ViewManager.h"

namespace Ui {
    class TextureDialog;
}

class ViewManager;
class TextUvGlWidget;

class TextureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextureDialog(ViewManager* viewManager,
                           APrimitive* primitive, QWidget *parent = 0);
    ~TextureDialog();

private slots:
    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_SetImageButton_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::TextureDialog *ui;
    TextUvGlWidget* uvWidget;
    ViewManager* viewManager;

    APrimitive* primitive;
    Texture* originText;
};

#endif // TextureDIALOG_H
