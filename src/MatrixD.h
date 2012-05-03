#ifndef MATRIXD_H
#define MATRIXD_H

// Matrix with the same width and height
class MatrixD
{
public:
    MatrixD(int size);
    ~MatrixD();
    MatrixD(const MatrixD&);
    MatrixD& operator = (const MatrixD&);

    int getSize() const;

    double* getPointer() const;
    double getElement(int x, int y) const;
    double getElement(int index) const;
    void setElement(int x, int y, double value);
    void setElement(int index, double value);

    // set to be identity matrix
    void setIdentity();

    // multiply two matrix with the same size
    MatrixD multiply(MatrixD another) const;

private:
    int size;
    int arrLength;
    double* matrix;
};

#endif // MATRIXD_H
