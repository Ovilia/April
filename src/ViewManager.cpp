#include "ViewManager.h"

ViewManager::ViewManager(MainWindow* mainWindow, QWidget *parent) :
    QMdiArea(parent),
    preferedViewerAmt(1)
{
    // tool widget
    toolWidget = new ToolWidget(mainWindow);
    addSubWindow(toolWidget);
    toolWidget->move(0, 0);

    // init viewWidget widgets
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        viewWidget[i] = new ViewWidget(mainWindow->getModelManager());
        addSubWindow(viewWidget[i]);
        viewWidget[i]->move(DEFAULT_AGL_X, DEFAULT_AGL_Y);
        viewWidget[i]->resize(DEFAULT_AGL_WIDTH, DEFAULT_AGL_HEIGHT);
    }
    showWidget(preferedViewerAmt);
}

ViewManager::~ViewManager()
{
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        if (viewWidget[i]) {
            delete viewWidget[i];
        }
    }

    delete toolWidget;
}

void ViewManager::showWidget(const int count)
{
    if (count <= 0) {
        return;
    }
    for (int i = 0; i < count; ++i) {
        viewWidget[i]->setVisible(true);
    }
    for (int i = count; i < MAX_VIEWER_AMT; ++i) {
        viewWidget[i]->setVisible(false);
    }
}

ViewWidget* ViewManager::getSelectedWidget()
{
    // TODO: get selected index, remember not to use activeSubWindow
    // since it may not be AGLWidget, consider a member variable here
    return viewWidget[0];
}

void ViewManager::setViewMode(AGLWidget::ViewMode mode)
{
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        viewWidget[i]->getAglWidget()->setViewMode(mode);
    }
    viewMode = mode;
}

AGLWidget::ViewMode ViewManager::getViewMode()
{
    return viewMode;
}

void ViewManager::setBestFit()
{

}
