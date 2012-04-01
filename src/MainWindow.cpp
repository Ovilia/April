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

void MainWindow::on_actionZoom_in_triggered(bool checked)
{
    viewManager->getSelectedWidget()->getAglWidget()->zoomIn();
}

void MainWindow::on_actionZoom_out_triggered(bool checked)
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
