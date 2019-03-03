#include <iostream>
#include <cassert>
#include "Matrix.h"

// Indexing - Function to index i,j positions in a linear manner
size_t Matrix::index(const size_t &i, const size_t &j) const
{
    assert(rows >= i && (columns >= j));
    return (i * columns + j);
}

// Constructor
Matrix::Matrix(size_t r, size_t c, double val)
{
    this->rows = r;
    this->columns = c;
    // First creating the row array
    // https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    this->matrix = new double[this->rows * this->columns];
    // Assigning values at i and j indexes
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->columns; ++j) {
            this->matrix[index(i, j)] = val;
        }
    }
}

//Swap function
void Matrix::swap(Matrix that)
{
    std::swap(this->rows, that.rows);
    std::swap(this->columns, that.columns);
    std::swap(this->matrix, that.matrix);
}

// Copy constructor
//https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
Matrix::Matrix(const Matrix &that)
{
    this->rows = that.rows;
    this->columns = that.columns;
    this->matrix = new double[rows * columns];
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            // Assigning values of each element to the copy
            this->matrix[index(i, j)] = that(i, j);
        }
    }
}

// move constructor
Matrix::Matrix(Matrix &&that)
    : rows(0), columns(0), matrix(nullptr)
{
    swap(that);
}

Matrix::~Matrix()
{
    delete[] matrix;
}

bool Matrix::operator!=(const Matrix &other)
{
    if ((this->rows) != other.rows)
        return true;
    else if ((this->columns) != other.columns)
        return true;
    else {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if (matrix[index(i, j)] != other(i, j))
                    return true;
            }
        }

    }
    return false;
}

bool Matrix::operator==(const Matrix &other)
{
    if ((this->rows) != other.rows)
        return false;
    else if ((this->columns) != other.columns)
        return false;
    else {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if (matrix[index(i, j)] != other(i, j))
                    return false;
            }
        }

    }
    return true;
}

// Copy and swap assignment operator
Matrix &Matrix::operator=(Matrix that)
{
    swap(that);
}

Matrix Matrix::operator+(const Matrix &addend) const
{
    assert((rows == addend.rows) && (columns == addend.columns));
    Matrix result(rows, columns, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result(i, j) = matrix[index(i, j)] + addend(i, j);
        }
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &addend)
{
    assert((rows == addend.rows) && (columns == addend.columns));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix[index(i, j)] = matrix[index(i, j)] + addend(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &subtrahend) const
{
    assert((rows == subtrahend.rows) && (columns == subtrahend.columns));
    Matrix result(rows, columns, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result(i, j) = matrix[index(i, j)] - subtrahend(i, j);
        }
    }
    return result;
}

Matrix &Matrix::operator-=(const Matrix &subtrahend)
{
    assert((rows == subtrahend.rows) && (columns == subtrahend.columns));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix[index(i, j)] = matrix[index(i, j)] - subtrahend(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &multiplicand) const
{
    assert(this->columns == multiplicand.rows);
    // https://msdn.microsoft.com/en-us/library/hh873134.aspx
    Matrix result(rows, multiplicand.columns, 0);
    for (size_t row = 0; row < (this->rows); ++row) {
        for (size_t col = 0; col < multiplicand.columns; ++col) {
            for (size_t inner = 0; inner < (this->columns); ++inner) {
                result(row, col) += matrix[index(row, inner)] * multiplicand(inner, col);
            }
        }
    }
    return result;
}

void Matrix::operator*=(const Matrix &multiplicand)
{
    assert(this->columns == multiplicand.rows);
    Matrix result(rows, multiplicand.columns, 0);
    for (size_t row = 0; row < (this->rows); ++row) {
        for (size_t col = 0; col < multiplicand.columns; ++col) {
            for (size_t inner = 0; inner < (this->columns); ++inner) {
                result(row, col) += matrix[index(row, inner)] * multiplicand(inner, col);
            }
        }
    }
    swap(result);
}

// () Operator overloading
// Note: return type is set to a double & (a reference is sent) so that, once can use it as a lvalue!
// Else, an r value would be sent, causing assignment of new values to the returned value from this operator futile
double &Matrix::operator()(const size_t &i, const size_t &j)
{
    assert((rows >= i) && (columns >= j));
    return matrix[index(i, j)];
}

const double &Matrix::operator()(const size_t &i, const size_t &j) const
{
    assert((rows >= i) && (columns >= j));
    return matrix[index(i, j)];
}

std::ostream &operator<<(std::ostream &out, const Matrix &mat)
{
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.columns; ++j) {
            out << "  " << mat(i, j) << "  ";
        }
        out << std::endl;
    }
    return out;
}