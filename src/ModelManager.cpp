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
    isDrawWire(false),
    selectedSolid(0)
{
    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        lighting[i] = 0;
    }
}

ModelManager::~ModelManager()
{
    solidMap.clear();
    primitiveMap.clear();

    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        if (lighting[i] != 0) {
            delete lighting[i];
        }
    }
}

bool ModelManager::getModelChanged()
{
    return modelChanged;
}

void ModelManager::setModelSaved()
{
    setModelChanged(false);
}

void ModelManager::setModelChanged()
{
    setModelChanged(true);
    mainWindow->getViewManager()->getToolWidget()->updateModelBox();
}

void ModelManager::setModelChanged(bool changed)
{
    modelChanged = changed;
}

void ModelManager::initialize()
{
    setModelChanged(false);
    solidMap.clear();
    primitiveMap.clear();
    nextSolidID = 0;
    nextPrimiID = 0;
    isDrawSolid = true;
    isDrawWire = false;
    selectedSolid = 0;

    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        if (lighting[i]) {
            delete lighting[i];
            lighting[i] = 0;
        }
    }
    lightChanged = true;

    ToolWidget* tool = mainWindow->getViewManager()->getToolWidget();
    tool->updateModelBox();
    tool->updateLightBox();
    tool->updateLightCanOpen();
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

void ModelManager::insertToMap(APrimitive* primitive,
                               const QString& pName, const QString& sName)
{
    if (pName == "" || sName == "") {
        // assign name by modelManager
        while (true) {
            QString primiName = "Primitive " + QString::number(nextPrimiID);
            if (primitiveMap.find(primiName) == primitiveMap.end()) {
                // new name found
                primitive->setName(primiName);
                primitiveMap.insert(pair<QString, APrimitive*>(
                                        primiName, primitive));
                break;
            }
            ++nextPrimiID;
        }
        while (true) {
            QString solidName = "Solid " + QString::number(nextSolidID);
            if (solidMap.find(solidName) == solidMap.end()) {
                // new name found
                ASolid* solid = new ASolid(primitive, solidName);
                solidMap.insert(pair<QString, ASolid*>(solidName, solid));
                break;
            }
            ++nextSolidID;
        }
    } else {
        primitive->setName(pName);
        primitiveMap.insert(pair<QString, APrimitive*>(pName, primitive));

        ASolid* solid = new ASolid(primitive, sName);
        solidMap.insert(pair<QString, ASolid*>(sName, solid));
    }
    setModelChanged(true);
}

void ModelManager::insertCube(double width, double depth, double height,
                              const QString& pName, const QString& sName)
{
    insertToMap(new ACube(width, depth, height), pName, sName);
}

void ModelManager::insertSphere(double radius, int slices, int stacks,
                                const QString& pName, const QString& sName)
{
    insertToMap(new ASphere(radius, slices, stacks), pName, sName);
}

void ModelManager::insertCylinder(double radius, int slices, double height,
                                  const QString& pName, const QString& sName)
{
    insertToMap(new ACylinder(radius, slices, height), pName, sName);
}

void ModelManager::insertCone(double radius, int slices, double height,
                              const QString& pName, const QString& sName)
{
    insertToMap(new ACone(radius, slices, height), pName, sName);
}

void ModelManager::insertPrism(double length, double sideLength, int sideCount,
                               const QString& pName, const QString& sName)
{
    insertToMap(new APrism(length, sideLength, sideCount), pName, sName);
}

void ModelManager::insertPyramid(double sideLength, int sideCount,
                                 const QString& pName, const QString& sName)
{
    insertToMap(new APyramid(sideLength, sideCount), pName, sName);
}

bool ModelManager::insertSolid(ASolid* left, ASolid* right,
                               ASolid::BoolOperation operation,
                               const QString& sName)
{
    if (left->hasDescent(right) || right->hasDescent(left)) {
        return false;
    }
    if (sName == "") {
        while (true) {
            QString solidName = "Solid " + QString::number(nextSolidID);
            if (solidMap.find(solidName) == solidMap.end()) {
                ASolid* solid = new ASolid(left, right, operation, solidName);
                left->setParenet(solid);
                right->setParenet(solid);
                solidMap.insert(pair<QString, ASolid*>(solidName, solid));
                break;
            }
            ++nextSolidID;
        }
    } else {
        ASolid* solid = new ASolid(left, right, operation, sName);
        left->setParenet(solid);
        right->setParenet(solid);
        solidMap.insert(pair<QString, ASolid*>(sName, solid));
    }
    setModelChanged(true);
    return true;
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
            setModelChanged(true);
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
        APrimitive* pmt = solid->getPrimitive();
        if (pmt) {
            primitiveMap.erase(pmt->getName());
            return;
        }
        ASolid* left = solid->getLeftChild();
        ASolid* right = solid->getRightChild();
        if (left != 0 || right != 0) {
            deleteSolidChild(left);
            deleteSolidChild(right);
            solidMap.erase(left->getName());
            solidMap.erase(right->getName());
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
            setModelChanged(true);
            return true;
        } else {
            return false;
        }
    }
}

ASolid* ModelManager::getSolidFromPmt(APrimitive* primitive)
{
    map<QString, ASolid*>::iterator sIter;
    for (sIter = solidMap.begin(); sIter != solidMap.end(); ++sIter) {
        if (primitive == sIter->second->getPrimitive()) {
            return sIter->second;
        }
    }
    // not found
    return 0;
}

void ModelManager::selectSolid(ASolid* solid)
{
    if (selectedSolid) {
        selectedSolid->setSelected(false);
    }
    selectedSolid = solid;
    if (solid) {
        solid->setSelected(true);
    }
}

bool ModelManager::deletePmt(APrimitive* primitive)
{
    ASolid* solid = getSolidFromPmt(primitive);
    if (!solid) {
        return false;
    }
    if (solid->isLeave() && solid->isRoot()) {
        // delete solid
        map<QString, ASolid*>::iterator sIter;
        for (sIter = solidMap.begin(); sIter != solidMap.end(); ++sIter) {
            if (sIter->second == solid) {
                solidMap.erase(sIter);

                // delete primitive
                map<QString, APrimitive*>::iterator pIter;
                for (pIter = primitiveMap.begin();
                     pIter != primitiveMap.end(); ++pIter) {
                    if (pIter->second == primitive) {
                        primitiveMap.erase(pIter);
                        return true;
                    }
                }
                // primitive not found
                return false;
            }
        }
    }
    return false;
}

bool ModelManager::canOpenLight() const
{
    if (firstOffLight() == NO_MORE_LIGHT) {
        return false;
    } else {
        return true;
    }
}

int ModelManager::firstOffLight() const
{
    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        if (lighting[i] == 0) {
            return i;
        }
    }
    // no more light
    return NO_MORE_LIGHT;
}

bool ModelManager::openLight()
{
    int id = firstOffLight();
    if (id == NO_MORE_LIGHT) {
        return false;
    }
    lighting[id] = new Lighting((GLuint)id);
    lighting[id]->setIsOn(true);
    lightChanged = true;
    return true;
}

bool ModelManager::closeLight(int id)
{
    if (id >= 0 && id < MAX_LIGHT_COUNT) {
        if (lighting[id])  {
            delete lighting[id];
            lighting[id] = 0;
            lightChanged = true;
            return true;
        }
    }
    return false;
}

Lighting* ModelManager::getLight(int id) const
{
    if (id >= 0 && id < MAX_LIGHT_COUNT) {
        return lighting[id];
    } else {
        return 0;
    }
}

bool ModelManager::getLightChanged() const
{
    return lightChanged;
}

void ModelManager::setLightUnchanged()
{
    lightChanged = false;
}

bool ModelManager::allLightOff() const
{
    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        if (lighting[i] && lighting[i]->getIsOn()) {
            return false;
        }
    }
    return true;
}

Lighting* ModelManager::getLight(QString name) const
{
    for (int i = 0; i < MAX_LIGHT_COUNT; ++i) {
        if (lighting[i] && lighting[i]->getName() == name) {
            return lighting[i];
        }
    }
    return 0;
}

bool ModelManager::openLight(int id)
{
    if (id < 0 || id > MAX_LIGHT_COUNT || lighting[id]) {
        return false;
    }
    lighting[id] = new Lighting((GLuint)id);
    lighting[id]->setIsOn(true);
    return true;
}
