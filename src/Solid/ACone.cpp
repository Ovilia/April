#include <cmath>

#include "ACone.h"

ACone::ACone(double radius, int slices, double height) :
    APrimitive(),
    radius(radius),
    slices(slices),
    height(height)
{
    reset(radius, slices, height);
}

ACone::~ACone()
{

}

void ACone::reset(double radius, int slices, double height)
{
    boundingBox = Vector3d(2 * radius, height, 2 * radius);

    vertexCount = slices + 2;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double step = 2 * M_PI / slices;
    for (int i = 0; i < slices; ++i) {
        double alpha = step * i;
        vertexArray[i] = Vector3d(cos(alpha) * radius, 0.0,
                                  sin(alpha) * radius);
    }
    vertexArray[slices] = Vector3d(0.0, height, 0.0);
    vertexArray[slices + 1] = Vector3d(0.0, 0.0, 0.0);

    faceCount = 2 * slices;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    for (int i = 0; i < slices - 1; ++i) {
        faceArray[i] = Vector3i(i, i + 1, slices);
        faceArray[slices + i] = Vector3i(i, slices + 1, i + 1);
    }
    faceArray[slices - 1] = Vector3i(0, slices, slices - 1);
    faceArray[slices * 2 - 1] = Vector3i(0, slices - 1, slices + 1);
}
