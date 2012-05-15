#include "FileManager.h"

#include <QFile>
#include <QTextStream>

#include "Solid/APrimitive.h"

FileManager::FileManager()
{
}

const QString FileManager::DOC_NAME = "April Project Model";
const QString FileManager::ROOT_NAME = "AprModel";

bool FileManager::readFile(const QString fileName,
                           ModelManager& modelManager)
{
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
            if (ele.tagName() == "Solids") {
            }
        }
    }
}

bool FileManager::writeFile(const QString fileName,
                            ModelManager& modelManager)
{
    QDomDocument doc(DOC_NAME);
    QDomElement root = doc.createElement(ROOT_NAME);
    doc.appendChild(root);

    QDomElement sldEle = doc.createElement("Solids");
    root.appendChild(sldEle);
    map<QString, ASolid*>* sMap = modelManager.getSolidMap();
    map<QString, ASolid*>::iterator sIter = sMap->begin();
    for (; sIter != sMap->end(); ++sIter) {
        if (sIter->second->isRoot()) {
            QDomElement ele = solidDom(doc, sIter->second);
            sldEle.appendChild(ele);
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
    return true;
}

QDomElement FileManager::solidDom(QDomDocument& doc, ASolid* solid)
{
    if (solid->isLeave()) {
        // leave solid
        QDomElement element = doc.createElement("Solid");
        // solid name
        element.setAttribute("name", solid->getName());

        APrimitive* pmt = solid->getPrimitive();
        QDomElement pEle = doc.createElement("Primitive");
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
        QDomElement element = doc.createElement("Solid");
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
}

void FileManager::vectorDom(QDomElement& element, const QString& name,
                            QDomDocument& doc, const Vector3d& vec)
{
    QDomElement ele = doc.createElement(name);
    ele.setAttribute("x", vec.x);
    ele.setAttribute("y", vec.y);
    ele.setAttribute("z", vec.z);
    element.appendChild(ele);
}
