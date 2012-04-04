#include <QtOpenGL>

#include "ModelManager.h"

ModelManager::ModelManager(MainWindow* mainWindow) :
    mainWindow(mainWindow),
    nextSolidID(0),
    nextPrimiID(0),
    isDrawSolid(true),
    isDrawWire(false)
{
}

ModelManager::~ModelManager()
{
    solidMap.clear();
    primitiveMap.clear();
}

map<QString, ASolid*>* ModelManager::getSolidMap()
{
    return &solidMap;
}

map<QString, APrimitive*>* ModelManager::getPrimitiveMap()
{
    return &primitiveMap;
}

void ModelManager::drawSolid()
{
    map<QString, ASolid*>::iterator iter;
    for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
        // only draw leaves
        if (iter->second->getParent() == 0) {
            iter->second->drawSolid();
        }
    }
}

void ModelManager::drawWire()
{
    map<QString, ASolid*>::iterator iter;
    for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
        // only draw leaves
        if (iter->second->getParent() == 0) {
            iter->second->drawWire();
        }
    }
}

void ModelManager::insertToMap(APrimitive* primitive)
{
    QString primiName = "Primitive " + QString::number(nextPrimiID);
    primitiveMap.insert(pair<QString, APrimitive*>(primiName, primitive));
    QString solidName = "Solid " + QString::number(nextSolidID);
    ASolid* solid = new ASolid(nextPrimiID, primitive, solidName);
    solidMap.insert(pair<QString, ASolid*>(solidName, solid));

    mainWindow->getViewManager()->repaintAll();
    mainWindow->getViewManager()->getToolWidget()->updateModelBox();

    ++nextPrimiID;
    ++nextSolidID;
}

void ModelManager::insertCube(double width, double depth, double height)
{
    insertToMap(new ACube(width, depth, height));
}

void ModelManager::insertSphere(double radius, int slices, int stacks)
{
    insertToMap(new ASphere(radius, slices, stacks));
}

void ModelManager::insertCylinder(double radius, int slices, double height)
{
    insertToMap(new ACylinder(radius, slices, height));
}

void ModelManager::insertCone(double radius, int slices, double height)
{
    insertToMap(new ACone(radius, slices, height));
}

void ModelManager::insertPrism(double length, double sideLength, int sideCount)
{
    insertToMap(new APrism(length, sideLength, sideCount));
}

void ModelManager::insertPyramid(double sideLength, int sideCount)
{
    insertToMap(new APyramid(sideLength, sideCount));
}

void ModelManager::insertSolid(ASolid* left, ASolid* right,
                               ASolid::BoolOperation operation)
{
    QString solidName = "Solid " + QString::number(nextSolidID);
    ASolid* solid = new ASolid(left, right, operation, solidName);
    left->setParenet(solid);
    right->setParenet(solid);
    solidMap.insert(pair<QString, ASolid*>(solidName, solid));

    ++nextSolidID;
}

bool ModelManager::getIsDrawSolid() const
{
    return isDrawSolid;
}

bool ModelManager::getIsDrawWire() const
{
    return isDrawWire;
}

void ModelManager::setDrawSolid(const bool enabled)
{
    isDrawSolid = enabled;
}

void ModelManager::setDrawWire(const bool enabled)
{
    isDrawWire = enabled;
}
