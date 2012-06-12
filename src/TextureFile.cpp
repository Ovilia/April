#include "TextureFile.h"

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

const QString TextureFile::DOC_NAME = "April_Project_Material_Version1.0";
const QString TextureFile::ROOT_NAME = "AprMat";

TextureFile::TextureFile()
{
}

Texture TextureFile::readFile(QString filename)
{

}

void TextureFile::writeFile(const Texture& filename)
{
    QDomDocument doc(DOC_NAME);
    QDomElement root = doc.createElement(ROOT_NAME);
    doc.appendChild(root);

//    QDomElement
}
