#ifndef ViewManager_H
#define ViewManager_H

#include <QMdiArea>

#include "AGLWidget.h"
#include "MainWindow.h"
#include "StateEnum.h"
#include "ToolWidget.h"
#include "ViewWidget.h"

class AGLWidget;
class MainWindow;
class ToolWidget;
class ViewWidget;

class ViewManager : public QMdiArea
{
    Q_OBJECT
public:
    explicit ViewManager(MainWindow* mainWindow, QWidget *parent = 0);
    ~ViewManager();

    void showWidget(const int count);
    // return selected widget
    ViewWidget* getSelectedWidget();

    void setViewMode(StateEnum::ViewMode mode);
    StateEnum::ViewMode getViewMode();

    ToolWidget* getToolWidget();

    void setBestFit();

    void repaintAll();

private:
    MainWindow* mainWindow;

    // widget to show model under different views
    static const int MAX_VIEWER_AMT = 6;
    int preferedViewerAmt;
    ViewWidget* viewWidget[MAX_VIEWER_AMT];

    StateEnum::ViewMode viewMode;

    static const int DEFAULT_AGL_X = 320;
    static const int DEFAULT_AGL_Y = 0;
    static const int DEFAULT_AGL_WIDTH = 700;
    static const int DEFAULT_AGL_HEIGHT = 500;

    ToolWidget* toolWidget;
};

#endif // ViewManager_H
