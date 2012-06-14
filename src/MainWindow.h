#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>

#include "ModelManager.h"
#include "ViewManager.h"

class ModelManager;
class ToolWidget;
class ViewManager;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ModelManager* getModelManager();
    ViewManager* getViewManager();

    void setSaveEnabled(bool enabled);

private slots:
    void on_actionMove_triggered(bool checked);

    void on_actionZoom_in_triggered(bool checked);

    void on_actionZoom_out_triggered(bool checked);

    void on_actionRotate_triggered(bool checked);

    void on_actionBest_fit_triggered();

    void on_actionSelect_triggered(bool checked);

    void on_actionSolid_triggered(bool checked);

    void on_actionWire_triggered(bool checked);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;

    // stores all models in model manager and give it to aglWidget to show
    ModelManager* modelManager;
    // show different views of models
    ViewManager* viewManager;

    // return true if open *.apr without error
    bool openProject();
    // return true if model is not changed or saved to *.apr without error
    bool saveProject();
};

#endif // MAINWINDOW_H
