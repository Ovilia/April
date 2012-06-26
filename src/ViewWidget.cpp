#include <QCloseEvent>

#include "ViewWidget.h"

ViewWidget::ViewWidget(ModelManager* modelManager)
{
    aglWidget = new AGLWidget(modelManager);
    setWidget(aglWidget);
}

ViewWidget::~ViewWidget()
{

}

AGLWidget* ViewWidget::getAglWidget()
{
    return aglWidget;
}

void ViewWidget::closeEvent(QCloseEvent *closeEvent)
{
    this->setVisible(false);
    closeEvent->ignore();
}

void ViewWidget::viewFront()
{
    aglWidget->viewFront();
}

void ViewWidget::viewLeft()
{
    aglWidget->viewLeft();
}

void ViewWidget::viewTop()
{
    aglWidget->viewTop();
}
