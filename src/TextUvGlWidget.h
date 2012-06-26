#ifndef TextUvGlWidget_H
#define TextUvGlWidget_H

#include <QImage>
#include <QLabel>

#include "Texture.h"
#include "ViewManager.h"

class ViewManager;

class TextUvGlWidget : public QLabel
{
public:
    TextUvGlWidget(ViewManager* viewManager,
                   Texture* texture, QWidget *parent = 0);
    ~TextUvGlWidget();

    Texture* getTexture() const;
    // call when texture changed
    void textChanged();

    void paintEvent(QPaintEvent *event);

    void setFillVisible(bool visible);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    Texture* texture;
    ViewManager* viewManager;

    QImage image;

    int getClickedVertex(int x, int y) const;
    int getClickedFace(int x, int y) const;

    bool isInsideTriangle(QPair<double, double>* triangle,
                          QPair<double, double> point) const;
    double crossProduct(QPair<double, double> vec1,
                        QPair<double, double> vec2) const;

    static const int NOT_SELECTED = -1;

    bool isMousePressed;

    int selectedVertex;
    int selectedFace;

    bool fillVisible;
};

#endif // TextUvGlWidget_H
