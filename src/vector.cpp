// Copyright 2016 Dolotov Evgeniy

#include "ml/vector.h"

#include <assert.h>
#include <math.h>

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;
using ml::Vector;
Vector::Vector(size_t dims, double defaultValue) {
    dims_ = dims;
    data_ = vector<double>(dims_, defaultValue);
}

Vector::Vector(const Vector& vec) {
    dims_ = vec.dims_;
    data_ = vector<double>(dims_);

    for (size_t i = 0; i < dims_; i++) {
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

    for (size_t i = 0; i < dims_; i++) {
        data_[i] = vec.data_[i];
    }

    return *this;
}

Vector Vector::operator +(const Vector& vec) const {
    Vector sumVec(vec.dims_);

    for (size_t i = 0; i < dims_; i++) {
        sumVec.data_[i] = data_[i]+vec.data_[i];
    }

    return sumVec;
}

Vector Vector::operator -(const Vector& vec) const {
    Vector diffVec(vec.dims_);

    for (size_t i = 0; i < dims_; i++) {
        diffVec.data_[i] = data_[i]-vec.data_[i];
    }

    return diffVec;
}

bool Vector::operator ==(const Vector& vec) const {
    if (dims_ != vec.dims_) {
        return false;
    }

    for (size_t i = 0; i < dims_; i++) {
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

size_t Vector::dims() const {
    return dims_;
}

std::ostream& ml::operator <<(std::ostream& os, const Vector& vec) {
    os << "(";
    for (size_t i = 0; i < vec.dims()-1; i++) {
        os << vec.at(i) << ", ";
    }
    os << vec.at(vec.dims()-1) << ")" << std::endl;
    return os;
}

Vector ml::operator *(const double& a, const Vector& vec) {
    Vector multVec(vec.dims());

    for (size_t i = 0; i < vec.dims(); i++) {
        multVec.at(i) = a*vec.at(i);
    }

    return multVec;
}

Vector ml::operator +(const double& a, const Vector& vec) {
    return Vector(vec.dims(), a) + vec;
}

Vector ml::operator +(const Vector& vec, const double& a) {
    return Vector(vec.dims(), a) + vec;
}

double Vector::length() const {
    double sum = 0;
    for (size_t i = 0; i < dims(); i++) {
        sum+=at(i)*at(i);
    }

    return sqrt(sum);
}
double ml::dot(const Vector &vec1, const Vector &vec2) {
    int sum = 0;
    for (size_t i = 0; i< vec1.dims(); i++) {
        sum+=vec1.at(i)*vec2.at(i);
    }

    return sum;
}

double ml::distance(const Vector &vec1, const Vector &vec2) {
    Vector diffVec = vec1 - vec2;
    return diffVec.length();
}
