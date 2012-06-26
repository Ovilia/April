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

    void show4Views(int width, int height);
    void show1View(int width, int height);

    ToolWidget* getToolWidget();

    void setBestFit();

    void repaintAll();

private:
    MainWindow* mainWindow;

    // widget to show model under different views
    static const int MAX_VIEWER_AMT = 4;
    int preferedViewerAmt;
    ViewWidget* viewWidget[MAX_VIEWER_AMT];

    StateEnum::ViewMode viewMode;

    static const int DEFAULT_AGL_X = 350;
    static const int DEFAULT_AGL_Y = 0;
    static const int DEFAULT_AGL_WIDTH = 800;
    static const int DEFAULT_AGL_HEIGHT = 600;

    ToolWidget* toolWidget;
};

#endif // ViewManager_H
