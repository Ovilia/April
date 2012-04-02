#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>

#include "Solid/APrimitive.h"

namespace Ui {
class CreateDialog;
}

/**
 * This dialog is currently used to create primitives.
 * Creating by dragging will be later implemented.
 */
class CreateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateDialog(APrimitive::PrimitiveType primitiveType,
                          QWidget *parent = 0);
    ~CreateDialog();

    void changePrimitive(APrimitive::PrimitiveType primitiveType);
    
private slots:
    void on_cancelButton_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::CreateDialog *ui;

    APrimitive::PrimitiveType primitiveType;
};

#endif // CREATEDIALOG_H
