#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"

TEST(multiarray, base_constructor_1) {
    auto A = numcalc::multirray::BaseArray({2, 2, 2});

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 8);
}

TEST(multiarray, base_constructor_2) {
    auto A = numcalc::multirray::BaseArray({1, 1, 2}, 3.0);

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 2);
    EXPECT_EQ(A.data()[0], 3.0);
}

TEST(multiarray, operator_pas) {
    auto A = numcalc::multirray::BaseArray({1, 1, 2}, 3.0);
    A({0, 0, 1}) = 4.5;

    EXPECT_EQ(A.ndim(), 3);
    EXPECT_EQ(A.nelements(), 2);

    EXPECT_EQ(A({0,0,0}), 3.0);
    EXPECT_EQ(A({0,0,1}), 4.5);
}

TEST(multiarray, copy_reference) {
    auto A = numcalc::multirray::BaseArray({1, 1, 2}, 3.0);
    auto b = numcalc::multirray::BaseArray(A);

    EXPECT_EQ(b.ndim(), 3);
    EXPECT_EQ(b.nelements(), 2);

    EXPECT_EQ(b({0,0,0}), 3.0);

    b({0, 0, 0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(multiarray, equality) {
    auto A = numcalc::multirray::BaseArray({1, 1, 2}, 3.0);
    auto b = A;

    EXPECT_EQ(b.ndim(), 3);
    EXPECT_EQ(b.nelements(), 2);

    EXPECT_EQ(b({0,0,0}), 3.0);

    b({0, 0, 0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(multiarray, sum) {
    auto A = numcalc::multirray::BaseArray({1, 1, 2}, 3.0);
    auto B = numcalc::multirray::BaseArray({1, 1, 2}, 7.0);

    EXPECT_EQ((A + B)({0,0,1}), 10.0);
    EXPECT_EQ((A - B)({0,0,1}), -4.0);
}
