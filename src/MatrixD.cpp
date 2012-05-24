#include "MatrixD.h"

#include <assert.h>

MatrixD::MatrixD(int size) :
    size(size),
    arrLength(size * size)
{
    matrix = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = 0.0;
    }
}

MatrixD::MatrixD(int size, double* arr) :
    size(size),
    arrLength(size * size)
{
    matrix = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) {
        matrix[i] = arr[i];
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

double MatrixD::getElement(int row, int col) const
{
    return getElement(row * size + col);
}

double MatrixD::getElement(int index) const
{
    return matrix[index];
}

void MatrixD::setElement(int row, int col, double value)
{
    setElement(row * size + col, value);
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
    MatrixD result(size);
    if (size != another.getSize()) {
        // error
        assert(false);
        return result;
    }

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

QString MatrixD::toString()
{
    QString result = "";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result += QString::number(getElement(i, j));
            if (j == size - 1) {
                result += "\n";
            } else {
                result += " ";
            }
        }
    }
    return result;
}

void MatrixD::setTransposed()
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            double a = getElement(i, j);
            double b = getElement(j, i);
            setElement(j, i, a);
            setElement(i, j, b);
        }
    }
}
