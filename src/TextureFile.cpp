#include "TextureFile.h"

#include <QDomDocument>
#include <QFile>
#include <QPair>
#include <QTextStream>

#include <QDebug>

const QString TextureFile::DOC_NAME = "April_Project_Texture_Version1.0";
const QString TextureFile::ROOT_NAME = "AprMat";

TextureFile::TextureFile()
{
}

bool TextureFile::readFile(Texture* texture, const QString& filename)
{
    QDomDocument doc(DOC_NAME);
    QFile file(filename);
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

    QDomElement fileEle = root.firstChildElement("texture_file");
    texture->setFileName(fileEle.attribute("name"));

    QDomElement faceCntEle = root.firstChildElement("faceCnt");
    int faceCnt = faceCntEle.attribute("value").toInt();
    texture->setVertexCount(faceCnt * 3);

    QDomElement pmtEle = root.firstChildElement("vertexPmtCnt");
    int pmtCnt = pmtEle.attribute("value").toInt();
    texture->setVertexPmtCnt(pmtCnt);

    QDomElement facesEle = root.firstChildElement("faces");
    int index = 0;
    QDomElement faceEle = facesEle.firstChildElement("face");
    while (index < faceCnt) {
        QDomElement vEle = faceEle.firstChildElement("vertex");
        for (int i = 0; i < 3; ++i) {
            double x = vEle.attribute("x").toDouble();
            double y = vEle.attribute("y").toDouble();
            QPair<double, double> pos(x, y);
            int id = vEle.attribute("id").toInt();
            int idInPmt = vEle.attribute("idInPmt").toInt();

            texture->setVertexArray(id, pos);
            texture->setVertexPmtId(id, idInPmt);

            vEle = vEle.nextSiblingElement("vertex");
        }
        faceEle = faceEle.nextSiblingElement("face");
        ++index;
    }
    return true;
}

bool TextureFile::writeFile(const Texture& texture, const QString& filename)
{
    QDomDocument doc(DOC_NAME);
    QDomElement root = doc.createElement(ROOT_NAME);
    doc.appendChild(root);

    QDomElement fileEle = doc.createElement("texture_file");
    fileEle.setAttribute("name", texture.getFileName());
    root.appendChild(fileEle);

    int faceCnt = texture.getVertexCount() / 3;
    QDomElement faceCntEle = doc.createElement("faceCnt");
    faceCntEle.setAttribute("value", faceCnt);
    root.appendChild(faceCntEle);

    int pmtCnt = texture.getVertexPmtCnt();
    QDomElement pmtEle = doc.createElement("vertexPmtCnt");
    pmtEle.setAttribute("value", pmtCnt);
    root.appendChild(pmtEle);

    QDomElement facesEle = doc.createElement("faces");
    root.appendChild(facesEle);

    QPair<double, double>* vtxArr = texture.getVertexArray();
    int* pmtId = texture.getVertexPmtId();
    for (int i = 0; i < faceCnt; ++i) {
        QDomElement faceEle = doc.createElement("face");
        // face id
        faceEle.setAttribute("id", i);
        facesEle.appendChild(faceEle);
        // vertex
        for (int j = 0; j < 3; ++j) {
            QDomElement vertexEle = doc.createElement("vertex");
            int id = i * 3 + j;
            vertexEle.setAttribute("id", id);
            vertexEle.setAttribute("x", vtxArr[id].first);
            vertexEle.setAttribute("y", vtxArr[id].second);
            vertexEle.setAttribute("idInPmt", pmtId[id]);
            faceEle.appendChild(vertexEle);
        }
    }

    // Save to file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
    return true;
}
