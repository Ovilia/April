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

    if (toolWidget) {
        delete toolWidget;
    }
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

void ViewManager::show4Views(int width, int height)
{
    showWidget(4);
    for (int i = 0; i < 4; ++i) {
        viewWidget[i]->resize(width / 2, height / 2);
    }

    int x = toolWidget->width() + 25;
    int y = 0;
    width -= x;
    height -= y;
    viewWidget[0]->move(x, y);
    viewWidget[1]->move(x + width / 2 + 180, y);
    viewWidget[2]->move(x, y + height / 2);
    viewWidget[3]->move(x + width / 2 + 180, y + height / 2);

    viewWidget[1]->viewFront();
    viewWidget[2]->viewLeft();
    viewWidget[3]->viewTop();
}

void ViewManager::show1View(int width, int height)
{
    showWidget(1);
    int x = toolWidget->width() + 25;
    int y = 0;
    width -= x;
    height -= y;
    viewWidget[0]->move(x, y);
    viewWidget[0]->resize(width + 200, height - 25);
}

ViewWidget* ViewManager::getSelectedWidget()
{
    // TODO: get selected index, remember not to use activeSubWindow
    // since it may not be AGLWidget, consider a member variable here
    return viewWidget[0];
}

void ViewManager::setViewMode(StateEnum::ViewMode mode)
{
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        viewWidget[i]->getAglWidget()->setViewMode(mode);
    }
    viewMode = mode;
}

StateEnum::ViewMode ViewManager::getViewMode()
{
    return viewMode;
}

void ViewManager::setBestFit()
{

}

void ViewManager::repaintAll()
{
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        if (viewWidget[i]->isVisible()) {
            viewWidget[i]->getAglWidget()->repaint();
        }
    }
}

ToolWidget* ViewManager::getToolWidget()
{
    return toolWidget;
}
