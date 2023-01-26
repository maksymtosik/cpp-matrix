#include "Matrix.h"

using namespace std;

Matrix::Matrix(size_t rows, size_t cols)
{
    data = new MatrixData(rows, cols);
}

Matrix::Matrix(string fileName)
{
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        throw FileNotOpenException();
    }
    size_t rows, cols;
    file >> rows >> cols;
    data = new MatrixData(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (file.eof()) {
                file.close();
                delete data;
                throw InvalidDataFromFileException();
            }
            file >> data->matrix[i][j];
        }
    }
    file.close();
}

Matrix::Matrix(const Matrix& m)
{
    m.data->references++;
    data = m.data;
}

Matrix::~Matrix()
{
    if (--data->references == 0) {
        delete data;
    }
}

size_t Matrix::getRows() const
{
    return data->rows;
}

size_t Matrix::getCols() const
{
    return data->cols;
}

size_t Matrix::getReferences() const
{
    return data->references;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix newMatrix(m1);
    newMatrix += m2;
    return newMatrix;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        throw IncompatibleMatrixDimensionsException();
    }
    Matrix newMatrix(m1.getRows(), m1.getCols());
    for (size_t i = 0; i < newMatrix.getRows(); i++) {
        for (size_t j = 0; j < newMatrix.getCols(); j++) {
            newMatrix.data->matrix[i][j] =
                m1.data->matrix[i][j] - m2.data->matrix[i][j];
        }
    }
    return newMatrix;
}

Matrix Matrix::multiplyByMatrix(const Matrix& m1, const Matrix& m2)
{
    if (m1.getCols() != m2.getRows()) {
        throw IncompatibleMatrixDimensionsException();
    }
    Matrix newMatrix(m1.getRows(), m2.getCols());
    for (size_t i = 0; i < newMatrix.getRows(); i++) {
        for (size_t j = 0; j < newMatrix.getCols(); j++) {
            for (size_t k = 0; k < m1.getCols(); k++) {
                newMatrix.data->matrix[i][j] +=
                    m1.data->matrix[i][k] * m2.data->matrix[k][j];
            }
        }
    }
    return newMatrix;
}

Matrix Matrix::multiplyByNumber(const Matrix& m, double number)
{
    Matrix newMatrix(m.getRows(), m.getCols());
    for (size_t i = 0; i < newMatrix.getRows(); i++) {
        for (size_t j = 0; j < newMatrix.getCols(); j++) {
            newMatrix.data->matrix[i][j] = m.data->matrix[i][j] * number;
        }
    }
    return newMatrix;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    if (m1.getCols() == 1 && m1.getRows() == 1) {
        return Matrix::multiplyByNumber(m2, m1.data->matrix[0][0]);
    }
    else if (m2.getCols() == 1 && m2.getRows() == 1) {
        return Matrix::multiplyByNumber(m1, m2.data->matrix[0][0]);
    }
    else {
        return Matrix::multiplyByMatrix(m1, m2);
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this != &m) {
        if (--data->references == 0) {
            delete data;
        }
        m.data->references++;
        data = m.data;
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if (this->getRows() != m.getRows() || this->getCols() != m.getCols()) {
        throw IncompatibleMatrixDimensionsException();
    }
    this->data = this->data->detach();
    for (size_t i = 0; i < this->getRows(); i++) {
        for (size_t j = 0; j < this->getCols(); j++) {
            this->data->matrix[i][j] += m.data->matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    Matrix newMatrix = *this - m;
    *this = newMatrix;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    Matrix newMatrix = *this * m;
    *this = newMatrix;
    return *this;
}

MatrixReference Matrix::operator()(size_t row, size_t col)
{
    if (row < 0 || row >= data->rows || col < 0 || col >= data->cols) {
        throw InvalidMatrixIndexException();
    }
    return MatrixReference(this, row, col);
}

double Matrix::read(size_t row, size_t col) const
{

    return data->matrix[row][col];
}

bool operator==(const Matrix& m1, const Matrix& m2)
{
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        return false;
    }
    for (size_t i = 0; i < m1.getRows(); i++) {
        for (size_t j = 0; j < m1.getCols(); j++) {
            if (m1.data->matrix[i][j] != m2.data->matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2)
{
    return !(m1 == m2);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.data->rows; i++) {
        for (size_t j = 0; j < m.data->cols; j++) {
            os << m.data->matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

void Matrix::write(size_t row, size_t col, double value)
{
    data = data->detach();
    data->matrix[row][col] = value;
}

Matrix::MatrixData::MatrixData(size_t newRows, size_t newCols)
{
    rows = newRows;
    cols = newCols;
    references = 1;
    matrix = new double*[rows];
    for (size_t i = 0; i < rows; i++) {
        this->matrix[i] = new double[cols]();
    }
}

Matrix::MatrixData::~MatrixData()
{
    for (size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix::MatrixData* Matrix::MatrixData::detach()
{
    if (references == 1) {
        return this;
    }
    MatrixData* newData = new MatrixData(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            newData->matrix[i][j] = matrix[i][j];
        }
    }
    references--;
    return newData;
}

MatrixReference::MatrixReference(Matrix* matrix, size_t rows, size_t cols)
{
    this->matrix = matrix;
    this->rows = rows;
    this->cols = cols;
}

MatrixReference::operator double() const
{
    return this->matrix->read(this->rows, this->cols);
}

void MatrixReference::operator=(double value)
{
    this->matrix->write(this->rows, this->cols, value);
}
