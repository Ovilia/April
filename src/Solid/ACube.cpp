#include <QtOpenGL>

#include "ACube.h"
#include "Vector3d.h"
#include "Vector3i.h"

const double ACube::DEFAULT_WIDTH = 1.0;
const double ACube::DEFAULT_DEPTH = 1.0;
const double ACube::DEFAULT_HEIGHT = 1.0;

ACube::ACube() :
    APrimitive(APrimitive::PT_CUBE),
    width(DEFAULT_WIDTH),
    depth(DEFAULT_DEPTH),
    height(DEFAULT_HEIGHT)
{
    reset(width, depth, height);
}

ACube::ACube(double width, double depth, double height) :
    APrimitive(APrimitive::PT_CUBE),
    width(width),
    depth(depth),
    height(height)
{
    reset(width, depth, height);
}

ACube::~ACube()
{

}

double ACube::getWidth()
{
    return width;
}

double ACube::getDepth()
{
    return depth;
}

double ACube::getHeight()
{
    return height;
}

void ACube::reset(double width, double depth, double height)
{
    this->width = width;
    this->depth = depth;
    this->height = height;

    boundingBoxMin = Vector3d(-width / 2.0, 0.0, -depth / 2.0);
    boundingBoxMax = Vector3d(width / 2.0, height, depth / 2.0);

    // vertex position
    vertexCount = 8;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double rightPos = width / 2;
    double leftPos = -rightPos;
    double topPos = height;
    double bottomPos = 0;
    double nearPos = depth / 2;
    double farPos = -nearPos;
    vertexArray[0] = Vector3d(rightPos, topPos, nearPos);
    vertexArray[1] = Vector3d(rightPos, topPos, farPos);
    vertexArray[2] = Vector3d(leftPos, topPos, farPos);
    vertexArray[3] = Vector3d(leftPos, topPos, nearPos);
    vertexArray[4] = Vector3d(rightPos, bottomPos, nearPos);
    vertexArray[5] = Vector3d(rightPos, bottomPos, farPos);
    vertexArray[6] = Vector3d(leftPos, bottomPos, farPos);
    vertexArray[7] = Vector3d(leftPos, bottomPos, nearPos);

    // face
    faceCount = 12;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    faceArray[0] = Vector3i(0, 4, 5);
    faceArray[1] = Vector3i(0, 5, 1);
    faceArray[2] = Vector3i(1, 6, 5);
    faceArray[3] = Vector3i(1, 2, 6);
    faceArray[4] = Vector3i(2, 7, 6);
    faceArray[5] = Vector3i(2, 3, 7);
    faceArray[6] = Vector3i(3, 7, 4);
    faceArray[7] = Vector3i(0, 3, 4);
    faceArray[8] = Vector3i(0, 1, 2);
    faceArray[9] = Vector3i(0, 2, 3);
    faceArray[10] = Vector3i(4, 5, 7);
    faceArray[11] = Vector3i(5, 6, 7);

    // init parameters
    if (defaultTextVertexPos) {
        delete []defaultTextVertexPos;
        defaultTextVertexPos = 0;
    }
    if (defaultPmtId) {
        delete []defaultPmtId;
        defaultPmtId = 0;
    }
    if (defaultTextFaceVertex) {
        delete []defaultTextFaceVertex;
        defaultTextFaceVertex = 0;
    }

    // texture
    texture = new Texture((APrimitive*)this);
}

QString ACube::toString() const
{
    return "width=" + QString::number(width) + "\ndepth="
            + QString::number(depth) + "\nheight=" +
            QString::number(height) + "\n";
}

const QPair<double, double>* ACube::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    defaultTextVertexPos[2] = defaultTextVertexPos[4] =
            QPair<double, double>(0.0, 1.0);
    defaultTextVertexPos[5] = defaultTextVertexPos[8] =
            defaultTextVertexPos[10] = QPair<double, double>(0.0, 1.0 / 3.0);
    defaultTextVertexPos[0] = defaultTextVertexPos[3] =
            defaultTextVertexPos[13] = defaultTextVertexPos[29] =
            defaultTextVertexPos[34] = defaultTextVertexPos[32] =
            QPair<double, double>(2.0 / 3.0, 1.0 / 3.0);
    defaultTextVertexPos[7] = defaultTextVertexPos[16] =
            defaultTextVertexPos[14] =
            QPair<double, double>(1.0 / 3.0, 1.0 / 3.0);
    defaultTextVertexPos[11] = QPair<double, double>(0.0, 0.0);
    defaultTextVertexPos[9] = defaultTextVertexPos[6] =
            defaultTextVertexPos[17] = QPair<double, double>(1.0 / 3.0, 0.0);
    defaultTextVertexPos[12] = defaultTextVertexPos[15] =
            defaultTextVertexPos[35] = QPair<double, double>(2.0 / 3.0, 0.0);
    defaultTextVertexPos[23] = defaultTextVertexPos[26] =
            defaultTextVertexPos[28] =
            QPair<double, double>(2.0 / 3.0, 2.0 / 3.0);
    defaultTextVertexPos[18] = defaultTextVertexPos[21] =
            defaultTextVertexPos[25] = QPair<double, double>(1.0, 2.0 / 3.0);
    defaultTextVertexPos[24] = defaultTextVertexPos[27] =
            defaultTextVertexPos[31] = QPair<double, double>(1.0, 1.0 / 3.0);
    defaultTextVertexPos[30] = defaultTextVertexPos[33] =
            QPair<double, double>(1.0, 0.0);
    defaultTextVertexPos[1] = defaultTextVertexPos[20] =
            defaultTextVertexPos[22] = QPair<double, double>(2.0 / 3.0, 1.0);
    defaultTextVertexPos[19] = QPair<double, double>(1.0, 1.0);
    return defaultTextVertexPos;
}

const int* ACube::getDefaultPmtId()
{
    if (defaultPmtId) {
        return defaultPmtId;
    }
    int cnt = getTextVertexCount();
    defaultPmtId = new int[cnt];
    defaultPmtId[0] = defaultPmtId[3] = defaultPmtId[17]  = defaultPmtId[24] = 4;
    defaultPmtId[1] = defaultPmtId[14] = defaultPmtId[16] = defaultPmtId[18]
            = defaultPmtId[21] = 0;
    defaultPmtId[2] = defaultPmtId[4] = defaultPmtId[7] = defaultPmtId[23] = 3;
    defaultPmtId[5] = defaultPmtId[6] = defaultPmtId[9] = defaultPmtId[26]
            = defaultPmtId[28] = 7;
    defaultPmtId[8] = defaultPmtId[10] = defaultPmtId[20] = defaultPmtId[22]
            = defaultPmtId[31] = 2;
    defaultPmtId[11] = defaultPmtId[29] = defaultPmtId[30] = defaultPmtId[33] = 6;
    defaultPmtId[12] = defaultPmtId[15] = defaultPmtId[25] = defaultPmtId[27]
            = defaultPmtId[35] = 5;
    defaultPmtId[13] = defaultPmtId[19] = defaultPmtId[32] = defaultPmtId[34] = 1;
    return defaultPmtId;
}
