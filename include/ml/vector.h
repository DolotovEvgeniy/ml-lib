// Copyright 2016 Dolotov Evgeniy

#ifndef INCLUDE_ML_VECTOR_H_
#define INCLUDE_ML_VECTOR_H_

#include <vector>
#include <iostream>
namespace ml {
class Vector {
 public:
    explicit Vector(size_t dims = 1, double defaultValue = 0);
    Vector(const Vector& vec);
    double at(int i) const;
    double& at(int i);
    size_t dims() const;
    Vector& operator =(const Vector& vec);
    Vector operator +(const Vector& vec) const;
    Vector operator -(const Vector& vec) const;
    bool operator ==(const Vector& vec) const;
    bool operator !=(const Vector& vec) const;
    std::vector<double> data() const;
    double length() const;
 private:
    std::vector<double> data_;
    size_t dims_;
};

std::ostream& operator <<(std::ostream& os, const Vector& vec);

Vector operator *(const double& a, const Vector& vec);
Vector operator +(const double& a, const Vector& vec);
Vector operator +(const Vector& vec, const double& a);

double dot(const Vector& vec1, const Vector& vec2);
double distance(const Vector& vec1, const Vector& vec2);
}  // namespace ml
#endif  // INCLUDE_ML_VECTOR_H_
