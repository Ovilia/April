#ifndef TextureDIALOG_H
#define TextureDIALOG_H

#include <QDialog>

#include "TextGlWidget.h"
#include "Texture.h"
#include "Solid/APrimitive.h"

namespace Ui {
    class TextureDialog;
}

class TextureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextureDialog(APrimitive* primitive, QWidget *parent = 0);
    ~TextureDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TextureDialog *ui;
    TextGlWidget* glWidget;

    APrimitive* primitive;
    Texture* originText;
};

#endif // TextureDIALOG_H
