#include <QGridLayout>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modelManager = new ModelManager();
    viewManager = new ViewManager(modelManager, this);

    ui->centerLayout->addWidget(viewManager);

    // TODO: this is the buttons not implemented
    ui->actionBest_fit->setVisible(false);
    ui->actionModelMove->setVisible(false);
    ui->actionModelScale->setVisible(false);
    ui->actionModelRotate->setVisible(false);
    ui->actionRotate->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete viewManager;
    delete modelManager;
}


void MainWindow::on_actionMove_triggered(bool checked)
{
    if (checked) {
        viewManager->setViewMode(AGLWidget::VM_MOVE);
        // uncheck other buttons
        ui->actionBest_fit->setChecked(false);
        ui->actionRotate->setChecked(false);
        ui->actionZoom_in->setChecked(false);
        ui->actionZoom_out->setChecked(false);
    } else {
        viewManager->setViewMode(AGLWidget::VM_NONE);
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
        viewManager->setViewMode(AGLWidget::VM_ROTATE);
        // uncheck other buttons
        ui->actionBest_fit->setChecked(false);
        ui->actionMove->setChecked(false);
        ui->actionZoom_in->setChecked(false);
        ui->actionZoom_out->setChecked(false);
    } else {
        viewManager->setViewMode(AGLWidget::VM_NONE);
    }
}

void MainWindow::on_actionBest_fit_triggered()
{
    // uncheck other buttons
    ui->actionBest_fit->setChecked(false);
    ui->actionMove->setChecked(false);
    ui->actionZoom_in->setChecked(false);
    ui->actionZoom_out->setChecked(false);
    ui->actionRotate->setChecked(false);
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
