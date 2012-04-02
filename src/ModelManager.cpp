#include <QtOpenGL>

#include "ModelManager.h"

ModelManager::ModelManager(MainWindow* mainWindow) :
    mainWindow(mainWindow),
    nextSolidID(0),
    nextPrimiID(0)
{
}

ModelManager::~ModelManager()
{

}

void ModelManager::drawSolid()
{
    map<QString, ASolid*>::iterator iter;
    for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
        iter->second->drawSolid();
    }
}

void ModelManager::drawWire()
{
    map<QString, ASolid*>::iterator iter;
    for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
        iter->second->drawWire();
    }
}

void ModelManager::insertToMap(APrimitive* primitive)
{
    QString primiName = "Primitive " + nextPrimiID;
    primitiveMap.insert(pair<QString, APrimitive*>(primiName, primitive));
    QString solidName = "Solid " + nextSolidID;
    ASolid* solid = new ASolid(nextPrimiID, primitive, solidName);
    solidMap.insert(pair<QString, ASolid*>(solidName, solid));

    ++nextPrimiID;
    ++nextSolidID;
}

void ModelManager::insertCube(double width, double depth, double height)
{
    insertToMap(new ACube(width, depth, height));
}

void ModelManager::insertSphere(double radius, int slices, int stacks)
{

}

void ModelManager::insertCylinder(double radius, int slices, double height)
{

}

void ModelManager::insertCone(double radius, int slices, double height)
{

}

void ModelManager::insertPrism(double length, double sideLength, int sideCount)
{

}

void ModelManager::insertPyramid(double sideLength, int sideCount)
{

}
