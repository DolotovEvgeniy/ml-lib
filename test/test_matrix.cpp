// Copyright 2016 Dolotov Evgeniy

#include <gtest/gtest.h>
#include "ml/linear_algebra.h"

#include <vector>
#include <iostream>

using std::vector;
using namespace ml;
TEST(ML_LINEAR_ALGEBRA, Can_Create_Matrix) {
    // Arrange
    size_t cols = 1;
    size_t rows = 2;

    // Act
    Matrix mat(rows, cols);

    // Assert
    EXPECT_EQ(cols, mat.cols());
    EXPECT_EQ(rows, mat.rows());
}

TEST(ML_LINEAR_ALGEBRA, Can_Create_Matrix_With_Default_Value) {
    // Arrange
    size_t cols = 1;
    size_t rows = 2;
    double defaultValue = 1.0;

    // Act
    Matrix mat(rows, cols, defaultValue);
    vector<double> data = mat.data();

    // Assert
    EXPECT_EQ(cols, mat.cols());
    EXPECT_EQ(rows, mat.rows());

    for (size_t i = 0; i < mat.cols(); i++) {
        for (size_t j = 0; j < mat.rows(); j++) {
            EXPECT_DOUBLE_EQ(defaultValue, mat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Create_Identity_Matrix) {
    // Arrange
    size_t dims = 5;

    // Act
    Matrix mat = Matrix::identity(dims);
    vector<double> data = mat.data();

    // Assert
    EXPECT_EQ(dims, mat.cols());
    EXPECT_EQ(dims, mat.rows());

    for (size_t i = 0; i < dims; i++) {
        for (size_t j = 0; j < dims; j++) {
            if (i == j) {
                EXPECT_DOUBLE_EQ(1.0, data[i+j*dims]);
            } else {
                EXPECT_DOUBLE_EQ(0.0, data[i+j*dims]);
            }
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Set_Matrix_Element) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value = 1;

    Matrix mat(rows, cols, value);

    // Act
    mat.at(0, 1) = 2;

    // Assert
    EXPECT_EQ(mat.at(0, 1), 2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Add_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value1 = 1;
    double value2 = 2;

    Matrix mat1(rows, cols, value1);
    Matrix mat2(rows, cols, value2);

    // Act

    Matrix sumMat = mat1 + mat2;

    // Assert

    EXPECT_EQ(cols, sumMat.cols());
    EXPECT_EQ(rows, sumMat.rows());

    for (size_t i = 0; i < sumMat.cols(); i++) {
        for (size_t j = 0; j < sumMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(value1 + value2, sumMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Substract_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value1 = 1;
    double value2 = 2;

    Matrix mat1(rows, cols, value1);
    Matrix mat2(rows, cols, value2);

    // Act

    Matrix diffMat = mat1 - mat2;

    // Assert

    EXPECT_EQ(cols, diffMat.cols());
    EXPECT_EQ(rows, diffMat.rows());

    for (size_t i = 0; i < diffMat.cols(); i++) {
        for (size_t j = 0; j < diffMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(value1 - value2, diffMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Compare_Equal_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value = 1;

    Matrix mat1(rows, cols, value);
    Matrix mat2(rows, cols, value);

    // Act & Assert
    EXPECT_EQ(mat1, mat2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Compare_Not_Equal_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value1 = 1;
    double value2 = 2;

    Matrix mat1(rows, cols, value1);
    Matrix mat2(rows, cols, value2);

    // Act & Assert
    EXPECT_NE(mat1, mat2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Compare_Matrix_With_Not_Same_Size) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    Matrix mat1(rows, cols);
    Matrix mat2(cols, rows);

    // Act & Assert
    EXPECT_NE(mat1, mat2);
}

TEST(ML_LINEAR_ALGEBRA, Can_Equate_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value = 1;

    Matrix mat(rows, cols, value);

    // Act
    Matrix mat1;
    mat1 = mat;

    // Assert
    EXPECT_EQ(mat, mat1);
}

TEST(ML_LINEAR_ALGEBRA, Can_Copy_Matrix) {
    // Arrange
    size_t rows = 1;
    size_t cols = 2;

    double value = 1;

    Matrix mat(rows, cols, value);

    // Act
    Matrix mat1(mat);

    // Assert
    EXPECT_EQ(mat, mat1);
}

TEST(ML_LINEAR_ALGEBRA, Can_Mult_Quad_Matrix) {
    // Arrange
    size_t rows = 2;
    size_t cols = 2;

    double value1 = 2;
    double value2 = 3;

    Matrix mat1(rows, cols, value1);
    Matrix mat2(rows, cols, value2);

    // Act
    Matrix multMat = mat1 * mat2;

    // Assert

    EXPECT_EQ(cols, multMat.cols());
    EXPECT_EQ(rows, multMat.rows());

    for (size_t i = 0; i < multMat.cols(); i++) {
        for (size_t j = 0; j < multMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(value1*value2 + value1*value2, multMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Mult_Matrix) {
    // Arrange
    size_t rows = 2;
    size_t cols = 3;

    double value1 = 2;
    double value2 = 3;

    Matrix mat1(rows, cols, value1);
    Matrix mat2(cols, rows, value2);

    // Act
    Matrix multMat = mat1 * mat2;

    // Assert
    EXPECT_EQ(rows, multMat.cols());
    EXPECT_EQ(rows, multMat.rows());

    double resultValue;
    resultValue = value1*value2*3;
    for (size_t i = 0; i < multMat.cols(); i++) {
        for (size_t j = 0; j < multMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(resultValue, multMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Multiply_Identity_Matrix_Is_Identity) {
    // Arrange
    size_t dims = 2;

    Matrix identity(Matrix::identity(dims));

    // Act
    Matrix multMat = identity*identity;

    // Assert
    EXPECT_EQ(identity, multMat);
}

TEST(ML_LINEAR_ALGEBRA, Can_Mult_On_Scalar) {
    // Arrange
    size_t rows = 2;
    size_t cols = 3;

    double a = 2;
    double value = 3;

    Matrix mat(rows, cols, value);

    // Act
    Matrix multMat = a*mat;

    // Assert
    EXPECT_EQ(cols, multMat.cols());
    EXPECT_EQ(rows, multMat.rows());

    for (size_t i = 0; i < multMat.cols(); i++) {
        for (size_t j = 0; j < multMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(a*value, multMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Left_Add_Scalar_To_Matrix) {
    // Arrange
    size_t rows = 2;
    size_t cols = 3;

    double a = 1;
    double value = 2;

    Matrix mat(rows, cols, value);

    // Act
    Matrix sumMat = a + mat;

    // Assert
    EXPECT_EQ(cols, sumMat.cols());
    EXPECT_EQ(rows, sumMat.rows());

    for (size_t i = 0; i < sumMat.cols(); i++) {
        for (size_t j = 0; j < sumMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(a+value, sumMat.at(j, i));
        }
    }
}

TEST(ML_LINEAR_ALGEBRA, Can_Right_Add_Scalar_To_Matrix) {
    // Arrange
    size_t rows = 2;
    size_t cols = 3;

    double a = 1;
    double value = 2;

    Matrix mat(rows, cols, value);

    // Act
    Matrix sumMat = mat + a;

    // Assert
    EXPECT_EQ(cols, sumMat.cols());
    EXPECT_EQ(rows, sumMat.rows());

    for (size_t i = 0; i < sumMat.cols(); i++) {
        for (size_t j = 0; j < sumMat.rows(); j++) {
            EXPECT_DOUBLE_EQ(a+value, sumMat.at(j, i));
        }
    }
}


