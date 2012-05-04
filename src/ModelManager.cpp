#include <QtOpenGL>

#include "ModelManager.h"

ModelManager::ModelManager(MainWindow* mainWindow) :
    mainWindow(mainWindow),
    modelChanged(false),
    solidMap(),
    nextSolidID(0),
    primitiveMap(),
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

bool ModelManager::getModelChanged()
{
    return modelChanged;
}

void ModelManager::initialize()
{
    modelChanged = false;
    solidMap.clear();
    primitiveMap.clear();
    nextSolidID = 0;
    nextPrimiID = 0;
    isDrawSolid = true;
    isDrawWire = false;
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
        if (iter->second->isRoot()) {
            iter->second->drawSolid();
        }
    }
}

void ModelManager::drawWire()
{
    map<QString, ASolid*>::iterator iter;
    for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
        // only draw leaves
        if (iter->second->isRoot()) {
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
    ++nextPrimiID;
    ++nextSolidID;
    modelChanged = true;
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
    modelChanged = true;
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

bool ModelManager::deleteSolid(QString solidName)
{
    map<QString, ASolid*>::iterator target = solidMap.find(solidName);
    if (target == solidMap.end()) {
        // target not found
        return false;
    } else {
        // target found, for root solid only
        ASolid* solid = target->second;
        if (solid->isRoot()) {
            // delete child
            deleteSolidChild(solid);
            // delete this solid
            solidMap.erase(target);
            modelChanged = true;
            return true;
        } else {
            return false;
        }
    }
}

void ModelManager::deleteSolidChild(ASolid* solid)
{
    if (solid != 0) {
        // delete child of this solid from solid map
        ASolid* left = solid->getLeftChild();
        ASolid* right = solid->getRightChild();
        if (left != 0 || right != 0) {
            map<QString, ASolid*>::iterator iter;
            for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
                if (iter->second == left) {
                    solidMap.erase(iter);
                    break;
                }
            }
            for (iter = solidMap.begin(); iter != solidMap.end(); ++iter) {
                if (iter->second == right) {
                    solidMap.erase(iter);
                    break;
                }
            }
            deleteSolidChild(left);
            deleteSolidChild(right);
        }
    }
}

bool ModelManager::ungroupSolid(QString solidName)
{
    map<QString, ASolid*>::iterator target = solidMap.find(solidName);
    if (target == solidMap.end()) {
        // target not found
        return false;
    } else {
        // target found, for root solid only
        ASolid* solid = target->second;
        if (solid->isRoot()) {
            // set child of this solid to be root
            solid->getLeftChild()->setParenet(0);
            solid->getRightChild()->setParenet(0);
            // delete this solid from solid map
            solidMap.erase(target);
            modelChanged = true;
            return true;
        } else {
            return false;
        }
    }
}
