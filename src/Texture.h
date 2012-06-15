#ifndef TEXTURE_H
#define TEXTURE_H

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

    QString getFileName();
    void setFileName(QString fileName);

private:
    // vertex count in texture
    int textVertexCount;
    // vertex position in texture
    QPair<double, double>* textVertexArray;
    // vertex id in primitive
    int* vertexPmtId;

    QString fileName;
};

#endif // TEXTURE_H
