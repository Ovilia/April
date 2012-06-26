#ifndef TextUvGlWidget_H
#define TextUvGlWidget_H

#include <QImage>
#include <QLabel>

#include "Texture.h"

class TextUvGlWidget : public QLabel
{
public:
    TextUvGlWidget(Texture* texture, QWidget *parent = 0);
    ~TextUvGlWidget();

    Texture* getTexture() const;
    // call when texture changed
    void textChanged();

    void paintEvent(QPaintEvent *event);

private:
    Texture* texture;

    QImage image;
};

#endif // TextUvGlWidget_H
