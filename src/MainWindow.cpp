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

