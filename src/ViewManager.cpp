#include "ViewManager.h"

ViewManager::ViewManager(ModelManager* modelManager, QWidget *parent) :
    QMdiArea(parent),
    preferedViewerAmt(4)
{
    // init viewWidget widgets
    for (int i = 0; i < MAX_VIEWER_AMT; ++i) {
        viewWidget[i] = new ViewWidget(modelManager);
        addSubWindow(viewWidget[i]);
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
