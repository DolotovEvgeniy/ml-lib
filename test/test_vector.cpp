// Copyright 2016 Dolotov Evgeniy

#include <gtest/gtest.h>
#include "ml/linear_algebra.h"

#include <vector>
#include <iostream>
#include <cmath>

using std::vector;
using namespace ml;

TEST(ML_LINEAR_ALGEBRA, Can_Create_Vector) {
    // Arrange
    size_t dims = 2;

    // Act
    Vector vec(2);

    // Assert
    EXPECT_EQ(vec.dims(), dims);
}

TEST(ML_LINEAR_ALGEBRA, Can_Create_Vector_With_Default_Value) {
    // Arrange
    size_t dims = 2;
    double value = 1;

    // Act
    Vector vec(dims, value);

    // Assert
    EXPECT_EQ(vec.dims(), dims);
    for (size_t i = 0; i < vec.dims(); i++) {
        EXPECT_EQ(vec.at(i), value);
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Set_Element) {
    // Arrange
    size_t dims = 2;
    double value = 1;
    Vector vec(dims, value);

    // Act
    vec.at(0) = 2;

    // Assert
    EXPECT_EQ(vec.at(0), 2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Add_Vector) {
    // Arrange
    size_t dims = 2;

    double value1 = 1;
    double value2 = 2;

    Vector vec1(dims, value1);
    Vector vec2(dims, value2);

    // Act
    Vector sumVec = vec1 + vec2;

    // Assert
    EXPECT_EQ(sumVec.dims(), dims);
    for (size_t i = 0; i < sumVec.dims(); i++) {
        EXPECT_EQ(sumVec.at(i), value1+value2);
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Substract_Vector) {
    // Arrange
    size_t dims = 2;

    double value1 = 1;
    double value2 = 2;

    Vector vec1(dims, value1);
    Vector vec2(dims, value2);

    // Act
    Vector diffVec = vec1 - vec2;

    // Assert
    EXPECT_EQ(diffVec.dims(), dims);
    for (size_t i = 0; i < diffVec.dims(); i++) {
        EXPECT_EQ(diffVec.at(i), value1-value2);
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Equal_Vector) {
    // Arrange
    size_t dims = 2;

    double value = 1;

    Vector vec(dims, value);

    // Act
    Vector vec2;
    vec2 = vec;

    // Assert
    EXPECT_EQ(vec2.dims(), vec.dims());
    for (size_t i = 0; i < vec.dims(); i++) {
        EXPECT_EQ(vec.at(i), vec2.at(i));
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Compare_Equal_Vectors) {
    // Arrange
    size_t dims = 2;
    double value = 1;
    Vector vec1(dims, value);
    Vector vec2(dims, value);

    // Act & Assert
    EXPECT_EQ(vec1, vec2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Compare_Not_Equal_Vector) {
    // Arrange
    size_t dims = 2;
    double value1 = 1;
    double value2 = 2;
    Vector vec1(dims, value1);
    Vector vec2(dims, value2);

    // Act & Assert
    EXPECT_NE(vec1, vec2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Calculate_Length) {
    // Arrange
    size_t dims = 2;
    double value = 1;

    Vector vec(dims, value);

    // Act
    double length = vec.length();

    // Assert
    EXPECT_EQ(length, std::sqrt(2));
}

TEST(ML_LINEAR_ALGEBRA, Can_Mult_At_Scalar) {
    // Arrange
    size_t dims = 2;
    double value = 2;
    double a = 2;

    Vector vec(dims, value);

    // Act
    Vector multVec = a*vec;

    // Assert
    EXPECT_EQ(multVec.dims(), dims);
    for (size_t i = 0; i < multVec.dims(); i++) {
        EXPECT_EQ(a*value, multVec.at(i));
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Left_Add_Scalar_To_Vector) {
    // Arrange
    size_t dims = 2;
    double value = 2;
    double a = 2;

    Vector vec(dims, value);

    // Act
    Vector sumVec = a+vec;

    // Assert
    EXPECT_EQ(sumVec.dims(), dims);
    for (size_t i = 0; i < sumVec.dims(); i++) {
        EXPECT_EQ(a+value, sumVec.at(i));
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Right_Add_Scalar_To_Vector) {
    // Arrange
    size_t dims = 2;
    double value = 2;
    double a = 2;

    Vector vec(dims, value);

    // Act
    Vector sumVec = vec+a;

    // Assert
    EXPECT_EQ(sumVec.dims(), dims);
    for (size_t i = 0; i < sumVec.dims(); i++) {
        EXPECT_EQ(a+value, sumVec.at(i));
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Dot_Two_Vector) {
    // Arrange
    size_t dims = 2;
    double value1 = 2;
    double value2 = 3;

    Vector vec1(dims, value1);
    Vector vec2(dims, value2);

    // Act
    double a = dot(vec1, vec2);

    // Assert
    EXPECT_EQ(a, 12);
}

TEST(ML_LINEAR_ALGEBRA, Can_Calculate_Distance) {
    // Arrange
    size_t dims = 2;
    double value1 = 2;
    double value2 = 3;

    Vector vec1(dims, value1);
    Vector vec2(dims, value2);

    // Act
    double a = ml::distance(vec1, vec2);

    // Assert
    EXPECT_EQ(a, std::sqrt(2));
}
