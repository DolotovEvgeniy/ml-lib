// Copyright 2016 Dolotov Evgeniy

#ifndef INCLUDE_ML_VECTOR_H_
#define INCLUDE_ML_VECTOR_H_

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

#endif  // INCLUDE_ML_VECTOR_H_
