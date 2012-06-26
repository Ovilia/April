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
    vertexPmtCnt(0),
    fileName(""),
    imageLoaded(false),
    textureId(0)
{
}

Texture::Texture(APrimitive* primitive) :
    textVertexCount(primitive->getFaceCount() * 3),
    vertexPmtCnt(primitive->getVertexCount()),
    fileName(""),
    imageLoaded(false),
    textureId(0)
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
    vertexPmtCnt(another.getVertexPmtCnt()),
    imageLoaded(false)
{
    if (textVertexCount > 0) {
        textVertexArray = new QPair<double, double>[textVertexCount];
        vertexPmtId = new int[textVertexCount];
        QPair<double, double>* vertex = another.getVertexArray();
        int* pmtId = another.getVertexPmtId();
        for (int i = 0; i < textVertexCount; ++i) {
            textVertexArray[i] = vertex[i];
            vertexPmtId[i] = pmtId[i];
        }
    }
    setFileName(another.getFileName());
}

Texture::~Texture()
{
    if (textVertexArray) {
        delete []textVertexArray;
    }
    if (vertexPmtId) {
        delete []vertexPmtId;
    }
    releaseTexture();
}

void Texture::releaseTexture()
{
    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
        textureId = 0;
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
    releaseTexture();

    if (textVertexCount > 0) {
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
    }
    setFileName(another.getFileName());
    return *this;
}

void Texture::generateTexture()
{
    if (fileName != "" && textVertexArray != 0) {
        // bind texture to image
        loadTextureImage();

        releaseTexture();
        // generate id
        glGenTextures(1, &textureId);

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, 4,//GL_RGBA,
                     textureImage.width(), textureImage.height(),
                     0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    }
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
    if (this->fileName != fileName) {
        this->fileName = fileName;
    }
    generateTexture();
}

QImage* Texture::getTextureImage()
{
    if (!imageLoaded) {
        loadTextureImage();
    }
    return &textureImage;
}

void Texture::loadTextureImage()
{
    if (fileName != "") {
        QImage buffer;
        if (!buffer.load(fileName)) {
            QImage dummy(128, 128, QImage::Format_RGB32);
            dummy.fill(0);
            buffer = dummy;
            qWarning("Texture image not loaded porperly");
        }
        textureImage = QGLWidget::convertToGLFormat(buffer);
        if (textureImage.isNull()) {
            qWarning("Texture image not convert porperly");
        }
        imageLoaded = true;
    }
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

GLuint Texture::getTextureId() const
{
    return textureId;
}
