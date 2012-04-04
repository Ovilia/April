#include <QtopenGL>

#include "ACube.h"
#include "Vector3d.h"
#include "Vector3i.h"

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

    boundingBox = Vector3d(width, height, depth);

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
}
