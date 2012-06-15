#include "Texture.h"

#include "Solid/ACone.h"
#include "Solid/ACube.h"
#include "Solid/ACylinder.h"
#include "Solid/APrism.h"
#include "Solid/APyramid.h"
#include "Solid/ASphere.h"

Texture::Texture() :
    textVertexCount(0),
    textVertexArray(0),
    vertexPmtId(0)
{
}

Texture::Texture(APrimitive* primitive) :
    textVertexCount(primitive->getFaceCount() * 3)
{
    if (textVertexCount > 0) {
        const QPair<double, double>* defPos =
                primitive->getDefaultTextVertexPos();
        const int* defId = primitive->getDefaultPmtId();

        textVertexArray = new QPair<double, double>[textVertexCount];
        vertexPmtId = new int[textVertexCount];
        for (int i = 0; i < textVertexCount; ++i) {
            textVertexArray[i] = defPos[i];
            vertexPmtId[i] = defId[i];
        }
    }
}

Texture::Texture(const Texture& another) :
    textVertexCount(another.getVertexCount())
{
    textVertexArray = new QPair<double, double>[textVertexCount];
    QPair<double, double>* vertex = another.getVertexArray();
    for (int i = 0; i < textVertexCount; ++i) {
        textVertexArray[i] = vertex[i];
    }
}

Texture::~Texture()
{
    if (textVertexArray) {
        delete []textVertexArray;
    }
    if (vertexPmtId) {
        delete []vertexPmtId;
    }
}

const Texture& Texture::operator = (const Texture& another)
{
    if (textVertexArray) {
        delete []textVertexArray;
    }
    textVertexCount = another.getVertexCount();
    textVertexArray = new QPair<double, double>[textVertexCount];
    QPair<double, double>* vertex = another.getVertexArray();
    for (int i = 0; i < textVertexCount; ++i) {
        textVertexArray[i] = vertex[i];
    }
    return *this;
}

int Texture::getVertexCount() const
{
    return textVertexCount;
}

QPair<double, double>* Texture::getVertexArray() const
{
    return textVertexArray;
}

QString Texture::getFileName()
{
    return fileName;
}

void Texture::setFileName(QString fileName)
{
    this->fileName = fileName;
}
