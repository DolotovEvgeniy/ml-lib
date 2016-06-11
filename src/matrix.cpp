// Copyright 2016 Dolotov Evgeniy

#include "ml/matrix.h"

#include <assert.h>
#include <math.h>

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;
using  ml::Matrix;
using  ml::Vector;
Matrix::Matrix() {
    cols_ = 1;
    rows_ = 1;
    data_ = vector<double>(cols_*rows_, 0);
}

Matrix::Matrix(int rows, int cols, double defaultValue) {
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

double Matrix::at(int row, int col) const {
    return data_[cols()*row+col];
}

double& Matrix::at(int row, int col) {
    return data_[cols()*row+col];
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

    Matrix sumMat(rows_, cols_);

    for (size_t i = 0; i < sumMat.data_.size(); i++) {
        sumMat.data_[i] = data_[i] + mat.data_[i];
    }

    return sumMat;
}

Matrix Matrix::operator -(const Matrix& mat) const {
    assert(cols_ == mat.cols_ && rows_ == mat.rows_);

    Matrix diffMat(rows_, cols_);

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

ostream& ml::operator <<(ostream& os, const Matrix& mat) {
    for (size_t i = 0; i < mat.cols(); i++) {
        os << "| ";
        for (size_t j = 0; j < mat.rows(); j++) {
            os << mat.at(i, j) << " ";
        }
        os << "|" << std::endl;
    }

    return os;
}

Matrix ml::operator *(const double& a, const Matrix& mat) {
    Matrix multiplyMat(mat.rows(), mat.cols());
    for (size_t i = 0; i < mat.rows(); i++) {
        for (size_t j = 0; j < mat.cols(); j++) {
            multiplyMat.at(i, j) = a*mat.at(i, j);
        }
    }

    return multiplyMat;
}

Matrix Matrix::operator *(const Matrix& mat) const {
    assert(this->cols() == mat.rows());
    Matrix multiplyMat(rows(), mat.cols());

    for (size_t i = 0; i < multiplyMat.cols(); i++) {
        for (size_t j = 0; j < multiplyMat.rows(); j++) {
            double sum = 0.0;
            for (size_t k = 0; k < cols(); k++) {
                sum+=this->at(i, k)*mat.at(k, j);
            }
            multiplyMat.at(i, j) = sum;
        }
    }

    return multiplyMat;
}

Matrix ml::operator +(const double& a, const Matrix& mat) {
    return Matrix(mat.rows(), mat.cols(), a) + mat;
}

Matrix ml::operator +(const Matrix& mat, const double& a) {
    return Matrix(mat.rows(), mat.cols(), a) + mat;
}

vector<double> Matrix::data() const {
    return data_;
}

size_t Matrix::cols() const {
    return cols_;
}

size_t Matrix::rows() const {
    return rows_;
}

Matrix Matrix::identity(int dims) {
    Matrix mat(dims, dims, 0);
    for (int i = 0; i < dims; i++) {
        mat.at(i, i) = 1.0;
    }

    return mat;
}

Vector Matrix::row(int i) {
    Vector vec(this->cols());

    for (size_t j = 0; j < cols(); j++) {
        vec.at(j) = this->at(i, j);
    }

    return vec;
}

Vector Matrix::col(int i) {
    Vector vec(this->rows());

    for (size_t j = 0; j < rows(); j++) {
        vec.at(j) = this->at(j, i);
    }

    return vec;
}
