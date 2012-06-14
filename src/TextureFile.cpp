#include "TextureFile.h"

#include <QDomDocument>
#include <QFile>
#include <QPair>
#include <QTextStream>

const QString TextureFile::DOC_NAME = "April_Project_Material_Version1.0";
const QString TextureFile::ROOT_NAME = "AprMat";

TextureFile::TextureFile()
{
}

Texture TextureFile::readFile(const QString& filename)
{

}

void TextureFile::writeFile(const Texture& texture, const QString& filename)
{
    QDomDocument doc(DOC_NAME);
    QDomElement root = doc.createElement(ROOT_NAME);
    doc.appendChild(root);

    int faceCnt = texture.getVertexCount() / 3;
    int vtxCnt = texture.getVertexCount();
    QPair<double, double>* vtxArr = texture.getVertexArray();
    for (int i = 0; i < faceCnt; ++i) {
        QDomElement faceEle = doc.createElement("face");
        // face id
        faceEle.setAttribute("id", i);
        root.appendChild(faceEle);
        // vertex
        for (int j = 0; j < 3; ++j) {
            QDomElement vertexEle = doc.createElement("vertex");
            int id = i * 3 + j;
            vertexEle.setAttribute("id", id);
            vertexEle.setAttribute("x", vtxArr[id].first);
            vertexEle.setAttribute("y", vtxArr[id].second);
            faceEle.appendChild(vertexEle);
        }
    }

}
