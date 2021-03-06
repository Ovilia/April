#include "APrism.h"

#include <qmath.h>

const double APrism::DEFAULT_LENGTH = 1.0;
const double APrism::DEFAULT_SIDE_LENGTH = 1.0;
const int APrism::DEFAULT_SIDE_COUNT = 3;

APrism::APrism() :
    APrimitive(APrimitive::PT_PRISM),
    length(DEFAULT_LENGTH),
    sideLength(DEFAULT_SIDE_LENGTH),
    sideCount(DEFAULT_SIDE_COUNT)
{
    reset(length, sideLength, sideCount);
}

APrism::APrism(double length, double sideLength, int sideCount) :
    APrimitive(APrimitive::PT_PRISM),
    length(length),
    sideLength(sideLength),
    sideCount(sideCount)
{
    reset(length, sideLength, sideCount);
}

APrism::~APrism()
{

}

double APrism::getLength()
{
    return length;
}

double APrism::getSideLength()
{
    return sideLength;
}

int APrism::getSideCount()
{
    return sideCount;
}

void APrism::reset(double length, double sideLength, int sideCount)
{
    this->length = length;
    this->sideLength = sideLength;
    this->sideCount = sideCount;

    double zLength = sideLength * 0.5 * qSqrt(3);

    boundingBoxMin = Vector3d(-sideLength / 2.0, 0.0, 0.0);
    boundingBoxMax = Vector3d(sideLength / 2.0, length, zLength);

    vertexCount = 6;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    vertexArray[0] = Vector3d(sideLength / 2.0, length, 0.0);
    vertexArray[1] = Vector3d(0, length, zLength);
    vertexArray[2] = Vector3d(-sideLength / 2.0, length, 0.0);
    vertexArray[3] = Vector3d(sideLength / 2.0, 0.0, 0.0);
    vertexArray[4] = Vector3d(0.0, 0.0, zLength);
    vertexArray[5] = Vector3d(-sideLength / 2.0, 0.0, 0.0);

    faceCount = 8;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    faceArray[0] = Vector3i(0, 1, 3);
    faceArray[1] = Vector3i(1, 4, 3);
    faceArray[2] = Vector3i(1, 2, 4);
    faceArray[3] = Vector3i(2, 5, 4);
    faceArray[4] = Vector3i(0, 2, 5);
    faceArray[5] = Vector3i(0, 5, 3);
    faceArray[6] = Vector3i(0, 2, 1);
    faceArray[7] = Vector3i(3, 4, 5);

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

QString APrism::toString() const
{
    return "length=" + QString::number(length) + "\nsideLength=" +
            QString::number(sideLength) + "\nsideCount=" +
            QString::number(sideCount) + "\n";
}

const QPair<double, double>* APrism::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    defaultTextVertexPos[0] = QPair<double, double>(0.0, 1.0);
    defaultTextVertexPos[2] = defaultTextVertexPos[5] =
            defaultTextVertexPos[6] = QPair<double, double>(0.5, 1.0);
    defaultTextVertexPos[8] = defaultTextVertexPos[11] =
            QPair<double, double>(1.0, 1.0);
    defaultTextVertexPos[1] = defaultTextVertexPos[4] =
            defaultTextVertexPos[12] = QPair<double, double>(0.0, 0.5);
    defaultTextVertexPos[3] = defaultTextVertexPos[7] =
            defaultTextVertexPos[10] = defaultTextVertexPos[14] =
            defaultTextVertexPos[17] = defaultTextVertexPos[18] =
            QPair<double, double>(0.5, 0.5);
    defaultTextVertexPos[9] = defaultTextVertexPos[20] =
            defaultTextVertexPos[23] = QPair<double, double>(1.0, 0.5);
    defaultTextVertexPos[13] = defaultTextVertexPos[16] =
            QPair<double, double>(0.0, 0.0);
    defaultTextVertexPos[15] = defaultTextVertexPos[19] =
            defaultTextVertexPos[22] = QPair<double, double>(0.5, 0.0);
    defaultTextVertexPos[21] = QPair<double, double>(1.0, 0.0);
    return defaultTextVertexPos;
}

const int* APrism::getDefaultPmtId()
{
    if (defaultPmtId) {
        return defaultPmtId;
    }
    int cnt = getTextVertexCount();
    defaultPmtId = new int[cnt];
    defaultPmtId[0] = defaultPmtId[15] = defaultPmtId[19] =
            defaultPmtId[22] = 0;
    defaultPmtId[1] = defaultPmtId[7] = defaultPmtId[10] =
            defaultPmtId[18] = 1;
    defaultPmtId[2] = defaultPmtId[6] = defaultPmtId[14] =
            defaultPmtId[17] = 2;
    defaultPmtId[3] = defaultPmtId[13] = defaultPmtId[16] =
            defaultPmtId[21] = 3;
    defaultPmtId[4] = defaultPmtId[9] = defaultPmtId[20] =
            defaultPmtId[23] = 4;
    defaultPmtId[5] = defaultPmtId[8] = defaultPmtId[11] =
            defaultPmtId[12] = 5;
    return defaultPmtId;
}
