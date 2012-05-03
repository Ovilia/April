#ifdef _DEBUG
#define <assert.h>
#endif

#include "MatrixD.h"
#include <QDebug>

MatrixD::MatrixD(int size) :
    size(size),
    arrLength(size * size)
{
    matrix = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = 0.0;
    }
}

MatrixD::~MatrixD()
{
    delete []matrix;
}

MatrixD::MatrixD(const MatrixD& rhs)
{
    size = rhs.getSize();
    arrLength = size * size;
    matrix = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = rhs.getElement(i);
    }
}

MatrixD& MatrixD::operator = (const MatrixD& rhs)
{
    if (this == &rhs) {
        // avoid delete `this`
        return *this;
    }
    size = rhs.getSize();
    arrLength = size * size;
    delete []matrix;
    matrix = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = rhs.getElement(i);
    }
    return *this;
}

int MatrixD::getSize() const
{
    return size;
}

double* MatrixD::getPointer() const
{
    return matrix;
}

double MatrixD::getElement(int x, int y) const
{
    return getElement(x * size + y);
}

double MatrixD::getElement(int index) const
{
    return matrix[index];
}

void MatrixD::setElement(int x, int y, double value)
{
    setElement(x * size + y, value);
}

void MatrixD::setElement(int index, double value)
{
    matrix[index] = value;
}

void MatrixD::setIdentity()
{
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = 0.0;
    }
    for (int i = 0; i < size; ++i) {
        matrix[i * (size + 1)] = 1.0;
    }
}

MatrixD MatrixD::multiply(MatrixD another) const
{
#ifdef _DEBUG
    assert(size == another.getSize());
#endif

    MatrixD result(size);
    int index = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0.0;
            for (int k = 0; k < size; ++k) {
                sum += this->getElement(i, k) * another.getElement(k, j);
            }
            result.setElement(index, sum);
            ++index;
        }
    }
    return result;
}
