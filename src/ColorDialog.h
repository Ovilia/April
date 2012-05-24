#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QString>

#include "MainWindow.h"
#include "Solid/APrimitive.h"
#include "Vector3d.h"

namespace Ui {
    class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(MainWindow* mainWindow, APrimitive* primitive,
                         QWidget *parent = 0);
    ~ColorDialog();

private slots:
    void on_cancelButton_clicked();

    void on_redSlider_valueChanged(int value);

    void on_greenSlider_valueChanged(int value);

    void on_blueSlider_valueChanged(int value);

    void on_oldButton_clicked();

    void on_applyButton_clicked();

private:
    Ui::ColorDialog *ui;

    MainWindow* mainWindow;
    APrimitive* primitive;

    Vector3d oldColor;
    Vector3d newColor;

    QString getStyleSheet(const Vector3d color) const;
};

#endif // COLORDIALOG_H
