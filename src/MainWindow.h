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

private slots:
    void on_actionMove_triggered(bool checked);

    void on_actionZoom_in_triggered(bool checked);

    void on_actionZoom_out_triggered(bool checked);

    void on_actionRotate_triggered(bool checked);

    void on_actionBest_fit_triggered();

    void on_actionRotate_X_triggered();

    void on_actionRotate_Y_triggered();

    void on_actionRotate_Z_triggered();

private:
    Ui::MainWindow *ui;

    // stores all models in model manager and give it to aglWidget to show
    ModelManager* modelManager;
    // show different views of models
    ViewManager* viewManager;
};

#endif // MAINWINDOW_H
