#ifndef MATRIXD_H
#define MATRIXD_H

#include <QString>

// Matrix with the same width and height
class MatrixD
{
public:
    MatrixD(int size);
    MatrixD(int size, double* arr);
    ~MatrixD();
    MatrixD(const MatrixD&);
    MatrixD& operator = (const MatrixD&);

    int getSize() const;

    double* getPointer() const;
    double getElement(int row, int col) const;
    double getElement(int index) const;
    void setElement(int row, int col, double value);
    void setElement(int index, double value);

    // set to be identity matrix
    void setIdentity();
    // set to be transposed
    void setTransposed();

    // multiply two matrix with the same size
    MatrixD multiply(MatrixD another) const;

    QString toString();

private:
    int size;
    int arrLength;
    double* matrix;
};

#endif // MATRIXD_H
