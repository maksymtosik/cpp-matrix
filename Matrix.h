#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Matrix;
class MatrixReference;

class IncompatibleMatrixDimensionsException : public exception {
  public:
    const char* what() const throw()
    {
        return "Matrices are of incompatible sizes";
    }
};

class InvalidMatrixIndexException : public exception {
  public:
    const char* what() const throw()
    {
        return "Index out of matrix's bounds";
    }
};

class FileNotOpenException : public exception {
  public:
    const char* what() const throw()
    {
        return "Couldn't open file";
    }
};

class InvalidDataFromFileException : public exception {
  public:
    const char* what() const throw()
    {
        return "File too short for given matrix size";
    }
};

class Matrix {
  private:
    struct MatrixData;
    MatrixData* data;
    double read(size_t row, size_t col) const;
    void write(size_t row, size_t col, double value);
    static Matrix multiplyByNumber(const Matrix& m, double number);
    static Matrix multiplyByMatrix(const Matrix& m1, const Matrix& m2);
  public:
    friend class MatrixReference;
    Matrix(size_t rows = 1, size_t cols = 1);
    Matrix(string fileName);
    Matrix(const Matrix& m);
    ~Matrix();
    size_t getRows() const;
    size_t getCols() const;
    size_t getReferences() const;
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    MatrixReference operator()(size_t row, size_t col);
    friend bool operator==(const Matrix& m1, const Matrix& m2);
    friend bool operator!=(const Matrix& m1, const Matrix& m2);
    friend ostream& operator<<(ostream& os, const Matrix& m);
};

struct Matrix::MatrixData {
    size_t rows;
    size_t cols;
    double** matrix;
    size_t references;

    MatrixData(size_t newRows, size_t newCols);
    ~MatrixData();
    MatrixData* detach();
};

class MatrixReference {
  private:
    Matrix* matrix;
    size_t rows;
    size_t cols;

  public:
    MatrixReference(Matrix* matrix, size_t rows, size_t cols);
    operator double() const;
    void operator=(double num);
};
