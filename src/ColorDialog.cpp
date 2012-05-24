#include "ColorDialog.h"
#include "ui_ColorDialog.h"

ColorDialog::ColorDialog(MainWindow* mainWindow, APrimitive* primitive,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog),
    mainWindow(mainWindow),
    primitive(primitive),
    oldColor(primitive->getColor()),
    newColor(oldColor)
{
    ui->setupUi(this);

    QString sheet = getStyleSheet(oldColor);
    ui->oldButton->setStyleSheet(sheet);
    ui->newButton->setStyleSheet(sheet);

    ui->redSlider->setValue(oldColor.x * 100);
    ui->greenSlider->setValue(oldColor.y * 100);
    ui->blueSlider->setValue(oldColor.z * 100);
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::on_cancelButton_clicked()
{
    primitive->setColor(oldColor);
    mainWindow->getViewManager()->repaintAll();
    close();
}

QString ColorDialog::getStyleSheet(const Vector3d color) const
{
    return "background-color:rgb(" + QString::number(color.x * 100) +
            "%," + QString::number(color.y * 100) + "%," +
            QString::number(color.z * 100) + "%);";
}

void ColorDialog::on_redSlider_valueChanged(int value)
{
    ui->rLabel->setNum(value);
    newColor.x = value / 100.0;
    ui->newButton->setStyleSheet(getStyleSheet(newColor));
    primitive->setColor(newColor);
    mainWindow->getViewManager()->repaintAll();
}

void ColorDialog::on_greenSlider_valueChanged(int value)
{
    ui->greenLabel->setNum(value);
    newColor.y = value / 100.0;
    ui->newButton->setStyleSheet(getStyleSheet(newColor));
    primitive->setColor(newColor);
    mainWindow->getViewManager()->repaintAll();
}

void ColorDialog::on_blueSlider_valueChanged(int value)
{
    ui->blueLabel->setNum(value);
    newColor.z = value / 100.0;
    ui->newButton->setStyleSheet(getStyleSheet(newColor));
    primitive->setColor(newColor);
    mainWindow->getViewManager()->repaintAll();
}

void ColorDialog::on_oldButton_clicked()
{
    newColor = oldColor;
    ui->newButton->setStyleSheet(getStyleSheet(newColor));
    primitive->setColor(newColor);
    mainWindow->getViewManager()->repaintAll();
}

void ColorDialog::on_applyButton_clicked()
{
    close();
}
