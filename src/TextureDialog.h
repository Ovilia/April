#ifndef TextureDIALOG_H
#define TextureDIALOG_H

#include <QDialog>

#include "TextGlWidget.h"
#include "Texture.h"
#include "TextUvGlWidget.h"

namespace Ui {
    class TextureDialog;
}

//class TextUvGlWidget;

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
    TextGlWidget* pmtWidget;
    TextUvGlWidget* uvWidget;

    APrimitive* primitive;
    Texture* originText;
};

#endif // TextureDIALOG_H
