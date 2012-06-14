#ifndef TEXTURE_H
#define TEXTURE_H

#include <QPair>

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

private:
    // vertex count in texture
    int textVertexCount;
    // vertex position in texture
    QPair<double, double>* textVertexArray;
    // vertex id in primitive
    int* vertexPmtId;
};

#endif // TEXTURE_H
