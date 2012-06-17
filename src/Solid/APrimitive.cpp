#include "APrimitive.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

#include <qmath.h>
#include <ctime>
#include <cstdlib>

#include <QtOpenGL>

const QString APrimitive::PRIMITIVE_TYPE_NAME[PRIMITIVE_TYPE_COUNT] = {
    "none", "cone", "cube", "cylinder", "prism", "pyramid", "sphere"
};

const double APrimitive::RANDOM_COLOR[RANDOM_COLOR_COUNT][3] =
{
    {0.50, 1.00, 1.00},
    {1.00, 0.50, 1.00},
    {1.00, 1.00, 0.50},
    {0.45, 0.75, 0.75},
    {0.75, 0.45, 0.75},
    {0.75, 0.75, 0.45},
    {0.80, 0.55, 1.00},
    {0.55, 1.00, 0.80},
    {1.00, 0.80, 0.55},
    {0.80, 1.00, 0.55},
    {0.55, 0.80, 1.00},
    {1.00, 0.55, 1.00},
    {0.40, 1.00, 1.00},
    {1.00, 0.40, 1.00},
    {1.00, 1.00, 0.40},
    {0.40, 0.40, 1.00}
};

const Vector3d APrimitive::DEFAULT_ROTATE = Vector3d(0.0, 0.0, 0.0);
const Vector3d APrimitive::DEFAULT_SCALE = Vector3d(1.0, 1.0, 1.0);
const Vector3d APrimitive::DEFAULT_TRANSLATE = Vector3d(0.0, 0.0, 0.0);

const Vector3d APrimitive::SELECTED_PMT_COLOR = Vector3d(1.0, 0.8, 0.0);
const Vector3d APrimitive::SELECTED_SLD_COLOR = Vector3d(0.0, 0.6, 0.6);

APrimitive::APrimitive(PrimitiveType type, const QString& name) :
    name(name),
    primitiveType(type),

    rotate(DEFAULT_ROTATE),
    scale(DEFAULT_SCALE),
    translate(DEFAULT_TRANSLATE),

    wireColor(Vector3d(0.3, 0.3, 0.3)),

    vertexCount(0),
    vertexArray(0),
    faceCount(0),
    faceArray(0),

    defaultTextVertexPos(0),
    defaultPmtId(0),
    defaultTextFaceVertex(0),

    oldScale(1.0, 1.0, 1.0),
    oldTrans(0.0, 0.0, 0.0),

    isSelected(false),

    material(0),
    texture(0)
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

    if (defaultTextVertexPos) {
        delete []defaultTextVertexPos;
    }
    if (defaultPmtId) {
        delete []defaultPmtId;
    }
    if (defaultTextFaceVertex) {
        delete []defaultTextFaceVertex;
    }

    if (material) {
        delete material;
    }
    if (texture) {
        delete texture;
    }
}

APrimitive::PrimitiveType APrimitive::getType() const
{
    return primitiveType;
}

void APrimitive::drawBefore() const
{
    glPushMatrix();
    glRotated(rotate.z, 0.0, 0.0, 1.0);
    glRotated(rotate.y, 0.0, 1.0, 0.0);
    glRotated(rotate.x, 1.0, 0.0, 0.0);
    glTranslated(translate.x, translate.y, translate.z);
    glScaled(scale.x, scale.y, scale.z);
}

void APrimitive::drawSolid() const
{
    drawBefore();

    glColor3d(color.x, color.y, color.z);

    drawAfter();
}

void APrimitive::drawWire() const
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

void APrimitive::drawAfter() const
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

    // draw vertex if is selected
    if (isSelected) {
        glPointSize(7.0f);
        glColor3d(selectColor.x, selectColor.y, selectColor.z);
        glBegin(GL_POINTS);
        for (int i = 0; i < vertexCount; ++i) {
            glVertex3d(vertexArray[i].x, vertexArray[i].y, vertexArray[i].z);
        }
        glEnd();
        glPointSize(1.0f);
    }

    glPopMatrix();
}

bool APrimitive::getSelected() const
{
    return isSelected;
}

void APrimitive::setSelected(const bool value, const bool usePmtColor)
{
    isSelected = value;
    if (usePmtColor) {
        selectColor = SELECTED_PMT_COLOR;
    } else {
        selectColor = SELECTED_SLD_COLOR;
    }
}

void APrimitive::drawBoundingBox() const
{
    glColor3d(selectColor.x, selectColor.y, selectColor.z);
    glBegin(GL_LINE_STRIP);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
    glEnd();
    glBegin(GL_LINES);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
        glVertex3d(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
    glEnd();
}

QString APrimitive::getName() const
{
    return name;
}

void APrimitive::setName(const QString& name)
{
    this->name = name;
}

Vector3d APrimitive::getBoundingBoxMin()
{
    return boundingBoxMin;
}

Vector3d APrimitive::getBoundingBoxMax()
{
    return boundingBoxMax;
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
//    resetBoundBoxRotate();
}

void APrimitive::setYRotate(const double rotate)
{
    this->rotate.y = rotate;
//    resetBoundBoxRotate();
}

void APrimitive::setZRotate(const double rotate)
{
    this->rotate.z = rotate;
//    resetBoundBoxRotate();
}

void APrimitive::setRotate(const Vector3d &rotate)
{
    this->rotate = rotate;
//    resetBoundBoxRotate();
}

void APrimitive::setXScale(const double scale)
{
    this->scale.x = scale;
//    resetBoundBoxScale(this->scale);
}

void APrimitive::setYScale(const double scale)
{
    this->scale.y = scale;
//    resetBoundBoxScale(this->scale);
}

void APrimitive::setZScale(const double scale)
{
    this->scale.z = scale;
//    resetBoundBoxScale(this->scale);
}

void APrimitive::setScale(const Vector3d &scale)
{
    this->scale = scale;
//    resetBoundBoxScale(this->scale);
}

void APrimitive::setXTranslate(const double translate)
{
    this->translate.x = translate;
//    resetBoundBoxTrans(this->translate);
}

void APrimitive::setYTranslate(const double translate)
{
    this->translate.y = translate;
//    resetBoundBoxTrans(this->translate);
}

void APrimitive::setZTranslate(const double translate)
{
    this->translate.z = translate;
//    resetBoundBoxTrans(this->translate);
}

void APrimitive::setTranslate(const Vector3d &translate)
{
    this->translate = translate;
//    resetBoundBoxTrans(this->translate);
}

Vector3d APrimitive::getColor() const
{
    return color;
}

void APrimitive::setColor(Vector3d color)
{
    this->color = color;
}

void APrimitive::resetBoundBoxRotate()
{
    if (vertexCount > 0) {
        // rotate matrix
        double cos = qCos(rotate.x * M_PI / 180.0);
        double sin = qSin(rotate.x * M_PI / 180.0);
        double xArr[16] = {1.0, 0.0, 0.0, 0.0,
                           0.0, cos, sin, 0.0,
                           0.0, -sin, cos, 0.0,
                           0.0, 0.0, 0.0, 1.0};
        MatrixD xRot(4, xArr);

        cos = qCos(rotate.y * M_PI / 180.0);
        sin = qSin(rotate.y * M_PI / 180.0);
        double yArr[16] = {cos, 0.0, -sin, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           sin, 0.0, cos, 0.0,
                           0.0, 0.0, 0.0, 1.0};
        MatrixD yRot(4, yArr);

        cos = qCos(rotate.z * M_PI / 180.0);
        sin = qSin(rotate.z * M_PI / 180.0);
        double zArr[16] = {cos, sin, 0.0, 0.0,
                          -sin, cos, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
        MatrixD zRot(4, zArr);

        MatrixD rot = xRot.multiply(yRot).multiply(zRot);

        boundingBoxMin = transform(vertexArray[0], rot);
        boundingBoxMax = boundingBoxMin;
        for (int i = 1; i < vertexCount; ++i) {
            Vector3d vertex = transform(vertexArray[i], rot);
            if (vertex.x < boundingBoxMin.x) {
                boundingBoxMin.x = vertex.x;
            } else if (vertex.x > boundingBoxMax.x) {
                boundingBoxMax.x = vertex.x;
            }
            if (vertex.y < boundingBoxMin.y) {
                boundingBoxMin.y = vertex.y;
            } else if (vertex.y > boundingBoxMax.y) {
                boundingBoxMax.y = vertex.y;
            }
            if (vertex.z < boundingBoxMin.z) {
                boundingBoxMin.z = vertex.z;
            } else if (vertex.z > boundingBoxMax.z) {
                boundingBoxMax.z = vertex.z;
            }
        }
        oldScale = Vector3d(1.0, 1.0, 1.0);
        oldTrans = Vector3d(0.0, 0.0, 0.0);
    }
}

void APrimitive::resetBoundBoxScale(Vector3d newScale)
{
    if (oldScale.x > EPSILON) {
        double ratio = newScale.x / oldScale.x;
        boundingBoxMin.x *= ratio;
        boundingBoxMax.x *= ratio;
    } else {
        boundingBoxMin.x = 0.0;
        boundingBoxMax.x = 0.0;
    }
    if (oldScale.y > EPSILON) {
        double ratio = newScale.y / oldScale.y;
        boundingBoxMin.y *= ratio;
        boundingBoxMax.y *= ratio;
    } else {
        boundingBoxMin.y = 0.0;
        boundingBoxMax.y = 0.0;
    }
    if (oldScale.z > EPSILON) {
        double ratio = newScale.z / oldScale.z;
        boundingBoxMin.z *= ratio;
        boundingBoxMax.z *= ratio;
    } else {
        boundingBoxMin.z = 0.0;
        boundingBoxMax.z = 0.0;
    }
    oldScale = newScale;
}

void APrimitive::resetBoundBoxTrans(Vector3d newTrans)
{
    Vector3d delta = newTrans - oldTrans;
    boundingBoxMin = boundingBoxMin + delta;
    boundingBoxMax = boundingBoxMax + delta;
    oldTrans = newTrans;
}

Vector3d APrimitive::transform(Vector3d vertex, const MatrixD& mat) const
{
    Vector3d result;
    result.x = vertex.x * mat.getElement(0) +
            vertex.y * mat.getElement(4) +
            vertex.z * mat.getElement(8) +
            mat.getElement(12);
    result.y = vertex.x * mat.getElement(1) +
            vertex.y * mat.getElement(5) +
            vertex.z * mat.getElement(9) +
            mat.getElement(13);
    result.z = vertex.x * mat.getElement(2) +
            vertex.y * mat.getElement(6) +
            vertex.z * mat.getElement(10) +
            mat.getElement(14);
    return result;
}

void APrimitive::setMaterial(const Material& material)
{
    if (this->material) {
        delete this->material;
    }
    this->material = new Material(material);
}

void APrimitive::eraseMaterial()
{
    if (material) {
        delete material;
    }
}

Material* APrimitive::getMaterial() const
{
    return material;
}

bool APrimitive::setTexture(const Texture& texture)
{
    if (texture.getVertexPmtCnt() == vertexCount &&
            texture.getVertexCount() / 3 == faceCount) {
        if (this->texture) {
            delete this->texture;
        }
        this->texture = new Texture(texture);
        return true;
    } else {
        return false;
    }
}

void APrimitive::eraseTexture()
{
    if (texture) {
        delete texture;
    }
}

Texture* APrimitive::getTexture() const
{
    return texture;
}

int APrimitive::getVertexCount() const
{
    return vertexCount;
}

Vector3d* APrimitive::getVertexArray() const
{
    return vertexArray;
}

int APrimitive::getFaceCount() const
{
    return faceCount;
}

Vector3i* APrimitive::getFaceArray() const
{
    return faceArray;
}

int APrimitive::getTextVertexCount()
{
    return faceCount * 3;
}
