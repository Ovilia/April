#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "Solid/ASolid.h"

class ModelManager
{
public:
    ModelManager();
    ~ModelManager();

    // draw all objects
    void draw();

    void insertCube(double width, double depth, double height);
    void insertSphere(double radius, int slices, int stacks);
    void insertCylinder(double radius, int slices, double height);
    void insertCone(double radius, int slices, double height);
    void insertPrism(double length, double sideLength, int sideCount = 3);
    void insertPyramid(double sideLength, int sideCount = 3);

private:

};

#endif // MODELMANAGER_H
