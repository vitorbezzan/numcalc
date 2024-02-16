#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"


TEST(Matrix, MatrixScalar) {
    auto M = Matrix::Matrix<double>(3, 3, 6.0);
    auto p2 = M * 0.5;

    EXPECT_NEAR(p2(1,1), 3.0, 0.0001);
}

TEST(Matrix, ScalarMatrix) {
    auto M = Matrix::Matrix<double>(3, 3, 6.0);
    auto p1 = 0.5 * M;

    EXPECT_NEAR(p1(2,2), 3.0, 0.0001);
}

TEST(Matrix, MatrixVecFloat) {
    auto M = Matrix::Matrix<float>(3, 3, 6.0);
    auto v = Matrix::Vector<float>(3, 1.0);

    auto p = M * v;
    EXPECT_NEAR(p[0], 18.0, 0.0001);
}

TEST(Matrix, MatrixVecDouble) {
    auto M = Matrix::Matrix<double>(3, 3, 6.0);
    auto v = Matrix::Vector<double>(3, 1.0);

    auto p = M * v;
    EXPECT_NEAR(p[0], 18.0, 0.0001);
}
