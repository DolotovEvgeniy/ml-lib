// Copyright 2016 Dolotov Evgeniy

#ifndef INCLUDE_ML_MATRIX_H_
#define INCLUDE_ML_MATRIX_H_

#include <ml/vector.h>

#include <vector>
#include <iostream>
namespace ml {
class Matrix {
 public:
    Matrix();
    Matrix(int rows, int cols, double defaultValue = 0);
    Matrix(const Matrix& mat);
    double at(int row, int col) const;
    double& at(int row, int col);
    Matrix& operator =(const Matrix& mat);
    Matrix operator +(const Matrix& mat) const;
    Matrix operator -(const Matrix& mat) const;
    Matrix operator *(const Matrix& mat) const;
    bool operator ==(const Matrix& mat) const;
    bool operator !=(const Matrix& mat) const;
    size_t cols() const;
    size_t rows() const;
    Vector row(int i);
    Vector col(int j);
    std::vector<double> data() const;
    static Matrix identity(int dims);

 private:
    std::vector<double> data_;
    size_t cols_;
    size_t rows_;
};

std::ostream& operator <<(std::ostream& os, const Matrix& mat);

Matrix operator *(const double& a, const Matrix& mat);
Matrix operator +(const double& a, const Matrix& mat);
Matrix operator +(const Matrix& mat, const double& a);
}  // namespace ml
#endif  // INCLUDE_ML_MATRIX_H_
