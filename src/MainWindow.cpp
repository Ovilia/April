#include <QGridLayout>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modelManager = new ModelManager(this);
    viewManager = new ViewManager(this, this);

    ui->centerLayout->addWidget(viewManager);

    viewManager->setViewMode(StateEnum::VM_MOVE);

    // TODO: this is the buttons not implemented
    ui->actionBest_fit->setVisible(false);
    ui->actionSelect->setVisible(false);
    ui->actionModelRotate->setVisible(false);
    ui->actionModelMove->setVisible(false);
    ui->actionModelScale->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete viewManager;
    delete modelManager;
}

ModelManager* MainWindow::getModelManager()
{
    return modelManager;
}

ViewManager* MainWindow::getViewManager()
{
    return viewManager;
}

void MainWindow::on_actionMove_triggered(bool checked)
{
    if (checked) {
        viewManager->setViewMode(StateEnum::VM_MOVE);
        // uncheck other buttons
        ui->actionBest_fit->setChecked(false);
        ui->actionRotate->setChecked(false);
        ui->actionZoom_in->setChecked(false);
        ui->actionZoom_out->setChecked(false);
        ui->actionSelect->setChecked(false);
    } else {
        viewManager->setViewMode(StateEnum::VM_NONE);
    }
}

void MainWindow::on_actionZoom_in_triggered(bool)
{
    viewManager->getSelectedWidget()->getAglWidget()->zoomIn();
}

void MainWindow::on_actionZoom_out_triggered(bool)
{
    viewManager->getSelectedWidget()->getAglWidget()->zoomOut();
}

void MainWindow::on_actionRotate_triggered(bool checked)
{
    if (checked) {
        viewManager->setViewMode(StateEnum::VM_ROTATE);
        // uncheck other buttons
        ui->actionBest_fit->setChecked(false);
        ui->actionMove->setChecked(false);
        ui->actionZoom_in->setChecked(false);
        ui->actionZoom_out->setChecked(false);
        ui->actionSelect->setChecked(false);
    } else {
        viewManager->setViewMode(StateEnum::VM_NONE);
    }
}

void MainWindow::on_actionBest_fit_triggered()
{
    // uncheck other buttons
    ui->actionMove->setChecked(false);
    ui->actionZoom_in->setChecked(false);
    ui->actionZoom_out->setChecked(false);
    ui->actionRotate->setChecked(false);
    ui->actionSelect->setChecked(false);
}

void MainWindow::on_actionRotate_X_triggered()
{
    viewManager->getSelectedWidget()->getAglWidget()->rotateX();
}

void MainWindow::on_actionRotate_Y_triggered()
{
    viewManager->getSelectedWidget()->getAglWidget()->rotateY();
}

void MainWindow::on_actionRotate_Z_triggered()
{
    viewManager->getSelectedWidget()->getAglWidget()->rotateZ();
}

void MainWindow::on_actionSelect_triggered(bool checked)
{
    if (checked) {
        viewManager->setViewMode(StateEnum::VM_SELECT);
        // uncheck other buttons
        ui->actionBest_fit->setChecked(false);
        ui->actionMove->setChecked(false);
        ui->actionZoom_in->setChecked(false);
        ui->actionZoom_out->setChecked(false);
        ui->actionRotate->setChecked(false);
    } else {
        viewManager->setViewMode(StateEnum::VM_NONE);
    }
}

void MainWindow::on_actionSolid_triggered(bool checked)
{
    if (!checked) {
        ui->actionWire->setChecked(true);
    }
    modelManager->setDrawSolid(checked);
    modelManager->setDrawWire(ui->actionWire->isChecked());
    viewManager->repaintAll();
}

void MainWindow::on_actionWire_triggered(bool checked)
{
    if (!checked) {
        ui->actionSolid->setChecked(true);
    }
    modelManager->setDrawSolid(ui->actionSolid->isChecked());
    modelManager->setDrawWire(checked);
    viewManager->repaintAll();
}
