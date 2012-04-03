#include <QtOpenGL>

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
    double right = width / 2;
    double left = -right;
    double top = height;
    double bottom = 0;
    double near = depth / 2;
    double far = -near;
    vertexArray[0] = Vector3d(right, top, near);
    vertexArray[1] = Vector3d(right, top, far);
    vertexArray[2] = Vector3d(left, top, far);
    vertexArray[3] = Vector3d(left, top, near);
    vertexArray[4] = Vector3d(right, bottom, near);
    vertexArray[5] = Vector3d(right, bottom, far);
    vertexArray[6] = Vector3d(left, bottom, far);
    vertexArray[7] = Vector3d(left, bottom, near);

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
