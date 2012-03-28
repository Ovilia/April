#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>

#include "ModelManager.h"
#include "ViewManager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // stores all models in model manager and give it to aglWidget to show
    ModelManager* modelManager;
    // show different views of models
    ViewManager* viewManager;
};

#endif // MAINWINDOW_H
