#ifndef APRILPRIMITIVE_H
#define APRILPRIMITIVE_H

class APrimitive
{
public:
    APrimitive();
    virtual ~APrimitive();

    enum RGB_Index {
        INDEX_RED = 0,
        INDEX_GREEN,
        INDEX_BLUE,
        INDEX_ALPHA
    };
    static const int RGBA_LENGTH = 4;

    // draw model with certain style
    virtual void drawWire() = 0;
    virtual void drawSolid() = 0;

    double getXRotate();
    double getYRotate();
    double getZRotate();

    double getXScale();
    double getYScale();
    double getZScale();

    double getXTransform();
    double getYTransform();
    double getZTransform();

    // rotate within [0, 360)
    void setXRotate(double rotate);
    void setYRotate(double rotate);
    void setZRotate(double rotate);

    // scale within (0, infinity)
    void setXScale(double scale);
    void setYScale(double scale);
    void setZScale(double scale);

    // transform within (-infinity, infinity)
    void setXTransform(double transform);
    void setYTransform(double transform);
    void setZTransform(double transform);

    bool getSelected();
    void setSelected(bool value);

protected:
    double xRotate;
    double yRotate;
    double zRotate;

    double xScale;
    double yScale;
    double zScale;

    double xTransform;
    double yTransform;
    double zTransform;

    bool isSelected;

    // rgba color within [0, 1], with index of RGB_INDEX
    // it is originally set to be random
    double color[RGBA_LENGTH];
    // random color to be used when init
    static const int RANDOM_COLOR_COUNT = 12;
    static const double RANDOM_COLOR[RANDOM_COLOR_COUNT][RGBA_LENGTH];
};

#endif // APRILPRIMITIVE_H
