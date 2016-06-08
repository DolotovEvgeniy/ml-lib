// Copyright 2016 Dolotov Evgeniy

#include "ml/matrix.h"

#include <assert.h>
#include <math.h>

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;

Vector::Vector(int dims, double defaultValue) {
    dims_ = dims;
    data_ = vector<double>(dims_, defaultValue);
}

Vector::Vector(const Vector& vec) {
    dims_ = vec.dims_;
    data_ = vector<double>(dims_);

    for (int i = 0; i < dims_; i++) {
        data_[i] = vec.data_[i];
    }
}

double Vector::at(int i) const {
    return data_[i];
}

double& Vector::at(int i) {
    return data_[i];
}

Vector& Vector::operator =(const Vector& vec) {
    dims_ = vec.dims_;
    data_ = vector<double>(dims_);

    for (int i = 0; i < dims_; i++) {
        data_[i] = vec.data_[i];
    }

    return *this;
}

Vector Vector::operator +(const Vector& vec) const {
    Vector sumVec(vec.dims_);

    for (int i = 0; i < dims_; i++) {
        sumVec.data_[i] = data_[i]+vec.data_[i];
    }

    return sumVec;
}

Vector Vector::operator -(const Vector& vec) const {
    Vector diffVec(vec.dims_);

    for (int i = 0; i < dims_; i++) {
        diffVec.data_[i] = data_[i]-vec.data_[i];
    }

    return diffVec;
}

Vector Vector::operator *(const Vector& vec) const {
    Vector multiplyVec(vec.dims_);

    for (int i = 0; i < dims_; i++) {
        multiplyVec.data_[i] = data_[i]*vec.data_[i];
    }

    return multiplyVec;
}

bool Vector::operator ==(const Vector& vec) const {
    if (dims_ != vec.dims_) {
        return false;
    }

    for (int i = 0; i < dims_; i++) {
        if (data_[i] != vec.data_[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator !=(const Vector& vec) const {
    return !(*this == vec);
}

std::vector<double> Vector::data() const {
    return data_;
}

int Vector::dims() const {
    return dims_;
}

std::ostream& operator <<(std::ostream& os, const Vector& vec) {
    os << "(";
    for (int i = 0; i < vec.dims()-1; i++) {
        os << vec.at(i) << ", ";
    }
    os << vec.at(vec.dims()-1) << ")" << std::endl;
    return os;
}

Vector operator *(const double& a, const Vector& vec) {
    Vector multVec(vec.dims());

    for (int i = 0; i < vec.dims(); i++) {
        multVec.at(i)*=a;
    }

    return multVec;
}

Vector operator +(const double& a, const Vector& vec) {
    return Vector(vec.dims(), a) + vec;
}

Vector operator +(const Vector& vec, const double& a) {
    return Vector(vec.dims(), a) + vec;
}

double Vector::length() const {
    double sum = 0;
    for (int i = 0; i < dims(); i++) {
        sum+=at(i)*at(i);
    }

    return sqrt(sum);
}
double dot(const Vector &vec1, const Vector &vec2) {
    int sum = 0;
    for (int i = 0; i< vec1.dims(); i++) {
        sum+=vec1.at(i)*vec2.at(i);
    }

    return sum;
}

Matrix::Matrix(int cols, int rows, double defaultValue) {
    cols_ = cols;
    rows_ = rows;
    data_ = vector<double>(cols_*rows_, defaultValue);
}

Matrix::Matrix(const Matrix &mat) {
    cols_ = mat.cols_;
    rows_ = mat.rows_;
    data_ = vector<double>(cols_*rows_);

    for (std::size_t i = 0; i < data_.size(); i++) {
        data_[i] = mat.data_[i];
    }
}

double Matrix::at(int i, int j) const {
    return data_[cols()*i+j];
}

double& Matrix::at(int i, int j) {
    return data_[cols()*i+j];
}

Matrix& Matrix::operator =(const Matrix& mat) {
    cols_ = mat.cols_;
    rows_ = mat.rows_;
    data_ = vector<double>(cols_*rows_);

    for (std::size_t i = 0; i < data_.size(); i++) {
        data_[i] = mat.data_[i];
    }

    return *this;
}

Matrix Matrix::operator +(const Matrix& mat) const {
    assert(cols_ == mat.cols_ && rows_ == mat.rows_);

    Matrix sumMat(cols_, rows_);

    for (size_t i = 0; i < sumMat.data_.size(); i++) {
        sumMat.data_[i] = data_[i] + mat.data_[i];
    }

    return sumMat;
}

Matrix Matrix::operator -(const Matrix& mat) const {
    assert(cols_ == mat.cols_ && rows_ == mat.rows_);

    Matrix diffMat(cols_, rows_);

    for (size_t i = 0; i < diffMat.data_.size(); i++) {
        diffMat.data_[i] = data_[i] - mat.data_[i];
    }

    return diffMat;
}

bool Matrix::operator ==(const Matrix& mat) const {
    if (cols_ != mat.cols_ || rows_ != mat.rows_) {
        return false;
    } else {
        for (size_t i = 0; i < data_.size(); i++) {
            if (data_[i] != mat.data_[i]) {
                return false;
            }
        }

        return true;
    }
}

bool Matrix::operator !=(const Matrix& mat) const {
    return !(*this == mat);
}

ostream& operator <<(ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.cols(); i++) {
        os << "| ";
        for (int j = 0; j < mat.rows(); j++) {
            os << mat.at(i, j) << " ";
        }
        os << "|" << std::endl;
    }

    return os;
}

Matrix operator *(const double& a, const Matrix& mat) {
    Matrix multiplyMat(mat.cols(), mat.rows());
    for (int i = 0; i < mat.rows(); i++) {
        for (int j = 0; j < mat.cols(); j++) {
            multiplyMat.at(i, j) = a*mat.at(i, j);
        }
    }

    return multiplyMat;
}

Matrix Matrix::operator *(const Matrix& mat) const {
    assert(this->cols() == mat.rows());
    Matrix multiplyMat(rows(), this->cols());

    for (int i = 0; i < multiplyMat.cols(); i++) {
        for (int j = 0; j < multiplyMat.rows(); j++) {
            double sum = 0.0;
            for (int k = 0; k < cols(); k++) {
                sum+=this->at(i, k)*mat.at(k, j);
            }
            multiplyMat.at(i, j) = sum;
        }
    }

    return multiplyMat;
}

Matrix operator +(const double& a, const Matrix& mat) {
    return Matrix(mat.cols(), mat.rows(), a) + mat;
}

Matrix operator +(const Matrix& mat, const double& a) {
    return Matrix(mat.cols(), mat.rows(), a) + mat;
}

vector<double> Matrix::data() const {
    return data_;
}

int Matrix::cols() const {
    return cols_;
}

int Matrix::rows() const {
    return rows_;
}

Matrix Matrix::identity(int dims) {
    Matrix mat(dims, dims, 0);
    for (int i = 0; i < dims; i++) {
        mat.at(i, i) = 1.0;
    }

    return mat;
}
