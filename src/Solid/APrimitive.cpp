#include <ctime>
#include <cstdlib>

#include <QtOpenGL/qgl.h>

#include "APrimitive.h"

const double APrimitive::RANDOM_COLOR[RANDOM_COLOR_COUNT][3] =
{
    {0.00, 1.00, 1.00},
    {1.00, 0.00, 1.00},
    {1.00, 1.00, 0.00},
    {0.25, 0.75, 0.75},
    {0.75, 0.25, 0.75},
    {0.75, 0.75, 0.25},
    {0.00, 0.75, 1.00},
    {0.75, 1.00, 0.00},
    {1.00, 0.00, 0.75},
    {0.00, 1.00, 0.75},
    {0.75, 0.00, 1.00},
    {1.00, 0.75, 1.00}
};

APrimitive::APrimitive(PrimitiveType type, const QString& name) :
    name(name),
    primitiveType(type),
    rotate(0.0, 0.0, 0.0),
    scale(1.0, 1.0, 1.0),
    translate(0.0, 0.0, 0.0),
    isSelected(false),
    wireColor(Vector3d(0.3, 0.3, 0.3)),
    vertexCount(0),
    vertexArray(0),
    faceCount(0),
    faceArray(0)
{
    // set random color
    srand((unsigned)time(0));
    int index = rand() % RANDOM_COLOR_COUNT;
    color.x = RANDOM_COLOR[index][0];
    color.y = RANDOM_COLOR[index][1];
    color.z = RANDOM_COLOR[index][2];
}

APrimitive::~APrimitive()
{
    if (vertexArray) {
        delete []vertexArray;
    }
    if (faceArray) {
        delete []faceArray;
    }
}

APrimitive::PrimitiveType APrimitive::getType()
{
    return primitiveType;
}

void APrimitive::drawBefore()
{
    glPushMatrix();

    glRotated(rotate.x, 1.0, 0.0, 0.0);
    glRotated(rotate.y, 0.0, 1.0, 0.0);
    glRotated(rotate.z, 0.0, 0.0, 1.0);
    glScaled(scale.x, scale.y, scale.z);
    glTranslated(translate.x, translate.y, translate.z);
}

void APrimitive::drawSolid()
{
    drawBefore();

    glColor3d(color.x, color.y, color.z);

    drawAfter();
}

void APrimitive::drawWire()
{
    drawBefore();

    glColor3d(wireColor.x, wireColor.y, wireColor.z);

    // draw as line
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    drawAfter();

    // resolve drawing as fill
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
}

void APrimitive::drawAfter()
{
    glBegin(GL_TRIANGLES);
    for (int face = 0; face < faceCount; ++face) {
        int vertex = faceArray[face].x;
        glVertex3d(vertexArray[vertex].x,
                   vertexArray[vertex].y,
                   vertexArray[vertex].z);
        vertex = faceArray[face].y;
        glVertex3d(vertexArray[vertex].x,
                   vertexArray[vertex].y,
                   vertexArray[vertex].z);
        vertex = faceArray[face].z;
        glVertex3d(vertexArray[vertex].x,
                   vertexArray[vertex].y,
                   vertexArray[vertex].z);
    }
    glEnd();

    glPopMatrix();
}

QString APrimitive::getName() const
{
    return name;
}

void APrimitive::setName(const QString& name)
{
    this->name = name;
}

Vector3d APrimitive::getBoundingBox()
{
    return boundingBox;
}

Vector3d APrimitive::getRotate() const
{
    return rotate;
}

Vector3d APrimitive::getScale() const
{
    return scale;
}

Vector3d APrimitive::getTranslate() const
{
    return translate;
}

void APrimitive::setXRotate(const double rotate)
{
    this->rotate.x = rotate;
}

void APrimitive::setYRotate(const double rotate)
{
    this->rotate.y = rotate;
}

void APrimitive::setZRotate(const double rotate)
{
    this->rotate.z = rotate;
}

void APrimitive::setXScale(const double scale)
{
    this->scale.x = scale;
}

void APrimitive::setYScale(const double scale)
{
    this->scale.y = scale;
}

void APrimitive::setZScale(const double scale)
{
    this->scale.z = scale;
}

void APrimitive::setXTranslate(const double translate)
{
    this->translate.x = translate;
}

void APrimitive::setYTranslate(const double translate)
{
    this->translate.y = translate;
}

void APrimitive::setZTranslate(const double translate)
{
    this->translate.z = translate;
}

bool APrimitive::getSelected() const
{
    return isSelected;
}

void APrimitive::setSelected(const bool value)
{
    isSelected = value;
}
