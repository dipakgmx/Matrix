#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cassert>


template<typename T>
class Matrix
{
private:
    size_t rows{};
    size_t columns{};
    T *matrix;
    friend std::ostream &operator<<(std::ostream &out, const Matrix &mat)
    {
        for (size_t i = 0; i < mat.rows; ++i) {
            for (size_t j = 0; j < mat.columns; ++j) {
                out << "  " << mat(i, j) << "  ";
            }
            out << std::endl;
        }
        out << std::endl;
        return out;
    }

public:
// Indexing - Function to index i,j positions in a linear manner
    size_t index(const size_t &i, const size_t &j) const;
// () Operator overloading
    T &operator()(const size_t &i, const size_t &j);
    const T &operator()(const size_t &i, const size_t &j) const;
// Constructor
    Matrix(const size_t row_size, const size_t column_size, T value = 0);
    Matrix();
    // Destructor
    virtual ~Matrix();
    // Copy constructor
    Matrix(const Matrix<T> &that);
    // Move constructor
    Matrix(Matrix<T> &&that);
    // Copy and swap assignment operator
    Matrix &operator=(Matrix<T> that);
    // == Operator overloading
    bool operator==(const Matrix<T> &rhs) const;
    // != Operator overloading
    bool operator!=(const Matrix<T> &rhs) const;
    // + Operator overloading
    Matrix operator+(const Matrix<T> &addend) const;
    Matrix &operator+=(const Matrix<T> &addend);
    // - Operator overloading
    Matrix operator-(const Matrix<T> &subtrahend) const;
    Matrix &operator-=(const Matrix<T> &subtrahend);
    // * Operator overloading
    Matrix operator*(const Matrix<T> &multiplicand) const;
    void operator*=(const Matrix<T> &multiplicand);
};

template<typename T>
size_t Matrix<T>::index(const size_t &i, const size_t &j) const
{
    assert(rows > i && (columns > j));
    return (i * columns + j);
}

// () Operator overloading
// Note: return type is set to a double & (a reference is sent) so that, once can use it as a lvalue!
// Else, an r value would be sent, causing assignment of new values to the returned value from this operator futile
template<typename T>
T &Matrix<T>::operator()(const size_t &i, const size_t &j)
{
    assert((rows >= i) && (columns >= j));
    return matrix[index(i, j)];
}

template<typename T>
const T &Matrix<T>::operator()(const size_t &i, const size_t &j) const
{
    assert((rows >= i) && (columns >= j));
    return matrix[index(i, j)];
}

template<typename T>
Matrix<T>::Matrix(const size_t row_size, const size_t column_size, T value)
    :rows(row_size),
     columns(column_size),
     matrix(new T[row_size * column_size])
{
    // Assigning values at i and j indexes
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            (*this)(i, j) = value;
        }
    }
}

template<typename T>
Matrix<T>::Matrix()
    :rows(0),
     columns(0),
     matrix(nullptr)
{

}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] matrix;
    std::cout << "\nDestructor called\n";
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &that)
    :rows(that.rows),
     columns(that.columns),
     matrix(new T[rows * columns])
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            // Assigning values of each element to the copy
            (*this)(i, j) = that(i, j);
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&that)
    :
    rows(std::move(that.rows)),
    columns(std::move(that.columns)),
    matrix(that.matrix)
{
    that.matrix = nullptr;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> that)
{
    std::swap(this->rows, that.rows);
    std::swap(this->columns, that.columns);
    std::swap(this->matrix, that.matrix);
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix &rhs) const
{
    if ((this->rows) != rhs.rows)
        return false;
    else if ((this->columns) != rhs.columns)
        return false;
    else {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if ((*this)(i, j) != rhs(i, j))
                    return false;
            }
        }
    }
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix &rhs) const
{
    return !(rhs == *this);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &addend) const
{
    assert((rows == addend.rows) && (columns == addend.columns));
    Matrix<T> result(rows, columns, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result(i, j) = (*this)(i, j) + addend(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &addend)
{
    assert((rows == addend.rows) && (columns == addend.columns));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            (*this)(i, j) += addend(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &subtrahend) const
{
    assert((rows == subtrahend.rows) && (columns == subtrahend.columns));
    Matrix<T> result(rows, columns, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result(i, j) = (*this)(i, j) + subtrahend(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &subtrahend)
{
    assert((rows == subtrahend.rows) && (columns == subtrahend.columns));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            (*this)(i, j) -= subtrahend(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &multiplicand) const
{
    assert(this->columns == multiplicand.rows);
    // https://msdn.microsoft.com/en-us/library/hh873134.aspx
    Matrix result(rows, multiplicand.columns, 0);
    for (size_t row = 0; row < (this->rows); ++row) {
        for (size_t col = 0; col < multiplicand.columns; ++col) {
            for (size_t inner = 0; inner < (this->columns); ++inner) {
                result(row, col) += (*this)(row, inner) * multiplicand(inner, col);
            }
        }
    }
    return result;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix &multiplicand)
{
    assert(this->columns == multiplicand.rows);
    Matrix result(rows, multiplicand.columns, 0);
    for (size_t row = 0; row < (this->rows); ++row) {
        for (size_t col = 0; col < multiplicand.columns; ++col) {
            for (size_t inner = 0; inner < (this->columns); ++inner) {
                result(row, col) += (*this)(row, inner) * multiplicand(inner, col);
            }
        }
    }
    swap(result);
}
#endif //MATRIX_H
