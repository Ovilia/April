#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QtOpenGL>
#include <QPair>
#include <QString>

#include "Solid/APrimitive.h"
#include "Vector3i.h"

class APrimitive;

class Texture
{
public:
    Texture();
    Texture(APrimitive* primitive);
    Texture(const Texture& another);
    ~Texture();

    const Texture& operator = (const Texture& another);

    int getVertexCount() const;
    QPair<double, double>* getVertexArray() const;

    int* getVertexPmtId() const;
    int getVertexPmtCnt() const;

    void setVertexCount(int count);
    void setVertexArray(QPair<double, double>* arr);
    void setVertexArray(int index, QPair<double, double> vertex);

    void setVertexPmtCnt(int count);
    void setVertexPmtId(int* pmtId);
    void setVertexPmtId(int index, int pmtId);

    QString getFileName() const;
    void setFileName(QString fileName);

    QImage* getTextureImage();

    GLuint* getTextureId() const;

private:
    // vertex count in texture
    int textVertexCount;
    // vertex position in texture
    QPair<double, double>* textVertexArray;
    // vertex id in primitive
    int* vertexPmtId;
    // vertex count in primitive
    int vertexPmtCnt;

    QString fileName;
    QImage* textureImage;
    void loadTextureImage();

    // length is faceCnt, which is textVertexCount / 3
    GLuint* textureId;
    void generateTexture();
    void releaseTexture();
};

#endif // TEXTURE_H
