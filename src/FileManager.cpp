#include "FileManager.h"

#include <QFile>
#include <QTextStream>

#include "Solid/APrimitive.h"

FileManager::FileManager()
{
}

const QString FileManager::DOC_NAME = "April_Project_Model_Version1.2";
const QString FileManager::ROOT_NAME = "AprModel";

bool FileManager::readFile(const QString fileName,
                           ModelManager& modelManager)
{
    modelManager.initialize();

    QDomDocument doc(DOC_NAME);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != ROOT_NAME) {
        return false;
    }

    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        QDomElement ele = node.toElement();
        if (!ele.isNull()) {
            if (ele.tagName() == "solids") {
                QDomNode sNode = ele.firstChild();
                while (!sNode.isNull()) {
                    if (!insertSolid(sNode, modelManager)) {
                        modelManager.initialize();
                        return false;
                    }
                    sNode = sNode.nextSibling();
                }
            } else if (ele.tagName() == "lighting") {
                QDomElement lEle = ele.firstChildElement("light");
                for (int i = 0; i < ModelManager::MAX_LIGHT_COUNT; ++i) {
                    int id = lEle.attribute("id").toInt();
                    if (!modelManager.openLight(id)) {
                        modelManager.initialize();
                        return false;
                    }
                    Lighting* light = modelManager.getLight(id);

                    bool isOn = lEle.attribute("isOn").toInt();
                    light->setIsOn(isOn);

                    QDomElement posEle = lEle.firstChildElement("position");
                    GLfloat pos[4];
                    pos[0] = posEle.attribute("x").toFloat();
                    pos[1] = posEle.attribute("y").toFloat();
                    pos[2] = posEle.attribute("z").toFloat();
                    pos[3] = posEle.attribute("w").toFloat();
                    light->setPosition(pos);

                    QDomElement ambEle = lEle.firstChildElement("ambient");
                    GLfloat amb[4];
                    amb[0] = ambEle.attribute("x").toFloat();
                    amb[1] = ambEle.attribute("y").toFloat();
                    amb[2] = ambEle.attribute("z").toFloat();
                    amb[3] = ambEle.attribute("w").toFloat();
                    light->setAmbient(amb);

                    QDomElement difEle = lEle.firstChildElement("diffuse");
                    GLfloat dif[4];
                    dif[0] = difEle.attribute("x").toFloat();
                    dif[1] = difEle.attribute("y").toFloat();
                    dif[2] = difEle.attribute("z").toFloat();
                    dif[3] = difEle.attribute("w").toFloat();
                    light->setDiffuse(dif);

                    QDomElement speEle = lEle.firstChildElement("specular");
                    GLfloat spe[4];
                    spe[0] = speEle.attribute("x").toFloat();
                    spe[1] = speEle.attribute("y").toFloat();
                    spe[2] = speEle.attribute("z").toFloat();
                    spe[3] = speEle.attribute("w").toFloat();
                    light->setSpecular(spe);

                    QDomElement dirEle = lEle.firstChildElement("direction");
                    GLfloat dir[4];
                    dir[0] = dirEle.attribute("x").toFloat();
                    dir[1] = dirEle.attribute("y").toFloat();
                    dir[2] = dirEle.attribute("z").toFloat();
                    dir[3] = dirEle.attribute("w").toFloat();
                    light->setDirection(dir);

                    QDomElement cutEle = lEle.firstChildElement("cutOff");
                    GLfloat cutOff = cutEle.attribute("value").toFloat();
                    light->setCutOff(cutOff);

                    lEle = lEle.nextSiblingElement("light");
                    if (lEle.isNull()) {
                        break;
                    }
                }
            }
        }
        node = node.nextSibling();
    }
    modelManager.setModelChanged();
    modelManager.setModelSaved();
    return true;
}

bool FileManager::insertSolid(QDomNode sNode, ModelManager &modelManager)
{
    map<QString, ASolid*>* sMap = modelManager.getSolidMap();
    map<QString, APrimitive*>* pMap = modelManager.getPrimitiveMap();

    QDomElement sEle = sNode.toElement();
    QString sName = sEle.attribute("name");
    if (sMap->find(sName) != sMap->end()) {
        // solid already exist, ignore
        return true;
    }

    QString operStr = sEle.attribute("operation");
    if (operStr == "") {
        // primitive
        QDomElement pEle = sEle.firstChildElement("primitive");
        QString pName = pEle.attribute("name");
        QString typeStr = pEle.attribute("type");
        if (typeStr == "cone") {
            double radius = pEle.attribute("radius").toDouble();
            int slices = pEle.attribute("slices").toInt();
            double height = pEle.attribute("height").toDouble();
            modelManager.insertCone(radius, slices, height, pName, sName);
        } else if (typeStr == "cube") {
            double width = pEle.attribute("width").toDouble();
            double depth = pEle.attribute("depth").toDouble();
            double height = pEle.attribute("height").toDouble();
            modelManager.insertCube(width, depth, height, pName, sName);
        } else if (typeStr == "cylinder") {
            double radius = pEle.attribute("radius").toDouble();
            int slices = pEle.attribute("slices").toInt();
            double height = pEle.attribute("height").toDouble();
            modelManager.insertCylinder(radius, slices, height, pName, sName);
        } else if (typeStr == "prism") {
            double length = pEle.attribute("length").toDouble();
            double sideLength = pEle.attribute("sideLength").toDouble();
            int sideCount = pEle.attribute("sideCount", "3").toInt();
            modelManager.insertPrism(length, sideLength, sideCount, pName, sName);
        } else if (typeStr == "pyramid") {
            double sideLength = pEle.attribute("sideLength").toDouble();
            int sideCount = pEle.attribute("sideCount", "3").toInt();
            modelManager.insertPyramid(sideLength, sideCount, pName, sName);
        } else if (typeStr == "sphere") {
            double radius = pEle.attribute("radius").toDouble();
            int slices = pEle.attribute("slices").toInt();
            int stacks = pEle.attribute("stacks").toInt();
            modelManager.insertSphere(radius, slices, stacks, pName, sName);
        } else {
            return false;
        }
        APrimitive* pmt = pMap->find(pName)->second;

        // color
        QDomElement cEle = pEle.firstChildElement("color");
        Vector3d color(cEle.attribute("r").toDouble(),
                       cEle.attribute("g").toDouble(),
                       cEle.attribute("b").toDouble());
        pmt->setColor(color);

        // rotate
        QDomElement ele = pEle.firstChildElement("rotate");
        if (!ele.isNull()) {
            Vector3d rotate(ele.attribute("x").toDouble(),
                            ele.attribute("y").toDouble(),
                            ele.attribute("z").toDouble());
            pmt->setRotate(rotate);
        }
        // scale
        ele = pEle.firstChildElement("scale");
        if (!ele.isNull()) {
            Vector3d scale(ele.attribute("x").toDouble(),
                           ele.attribute("y").toDouble(),
                           ele.attribute("z").toDouble());
            pmt->setScale(scale);
        }
        // translate
        ele = pEle.firstChildElement("translate");
        if (!ele.isNull()) {
            Vector3d translate(ele.attribute("x").toDouble(),
                               ele.attribute("y").toDouble(),
                               ele.attribute("z").toDouble());
            pmt->setTranslate(translate);
        }

    } else {
        // binary operation
        ASolid::BoolOperation operation = ASolid::BO_PRIMITIVE;
        for (int i = 0; i < ASolid::BOOL_OPERATION_COUNT; ++i) {
            if (ASolid::BOOL_OPERATION_NAME[i] == operStr) {
                operation = (ASolid::BoolOperation)i;
                break;
            }
        }
        if (operation == ASolid::BO_PRIMITIVE) {
            return false;
        }

        // left and right child
        QString left = sEle.attribute("left");
        QString right = sEle.attribute("right");
        if (left == "" || right == "") {
            return false;
        }

        // child information
        QDomNode cNode = sEle.firstChildElement("solid");
        if (cNode.isNull()) {
            return false;
        } else {
            if (!insertSolid(cNode, modelManager)) {
                return false;
            }
            cNode = cNode.nextSiblingElement("solid");
            if (cNode.isNull()) {
                return false;
            } else if (!insertSolid(cNode, modelManager)) {
                return false;
            }
        }

        // insert solid to modelManager
        map<QString, ASolid*>::iterator iter = sMap->find(left);
        if (iter == sMap->end()) {
            return false;
        }
        ASolid* leftSolid = iter->second;
        iter = sMap->find(right);
        if (iter == sMap->end()) {
            return false;
        }
        ASolid* rightSolid = iter->second;
        if (!modelManager.insertSolid(leftSolid, rightSolid,
                                      operation, sName)) {
            return false;
        }

        ASolid* solid = sMap->find(sName)->second;
        // rotate
        QDomElement ele = sEle.firstChildElement("rotate");
        if (!ele.isNull()) {
            Vector3d rotate(ele.attribute("x").toDouble(),
                            ele.attribute("y").toDouble(),
                            ele.attribute("z").toDouble());
            solid->setRotate(rotate);
        }
        // scale
        ele = sEle.firstChildElement("scale");
        if (!ele.isNull()) {
            Vector3d scale(ele.attribute("x").toDouble(),
                           ele.attribute("y").toDouble(),
                           ele.attribute("z").toDouble());
            solid->setScale(scale);
        }
        // translate
        ele = sEle.firstChildElement("translate");
        if (!ele.isNull()) {
            Vector3d translate(ele.attribute("x").toDouble(),
                               ele.attribute("y").toDouble(),
                               ele.attribute("z").toDouble());
            solid->setTranslate(translate);
        }
    }
    return true;
}

bool FileManager::writeFile(const QString fileName,
                            ModelManager& modelManager)
{
    QDomDocument doc(DOC_NAME);
    QDomElement root = doc.createElement(ROOT_NAME);
    doc.appendChild(root);

    // solids
    QDomElement sldEle = doc.createElement("solids");
    root.appendChild(sldEle);
    map<QString, ASolid*>* sMap = modelManager.getSolidMap();
    map<QString, ASolid*>::iterator sIter = sMap->begin();
    for (; sIter != sMap->end(); ++sIter) {
        if (sIter->second->isRoot()) {
            QDomElement ele = solidDom(doc, sIter->second);
            sldEle.appendChild(ele);
        }
    }

    // lighting
    QDomElement lightEle = doc.createElement("lighting");
    root.appendChild(lightEle);
    for (int i = 0; i < ModelManager::MAX_LIGHT_COUNT; ++i) {
        Lighting* light = modelManager.getLight(i);
        if (light) {
            QDomElement lEle = doc.createElement("light");
            lEle.setAttribute("id", light->getId());
            lEle.setAttribute("isOn", light->getIsOn());

            QDomElement posEle = doc.createElement("position");
            const GLfloat* position = light->getPosition();
            float4(posEle, position);
            lEle.appendChild(posEle);

            QDomElement ambEle = doc.createElement("ambient");
            GLfloat* amb = light->getAmbient();
            float4(ambEle, amb);
            lEle.appendChild(ambEle);

            QDomElement difEle = doc.createElement("diffuse");
            GLfloat* dif = light->getDiffuse();
            float4(difEle, dif);
            lEle.appendChild(difEle);

            QDomElement speEle = doc.createElement("specular");
            GLfloat* spe = light->getSpecular();
            float4(speEle, spe);
            lEle.appendChild(speEle);

            QDomElement dirEle = doc.createElement("direction");
            const GLfloat* dir = light->getDirection();
            float4(dirEle, dir);
            lEle.appendChild(dirEle);

            QDomElement cutEle = doc.createElement("cutOff");
            GLfloat cutOff = light->getCutOff();
            cutEle.setAttribute("value", cutOff);
            lEle.appendChild(cutEle);

            lightEle.appendChild(lEle);
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    modelManager.setModelSaved();
    return true;
}

void FileManager::float4(QDomElement &element, const GLfloat *f)
{
    element.setAttribute("x", f[0]);
    element.setAttribute("y", f[1]);
    element.setAttribute("z", f[2]);
    element.setAttribute("w", f[3]);
}

QDomElement FileManager::solidDom(QDomDocument& doc, ASolid* solid)
{
    if (solid->isLeave()) {
        // leave solid
        QDomElement element = doc.createElement("solid");
        // solid name
        element.setAttribute("name", solid->getName());

        APrimitive* pmt = solid->getPrimitive();
        QDomElement pEle = doc.createElement("primitive");
        // primitive name
        pEle.setAttribute("name", pmt->getName());
        // primitive type
        pEle.setAttribute("type", APrimitive::PRIMITIVE_TYPE_NAME[
                          pmt->getType()]);
        // primitive attributes
        pmtDom(doc, pEle, pmt);
        element.appendChild(pEle);

        return element;
    } else {
        // non-leave solid
        QDomElement element = doc.createElement("solid");
        // solid name
        element.setAttribute("name", solid->getName());

        Vector3d d0(0.0, 0.0, 0.0);
        Vector3d d1(1.0, 1.0, 1.0);
        if (solid->getRotate() != d0) {
            vectorDom(element, "rotate", doc, solid->getRotate());
        }
        if (solid->getScale() != d1) {
            vectorDom(element, "scale", doc, solid->getScale());
        }
        if (solid->getTranslate() != d0) {
            vectorDom(element, "translate", doc, solid->getTranslate());
        }

        // left child
        element.setAttribute("left",
                             solid->getLeftChild()->getName());
        // right child
        element.setAttribute("right",
                             solid->getRightChild()->getName());
        // operation
        element.setAttribute("operation", ASolid::BOOL_OPERATION_NAME[
                             solid->getOperation()]);

        element.appendChild(solidDom(doc, solid->getLeftChild()));
        element.appendChild(solidDom(doc, solid->getRightChild()));
        return element;
    }
}

void FileManager::pmtDom(QDomDocument& doc, QDomElement& element, APrimitive* pmt)
{
    QString attr = pmt->toString();
    QStringList lines = attr.split("\n", QString::SkipEmptyParts);

    int cnt = lines.count();
    for (int i = 0; i < cnt; ++i) {
        int equPos = lines[i].indexOf('=');
        QString attrName = lines[i].mid(0, equPos);
        QString value = lines[i].mid(equPos + 1);
        element.setAttribute(attrName, value);
    }

    Vector3d d0(0.0, 0.0, 0.0);
    Vector3d d1(1.0, 1.0, 1.0);
    if (pmt->getRotate() != d0) {
        vectorDom(element, "rotate", doc, pmt->getRotate());
    }
    if (pmt->getScale() != d1) {
        vectorDom(element, "scale", doc, pmt->getScale());
    }
    if (pmt->getTranslate() != d0) {
        vectorDom(element, "translate", doc, pmt->getTranslate());
    }

    // color
    vectorDom(element, "color", doc, pmt->getColor(), "r", "g", "b");
}

void FileManager::vectorDom(QDomElement& element, const QString& name,
                            QDomDocument& doc, const Vector3d& vec,
                            const QString& xLabel, const QString& yLabel,
                            const QString& zLabel)
{
    QDomElement ele = doc.createElement(name);
    ele.setAttribute(xLabel, vec.x);
    ele.setAttribute(yLabel, vec.y);
    ele.setAttribute(zLabel, vec.z);
    element.appendChild(ele);
}
