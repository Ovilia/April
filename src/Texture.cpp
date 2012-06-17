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
    vertexPmtId(0),
    vertexPmtCnt(0)
{
}

Texture::Texture(APrimitive* primitive) :
    textVertexCount(primitive->getFaceCount() * 3),
    vertexPmtCnt(primitive->getVertexCount())
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
    textVertexCount(another.getVertexCount()),
    vertexPmtCnt(another.getVertexPmtCnt())
{
    textVertexArray = new QPair<double, double>[textVertexCount];
    vertexPmtId = new int[textVertexCount];
    QPair<double, double>* vertex = another.getVertexArray();
    int* pmtId = another.getVertexPmtId();
    for (int i = 0; i < textVertexCount; ++i) {
        textVertexArray[i] = vertex[i];
        vertexPmtId[i] = pmtId[i];
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
    if (vertexPmtId) {
        delete []vertexPmtId;
    }
    textVertexCount = another.getVertexCount();
    vertexPmtCnt = another.getVertexPmtCnt();
    textVertexArray = new QPair<double, double>[textVertexCount];
    vertexPmtId = new int[textVertexCount];
    QPair<double, double>* vertex = another.getVertexArray();
    int* pmtId = another.getVertexPmtId();
    for (int i = 0; i < textVertexCount; ++i) {
        textVertexArray[i] = vertex[i];
        vertexPmtId[i] = pmtId[i];
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

QString Texture::getFileName() const
{
    return fileName;
}

void Texture::setFileName(QString fileName)
{
    this->fileName = fileName;
}

int* Texture::getVertexPmtId() const
{
    return vertexPmtId;
}

int Texture::getVertexPmtCnt() const
{
    return vertexPmtCnt;
}

void Texture::setVertexCount(int count)
{
    textVertexCount = count;

    if (textVertexArray) {
        delete []textVertexArray;
    }
    textVertexArray = new QPair<double, double>[count];
    if (vertexPmtId) {
        delete []vertexPmtId;
    }
    vertexPmtId = new int[count];

    for (int i = 0; i < count; ++i) {
        textVertexArray[i] = QPair<double, double>(0.0, 0.0);
        vertexPmtId[i] = 0;
    }
}

void Texture::setVertexArray(QPair<double, double>* arr)
{
    for (int i = 0; i < textVertexCount; ++i) {
        textVertexArray[i] = arr[i];
    }
}

void Texture::setVertexArray(int index, QPair<double, double> vertex)
{
    textVertexArray[index] = vertex;
}

void Texture::setVertexPmtCnt(int count)
{
    vertexPmtCnt = count;
}

void Texture::setVertexPmtId(int* pmtId)
{
    for (int i = 0; i < textVertexCount; ++i) {
        vertexPmtId[i] = pmtId[i];
    }
}

void Texture::setVertexPmtId(int index, int pmtId)
{
    vertexPmtId[index] = pmtId;
}
