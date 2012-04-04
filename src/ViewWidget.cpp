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
