// Copyright 2016 Dolotov Evgeniy


#ifndef INCLUDE_ML_LINEAR_ALGEBRA_H_
#define INCLUDE_ML_LINEAR_ALGEBRA_H_

#include <vector>
#include <iostream>

class Vector {
 public:
    explicit Vector(int dims, double defaultValue = 0);
    Vector(const Vector& vec);
    double at(int i) const;
    double& at(int i);
    int dims() const;
    Vector& operator =(const Vector& vec);
    Vector operator +(const Vector& vec) const;
    Vector operator -(const Vector& vec) const;
    Vector operator *(const Vector& vec) const;
    bool operator ==(const Vector& vec) const;
    bool operator !=(const Vector& vec) const;
    std::vector<double> data() const;
    double length() const;
 private:
    std::vector<double> data_;
    int dims_;
};

std::ostream& operator <<(std::ostream& os, const Vector& vec);

Vector operator *(const double& a, const Vector& mat);
Vector operator +(const double& a, const Vector& mat);
Vector operator +(const Vector& mat, const double& a);

double dot(const Vector& vec1, const Vector& vec2);

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
#endif  // INCLUDE_ML_LINEAR_ALGEBRA_H_
