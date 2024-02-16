#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"


TEST(Vector, VectorInstanceMultiply) {
    auto V1 = Matrix::Vector(3, 1.0);
    auto V2 = Matrix::Vector(3, 1.0);
    auto Vn = Matrix::Vector(3, 1.0) * 5.0;

    auto V3 = 3.0 * V1;
    auto V4 = V2 * 1.5;

    EXPECT_EQ(V3[0], 3.0);
    EXPECT_EQ(V4[1], 1.5);
    EXPECT_EQ(Vn[2], 5.0);
}

TEST(Vector, VectorDot) {
    auto V1 = Matrix::Vector(3, 1.0);

    EXPECT_NEAR(Matrix::fabs(V1), std::sqrt(3), 0.0001);
}
