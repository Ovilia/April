#ifndef ACREATEDIALOG_H
#define ACREATEDIALOG_H

#include <QDialog>

#include "MainWindow.h"
#include "Solid/APrimitive.h"
#include "ToolWidget.h"

namespace Ui {
    class ACreateDialog;
}

class MainWindow;
class ToolWidget;

/**
 * This dialog is used to create primitives.
 * Creating by dragging will be later implemented.
 */
class ACreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ACreateDialog(APrimitive::PrimitiveType primitiveType,
                           MainWindow* mainWindow,
                           ToolWidget* toolWidget,
                           QWidget *parent = 0);
    ~ACreateDialog();

    void changePrimitive(APrimitive::PrimitiveType primitiveType);

private slots:
    void on_cancelButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_okButton_clicked();

private:
    Ui::ACreateDialog *ui;

    MainWindow* mainWindow;
    ToolWidget* toolWidget;

    APrimitive::PrimitiveType primitiveType;
};

#endif // ACREATEDIALOG_H
