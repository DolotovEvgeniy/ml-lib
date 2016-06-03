// Copyright 2016 Dolotov Evgeniy

#include <gtest/gtest.h>
#include "ml/linear_algebra.h"

#include <vector>
#include <iostream>

using std::vector;

TEST(ML_LINEAR_ALGEBRA, Can_Create_Matrix) {
    // Arrange
    int cols = 1;
    int rows = 2;

    // Act
    Matrix mat(cols, rows);

    // Assert
    EXPECT_EQ(cols, mat.cols());
    EXPECT_EQ(rows, mat.rows());
}

TEST(ML_LINEAR_ALGEBRA, Can_Create_Matrix_With_Default_Value) {
    // Arrange
    int cols = 1;
    int rows = 2;
    double defaultValue = 1.0;

    // Act
    Matrix mat(cols, rows, defaultValue);
    vector<double> data = mat.data();

    // Assert
    EXPECT_EQ(cols, mat.cols());
    EXPECT_EQ(rows, mat.rows());
    for(size_t i = 0; i < data.size(); i++) {
        EXPECT_DOUBLE_EQ(defaultValue, data[i]);
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Create_Identity_Matrix) {
    // Arrange
    int dims = 5;

    // Act
    Matrix mat = Matrix::identity(dims);
    vector<double> data = mat.data();

    // Assert
    EXPECT_EQ(dims, mat.cols());
    EXPECT_EQ(dims, mat.rows());
    std::cout << mat + 3*mat;
    for (int i = 0; i < dims; i++) {
        for (int j = 0; j < dims; j++) {
            if (i == j) {
                EXPECT_DOUBLE_EQ(1.0, data[i+j*dims]);
            } else {
                EXPECT_DOUBLE_EQ(0.0, data[i+j*dims]);
            }
        }
    }
}
