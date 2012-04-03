#include <cmath>

#include "ACylinder.h"

ACylinder::ACylinder(double radius, int slices, double height) :
    APrimitive(),
    radius(radius),
    slices(slices),
    height(height)
{
    reset(radius, slices, height);
}

ACylinder::~ACylinder()
{

}

void ACylinder::reset(double radius, int slices, double height)
{
    boundingBox = Vector3d(2 * radius, height, 2 * radius);

    vertexCount = 2 * slices + 2;
    if (vertexArray) {
        delete []vertexArray;
    }
    vertexArray = new Vector3d[vertexCount];
    double step = 2 * M_PI / slices;
    for (int i = 0; i < slices; ++i) {
        double alpha = step * i;
        vertexArray[i] = Vector3d(cos(alpha) * radius, height,
                                  sin(alpha) * radius);
        vertexArray[slices + i] = Vector3d(cos(alpha) * radius, 0.0,
                                  sin(alpha) * radius);
    }
    vertexArray[2 * slices] = Vector3d(0.0, height, 0.0);
    vertexArray[2 * slices + 1] = Vector3d(0.0, 0.0, 0.0);

    faceCount = 4 * slices;
    if (faceArray) {
        delete []faceArray;
    }
    faceArray = new Vector3i[faceCount];
    for (int i = 0; i < slices - 1; ++i) {
        // top
        faceArray[i] = Vector3i(i, i + 1, 2 * slices);
        // bottom
        faceArray[slices + i] = Vector3i(slices + i,
                                         2 * slices + 1, slices + i + 1);
        // side
        faceArray[2 * (slices + i)] = Vector3i(i, slices + i, i + 1);
        faceArray[2 * (slices + i) + 1] = Vector3i(i + 1,
                                                 slices + i, slices + i + 1);
    }
    faceArray[slices - 1] = Vector3i(0, 2 * slices, slices - 1);
    faceArray[slices * 2 - 1] = Vector3i(slices,
                                         2 * slices - 1, 2 * slices + 1);
    faceArray[slices * 4 - 2] = Vector3i(0, slices - 1, 2 * slices - 1);
    faceArray[slices * 4 - 1] = Vector3i(0, 2 * slices - 1, slices);
}
