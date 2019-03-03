#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>

class Matrix
{

private:
    size_t rows;
    size_t columns;
    double *matrix;

public:
    // Indexing - Function to index i,j positions in a linear manner
    size_t index(const size_t &i, const size_t &j) const;

    // Constructor
    Matrix(size_t r = 1, size_t c = 1, double val = 0);

    // Destructor
    ~Matrix();

    //Swap function - would be used within the move constructor
    void swap(Matrix that);

    // Copy constructor
    Matrix(const Matrix &that);

    // Move constructor
    Matrix(Matrix &&that);

    // Copy and swap assignment operator
    Matrix &operator=(Matrix that);

    // != Operator overloading
    bool operator!=(const Matrix &other);

    // == Operator overloading
    bool operator==(const Matrix &other);

    // + Operator overloading
    Matrix operator+(const Matrix &addend) const;
    Matrix &operator+=(const Matrix &addend);

    // - Operator overloading
    Matrix operator-(const Matrix &subtrahend) const;
    Matrix &operator-=(const Matrix &subtrahend);

    // * Operator overloading
    Matrix operator*(const Matrix &multiplicand) const;
    void operator*=(const Matrix &multiplicand);

    // () Operator overloading
    double &operator()(const size_t &i, const size_t &j);
    const double &operator()(const size_t &i, const size_t &j) const;

    // << Operator overloading
    friend std::ostream &operator<<(std::ostream &out, const Matrix &mat);

};

#endif //MATRIX_H
