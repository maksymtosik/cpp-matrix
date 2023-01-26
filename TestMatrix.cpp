#include "Matrix.h"

using namespace std;

void testCompoundOperators();
void testCompoundAddition();
void testCompoundSubtraction();
void testCompoundMultiplication();
void testRegularOperators();
void testAddition();
void testSubtraction();
void testMultiplication();
void testExceptions();
void testIncompatibleMatrixDimensionsException();
void testInvalidMatrixIndexException();
void testFileNotOpenException();
void testInvalidDataFromFileException();
void testReferenceCounting();
void testReadingFromFile();
void testBracesOperator();

int main()
{
    testCompoundOperators();
    testRegularOperators();
    testExceptions();
    testReferenceCounting();
    testReadingFromFile();
    testBracesOperator();
}

void testCompoundOperators()
{
    cout << "\n--------------Testing compound operators--------------" << endl;
    testCompoundAddition();
    testCompoundSubtraction();
    testCompoundMultiplication();
}

void testCompoundAddition()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = 6;
    m3(0, 1) = 8;
    m3(1, 0) = 10;
    m3(1, 1) = 12;
    m1 += m2;
    if (m1 == m3) {
        cout << "Compound addition test passed" << endl;
    }
    else {
        cout << "Compound addition test failed" << endl;
    }
}

void testCompoundSubtraction()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = -4;
    m3(0, 1) = -4;
    m3(1, 0) = -4;
    m3(1, 1) = -4;
    m1 -= m2;
    if (m1 == m3) {
        cout << "Compound subtraction test passed" << endl;
    }
    else {
        cout << "Compound subtraction test failed" << endl;
    }
}

void testCompoundMultiplication()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = 19;
    m3(0, 1) = 22;
    m3(1, 0) = 43;
    m3(1, 1) = 50;
    m1 *= m2;
    if (m1 == m3) {
        cout << "Compound multiplication test passed" << endl;
    }
    else {
        cout << "Compound multiplication test failed" << endl;
    }
}

void testRegularOperators()
{
    cout << "\n--------------Testing regular operators--------------" << endl;
    testAddition();
    testSubtraction();
    testMultiplication();
}

void testAddition()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = 6;
    m3(0, 1) = 8;
    m3(1, 0) = 10;
    m3(1, 1) = 12;
    Matrix m4 = m1 + m2;
    if (m4 == m3) {
        cout << "Addition test passed" << endl;
    }
    else {
        cout << "Addition test failed" << endl;
    }
}

void testSubtraction()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = -4;
    m3(0, 1) = -4;
    m3(1, 0) = -4;
    m3(1, 1) = -4;
    Matrix m4;
    m4 = m1 - m2;
    if (m4 == m3) {
        cout << "Subtraction test passed" << endl;
    }
    else {
        cout << "Subtraction test failed" << endl;
    }
}

void testMultiplication()
{
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;
    Matrix m3(2, 2);
    m3(0, 0) = 19;
    m3(0, 1) = 22;
    m3(1, 0) = 43;
    m3(1, 1) = 50;
    Matrix m4 = m1 * m2;
    if (m4 == m3) {
        cout << "Multiplication test passed" << endl;
    }
    else {
        cout << "Multiplication test failed" << endl;
    }
}

void testExceptions()
{
    cout << "\n--------------Testing exceptions--------------" << endl;
    testIncompatibleMatrixDimensionsException();
    testInvalidMatrixIndexException();
    testFileNotOpenException();
    testInvalidDataFromFileException();
}

void testIncompatibleMatrixDimensionsException()
{
    Matrix m1(2, 2);
    Matrix m2(3, 3);
    try {
        m1 += m2;
        cout << "Incompatible matrix dimensions exception test failed" << endl;
    }
    catch (IncompatibleMatrixDimensionsException& e) {
        cout << "Incompatible matrix dimensions exception test passed" << endl;
    }
}

void testInvalidMatrixIndexException()
{
    Matrix m1(2, 2);
    try {
        m1(2, 2);
        cout << "Invalid matrix index exception test failed" << endl;
    }
    catch (InvalidMatrixIndexException& e) {
        cout << "Invalid matrix index exception test passed" << endl;
    }
}

void testFileNotOpenException()
{
    try {
        Matrix m1("file.txt");
        cout << "File not open exception test failed" << endl;
    }
    catch (FileNotOpenException& e) {
        cout << "File not open exception test passed" << endl;
    }
}

void testInvalidDataFromFileException()
{
    try {
        Matrix m1("invalidMatrix.txt");
        cout << "Invalid data from file exception test failed" << endl;
    }
    catch (InvalidDataFromFileException& e) {
        cout << "Invalid data from file exception test passed" << endl;
    }
}

void testReferenceCounting()
{
    cout << "\n--------------Testing reference counting--------------" << endl;
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    Matrix m2(3, 3);
    m2(0, 0) = 2;
    Matrix m3(m1);
    Matrix m4(m1);
    m2 = m1;
    if (m1.getReferences() == 4) {
        m2(0, 0) = 4;
    }
    if (m1.getReferences() == 3) {
        cout << "Reference counting test passed" << endl;
    }
    else {
        cout << "Reference counting test failed" << endl;
    }
}

void testReadingFromFile()
{
    cout << "\n--------------Testing reading from file--------------" << endl;
    Matrix m1("matrix.txt");
    cout << "Rows: " << m1.getRows() << ", cols: " << m1.getCols() << endl;
    cout << m1;
    cout << "Reading from file test passed" << endl;
}

void testBracesOperator()
{
    cout << "\n--------------Testing () operator--------------" << endl;
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    if (m1(0, 0) == 1 && m1(0, 1) == 2 && m1(1, 0) == 3 && m1(1, 1) == 4) {
        cout << "() operator test passed" << endl;
    }
    else {
        cout << "() operator test failed" << endl;
    }
}
