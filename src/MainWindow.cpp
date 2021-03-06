#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

#include "FileManager.h"

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

bool MainWindow::openProject()
{
    QString openName = QFileDialog::getOpenFileName(
                this,
                tr("Open April Project"),
                QDir::currentPath(),
                tr("April Project File (*.apr)"));
    if (!openName.isNull()) {
        bool isOpened = FileManager::readFile(openName, *modelManager);
        if (isOpened) {
            return true;
        } else {
            QMessageBox::about(this, tr("Failed to open project"),
                               tr("Failed to open project file ") + openName);
            return false;
        }
    } else {
        // cancelled when input open name
        return false;
    }
    // unexpected to reach here
    return false;
}

bool MainWindow::saveProject()
{
    if (modelManager->getModelChanged()) {
        QString saveName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save April Project"),
                    QDateTime::currentDateTime().
                    toString("yyyy_MM_dd_hh_mm_ss").append(".apr"),
                    tr("April Project File (*.apr)"));

        if (!saveName.isNull()) {
            bool isSaved = FileManager::writeFile(saveName, *modelManager);

            if (isSaved) {
                return true;
            } else {
                // ask if to retry if failed
                QMessageBox::StandardButton retry =
                        QMessageBox::warning(this, tr("Failed to save project"),
                                             tr("Failed to save project. "\
                                                "Try again?"),
                                             QMessageBox::Yes | QMessageBox::No,
                                             QMessageBox::Yes);
                if (retry == QMessageBox::Yes) {
                    return saveProject();
                } else {
                    return false;
                }
            }
        } else {
            // cancelled when input save name
            return false;
        }
    }
    // model not changed
    return true;
}

void MainWindow::on_actionOpen_triggered()
{
    if (modelManager->getModelChanged()) {
        // ask if to save model if model changed
        QMessageBox::StandardButton button =
                QMessageBox::question(NULL, tr("Save project"),
                                      tr("Project has been changed. "\
                                         "Save project?"),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::Yes);

        if (button == QMessageBox::Yes) {
            saveProject();
        }
    }
    openProject();
    viewManager->repaintAll();
    ToolWidget* tool = viewManager->getToolWidget();
    tool->updateModelBox();
    tool->updateLightBox();
    tool->updateLightCanOpen();
    ui->actionSolid->setChecked(true);
    ui->actionWire->setChecked(false);
}

void MainWindow::on_actionSave_triggered()
{
    saveProject();
}

void MainWindow::on_actionNew_triggered()
{
    if (modelManager->getModelChanged()) {
        // ask if to save model if model changed
        QMessageBox::StandardButton button =
                QMessageBox::question(NULL, tr("Save project"),
                                      tr("Project has been changed. "\
                                         "Save project?"),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::Yes);

        if (button == QMessageBox::Yes) {
            saveProject();
        }
    }
    modelManager->initialize();
    viewManager->repaintAll();
}

void MainWindow::on_action1_View_triggered()
{
    QSize size = ui->centerLayout->sizeHint();
    int x = size.width();
    int y = size.height();
    viewManager->show1View(x, y);
}

void MainWindow::on_action4_Views_triggered()
{
    QSize size = ui->centerLayout->sizeHint();
    int x = size.width();
    int y = size.height();
    viewManager->show4Views(x, y);
}
