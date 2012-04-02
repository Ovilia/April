#ifndef ACREATEDIALOG_H
#define ACREATEDIALOG_H

#include <QDialog>

#include "ModelManager.h"
#include "Solid/APrimitive.h"

namespace Ui {
    class ACreateDialog;
}

class ModelManager;

/**
 * This dialog is currently used to create primitives.
 * Creating by dragging will be later implemented.
 */
class ACreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ACreateDialog(APrimitive::PrimitiveType primitiveType,
                          ModelManager* modelManager,
                          QWidget *parent = 0);
    ~ACreateDialog();

    void changePrimitive(APrimitive::PrimitiveType primitiveType);

private slots:
    void on_cancelButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_okButton_clicked();

private:
    Ui::ACreateDialog *ui;

    ModelManager* modelManager;

    APrimitive::PrimitiveType primitiveType;
};

#endif // ACREATEDIALOG_H
