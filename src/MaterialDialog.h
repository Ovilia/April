#ifndef MATERIALDIALOG_H
#define MATERIALDIALOG_H

#include <QDialog>

#include "MatGlWidget.h"
#include "Solid/APrimitive.h"

namespace Ui {
    class MaterialDialog;
}

class MaterialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialDialog(APrimitive* primitive, QWidget *parent = 0);
    ~MaterialDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MaterialDialog *ui;
    MatGlWidget* glWidget;

    APrimitive* primitive;
    Material* originMat;
};

#endif // MATERIALDIALOG_H
