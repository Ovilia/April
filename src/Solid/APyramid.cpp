#include "APyramid.h"

#include <qmath.h>

const double APyramid::DEFAULT_SIDE_LENGTH = 1.0;
const int APyramid::DEFAULT_SIDE_COUNT = 4;

APyramid::APyramid() :
    APrimitive(APrimitive::PT_PRISM),
    sideLength(DEFAULT_SIDE_LENGTH),
    sideCount(DEFAULT_SIDE_LENGTH)
{
    reset(sideLength, sideCount);
}

APyramid::APyramid(double sideLength, int sideCount) :
    APrimitive(APrimitive::PT_PYRAMID),
    sideLength(sideLength),
    sideCount(sideCount)
{
    reset(sideLength, sideCount);
}

APyramid::~APyramid()
{

}

double APyramid::getSideLength()
{
    return sideLength;
}

int APyramid::getSideCount()
{
    return sideCount;
}

void APyramid::reset(double sideLength, int sideCount)
{
    this->sideLength = sideLength;
    this->sideCount = sideCount;

    // TODO: only calculated when sideCount is 4 now
    double height = sideLength * 0.5 * qSqrt(3);

    boundingBoxMin = Vector3d(-sideLength / 2.0, 0.0, -height * 2.0 / 3.0);
    boundingBoxMax = Vector3d(sideLength / 2.0, height, height / 3.0);

    vertexCount = 4;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    vertexArray[0] = Vector3d(0.0, sideLength * qSqrt(6.0) / 3.0, 0.0);
    vertexArray[1] = Vector3d(-0.5 * sideLength, 0.0, height / 3.0);
    vertexArray[2] = Vector3d(0.5 * sideLength, 0.0, height / 3.0);
    vertexArray[3] = Vector3d(0.0, 0.0, -height * 2.0 / 3.0);

    faceCount = 4;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    faceArray[0] = Vector3i(0, 1, 2);
    faceArray[1] = Vector3i(0, 2, 3);
    faceArray[2] = Vector3i(1, 2, 3);
    faceArray[3] = Vector3i(0, 1, 3);

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

QString APyramid::toString() const
{
    return "sideLength=" + QString::number(sideLength) + "\nsideCount=" + \
            QString::number(sideCount) + "\n";
}

const QPair<double, double>* APyramid::getDefaultTextVertexPos()
{
    if (defaultTextVertexPos) {
        return defaultTextVertexPos;
    }
    int cnt = getTextVertexCount();
    defaultTextVertexPos = new QPair<double, double>[cnt];
    defaultTextVertexPos[0] = QPair<double, double>(0.5, qSqrt(3) * 0.5);
    defaultTextVertexPos[1] = defaultTextVertexPos[3] =
            defaultTextVertexPos[11] =
            QPair<double, double>(0.25, qSqrt(3) * 0.25);
    defaultTextVertexPos[2] = defaultTextVertexPos[10] =
            defaultTextVertexPos[6] =
            QPair<double, double>(0.75, qSqrt(3) * 0.25);
    defaultTextVertexPos[4] = QPair<double, double>(0.0, 0.0);
    defaultTextVertexPos[5] = defaultTextVertexPos[7] =
            defaultTextVertexPos[9] = QPair<double, double>(0.5, 0.0);
    defaultTextVertexPos[8] = QPair<double, double>(1.0, 0.0);
    return defaultTextVertexPos;
}

const int* APyramid::getDefaultPmtId()
{
    if (defaultPmtId) {
        return defaultPmtId;
    }
    int cnt = getTextVertexCount();
    defaultPmtId = new int[cnt];
    defaultPmtId[0] = defaultPmtId[4] = defaultPmtId[8] = 0;
    defaultPmtId[1] = defaultPmtId[3] = defaultPmtId[11] = 2;
    defaultPmtId[2] = defaultPmtId[10] = defaultPmtId[6] = 1;
    defaultPmtId[5] = defaultPmtId[7] = defaultPmtId[9] = 3;
    return defaultPmtId;
}
