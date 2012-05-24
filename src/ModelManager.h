#ifndef MODELMANAGER_H
#define MODELMANAGER_H

using namespace std;

#include <map>

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

    // get if model is changed since last saving to file
    bool getModelChanged();
    // call when model saved
    void setModelSaved();
    // call when model changed (during open file)
    void setModelChanged();

    // initialize to contain no model
    void initialize();

    // draw all objects
    void drawSolid();
    void drawWire();

    map<QString, ASolid*>* getSolidMap();
    map<QString, APrimitive*>* getPrimitiveMap();

    // insert to solidMap and primitiveMap
    void insertToMap(APrimitive* primitive,
                     const QString& pName = "", const QString& sName = "");

    void insertCube(double width, double depth, double height,
                    const QString& pName = "", const QString& sName = "");
    void insertSphere(double radius, int slices, int stacks,
                      const QString& pName = "", const QString& sName = "");
    void insertCylinder(double radius, int slices, double height,
                        const QString& pName = "", const QString& sName = "");
    void insertCone(double radius, int slices, double height,
                    const QString& pName = "", const QString& sName = "");
    void insertPrism(double length, double sideLength, int sideCount = 3,
                     const QString& pName = "", const QString& sName = "");
    void insertPyramid(double sideLength, int sideCount = 3,
                       const QString& pName = "", const QString& sName = "");

    // fail if one solid is descent of the other
    bool insertSolid(ASolid* left, ASolid* right,
                     ASolid::BoolOperation operation,
                     const QString& sName = "");

    bool getIsDrawSolid() const;
    bool getIsDrawWire() const;
    void setDrawWire(const bool enabled);
    void setDrawSolid(const bool enabled);

    // for root solid only
    // return if delete successfully, false if not exist in map
    bool deleteSolid(QString solidName);
    // for root solid only
    // return if ungroup successfully, false if not exist in map
    bool ungroupSolid(QString solidName);
    // for primitive of root and leave solid
    // return if ungroup successfully, false if not exist in map
    bool deletePmt(APrimitive* primitive);

    // get solid from primitive
    ASolid* getSolidFromPmt(APrimitive* primitive);

    void selectSolid(ASolid* solid);

private:
    MainWindow* mainWindow;

    // if model changed since last saving to file
    bool modelChanged;

    // unique name and solid
    map<QString, ASolid*> solidMap;
    // used as a hint of next id
    unsigned int nextSolidID;

    // unique name and primitive
    map<QString, APrimitive*> primitiveMap;
    // used as a hint of next id
    unsigned int nextPrimiID;

    // help funtion for bool deleteSolid(QString solidName);
    void deleteSolidChild(ASolid* solid);

    bool isDrawSolid;
    bool isDrawWire;

    void setModelChanged(bool changed);

    ASolid* selectedSolid;
};

#endif // MODELMANAGER_H
