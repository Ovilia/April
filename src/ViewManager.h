#ifndef ViewManager_H
#define ViewManager_H

#include <QMdiArea>

#include "AGLWidget.h"
#include "ModelManager.h"
#include "ViewWidget.h"

class ViewManager : public QMdiArea
{
    Q_OBJECT
public:
    explicit ViewManager(ModelManager* modelManager, QWidget *parent = 0);
    ~ViewManager();

    void showWidget(const int count);

private:
    // widget to show model under different views
    static const int MAX_VIEWER_AMT = 6;
    int preferedViewerAmt;
    ViewWidget* viewWidget[MAX_VIEWER_AMT];
};

#endif // ViewManager_H
