#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <map>
using namespace std;

#include <QString>

#include "MainWindow.h"

#include "Solid/APrimitive.h"
#include "Solid/ASolid.h"

#include "Solid/ACone.h"
#include "Solid/ACube.h"
#include "Solid/ACylinder.h"
#include "Solid/APrism.h"
#include "Solid/APyramid.h"
#include "Solid/ASphere.h"

class MainWindow;

class ModelManager
{
public:
    ModelManager(MainWindow* mainWindow);
    ~ModelManager();

    // draw all objects
    void drawSolid();
    void drawWire();

    map<QString, ASolid*>* getSolidMap();

    void insertCube(double width, double depth, double height);
    void insertSphere(double radius, int slices, int stacks);
    void insertCylinder(double radius, int slices, double height);
    void insertCone(double radius, int slices, double height);
    void insertPrism(double length, double sideLength, int sideCount = 3);
    void insertPyramid(double sideLength, int sideCount = 3);

    bool getIsDrawSolid() const;
    bool getIsDrawWire() const;
    void setDrawWire(const bool enabled);
    void setDrawSolid(const bool enabled);

private:
    MainWindow* mainWindow;

    // unique name and solid
    map<QString, ASolid*> solidMap;
    // used as a hint of next id
    unsigned int nextSolidID;

    // unique name and primitive
    map<QString, APrimitive*> primitiveMap;
    // used as a hint of next id
    unsigned int nextPrimiID;

    // called by insertCude ..., insert to solidMap and primitiveMap
    void insertToMap(APrimitive* primitive);

    bool isDrawSolid;
    bool isDrawWire;
};

#endif // MODELMANAGER_H
