#ifndef ViewManager_H
#define ViewManager_H

#include <QMdiArea>

#include "AGLWidget.h"
#include "ModelManager.h"
#include "ToolWidget.h"
#include "ViewWidget.h"

class ToolWidget;

class ViewManager : public QMdiArea
{
    Q_OBJECT
public:
    explicit ViewManager(ModelManager* modelManager, QWidget *parent = 0);
    ~ViewManager();

    void showWidget(const int count);
    // return selected widget
    ViewWidget* getSelectedWidget();

    void setViewMode(AGLWidget::ViewMode mode);
    AGLWidget::ViewMode getViewMode();

    void setBestFit();

private:
    // widget to show model under different views
    static const int MAX_VIEWER_AMT = 6;
    int preferedViewerAmt;
    ViewWidget* viewWidget[MAX_VIEWER_AMT];

    AGLWidget::ViewMode viewMode;

    static const int DEFAULT_AGL_X = 260;
    static const int DEFAULT_AGL_Y = 0;
    static const int DEFAULT_AGL_WIDTH = 700;
    static const int DEFAULT_AGL_HEIGHT = 500;

    ToolWidget* toolWidget;
};

#endif // ViewManager_H
