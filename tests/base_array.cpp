#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"

TEST(BaseArray, TestConstructor1) {
    auto A = Matrix::BaseArray({2, 2, 2});

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 8);
}

TEST(BaseArray, TestConstructor2) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 2);
    EXPECT_EQ(A.data()[0], 3.0);
}

TEST(BaseArray, TestOperatorPas) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    A({0, 0, 1}) = 4.5;

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 2);

    EXPECT_EQ(A({0,0,0}), 3.0);
    EXPECT_EQ(A({0,0,1}), 4.5);
}

TEST(BaseArray, TestCopyRef) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    auto b = Matrix::BaseArray(A);

    EXPECT_EQ(b.ndim(), 3);
    EXPECT_EQ(b.nelements(), 2);

    EXPECT_EQ(b({0,0,0}), 3.0);

    b({0, 0, 0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(BaseArray, TestEq) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    auto b = A;

    EXPECT_EQ(b.ndim(), 3);
    EXPECT_EQ(b.nelements(), 2);

    EXPECT_EQ(b({0,0,0}), 3.0);

    b({0, 0, 0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(BaseArray, TestSum) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    auto B = Matrix::BaseArray({1, 1, 2}, 7.0);

    EXPECT_EQ((A + B)({0,0,1}), 10.0);
    EXPECT_EQ((A - B)({0,0,1}), -4.0);
}
