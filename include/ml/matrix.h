// Copyright 2016 Dolotov Evgeniy

#ifndef INCLUDE_ML_MATRIX_H_
#define INCLUDE_ML_MATRIX_H_

#include <ml/vector.h>

#include <vector>
#include <iostream>

class Matrix {
 public:
    Matrix(int cols, int rows, double defaultValue = 0);
    Matrix(const Matrix& mat);
    double at(int i, int j) const;
    double& at(int i, int j);
    Matrix& operator =(const Matrix& mat);
    Matrix operator +(const Matrix& mat) const;
    Matrix operator -(const Matrix& mat) const;
    Matrix operator *(const Matrix& mat) const;
    bool operator ==(const Matrix& mat) const;
    bool operator !=(const Matrix& mat) const;
    int cols() const;
    int rows() const;
    Vector row(int i);
    Vector col(int j);
    std::vector<double> data() const;
    static Matrix identity(int dims);

 private:
    std::vector<double> data_;
    int cols_;
    int rows_;
};

std::ostream& operator <<(std::ostream& os, const Matrix& mat);

Matrix operator *(const double& a, const Matrix& mat);
Matrix operator +(const double& a, const Matrix& mat);
Matrix operator +(const Matrix& mat, const double& a);

#endif  // INCLUDE_ML_MATRIX_H_
