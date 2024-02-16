#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "./include/numcalc/base_array.h"
#include "./include/numcalc/derivative.h"
#include "./include/numcalc/matrix.h"
#include "./include/numcalc/rootfind_newton.h"
#include "./include/numcalc/vector.h"

float test_sine_float(const float &x) {
    return std::sin(x);
}

double test_sine_double(const double &x) {
    return std::sin(x);
}

TEST(Derivatives, TestDerivativeFloat) {
    float increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        float cos_v = std::cos(i * increment);
        float d =
            Derivatives::derivative(&test_sine_float, i * increment, (float)0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}

TEST(Derivatives, TestDerivativeDouble) {
    double increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        double cos_v = std::cos(i * increment);
        double d = Derivatives::derivative(&test_sine_double, i * increment,
                                           (double)0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}

TEST(NewtonRoot, TestNewtonFloat) {
    float x0 = 0.75 * M_PI;
    auto n = RootFind::Newton(&test_sine_float, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}

TEST(NewtonRoot, TestNewtonDouble) {
    double x0 = 0.75 * M_PI;
    auto n = RootFind::Newton(&test_sine_double, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}

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
    A({0,0,1}) = 4.5;

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

    b({0,0,0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(BaseArray, TestEq) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    auto b = A;

    EXPECT_EQ(b.ndim(), 3);
    EXPECT_EQ(b.nelements(), 2);

    EXPECT_EQ(b({0,0,0}), 3.0);

    b({0,0,0}) = 6.1;

    EXPECT_NE(A({0,0,0}), b({0,0,0}));
}

TEST(BaseArray, TestSum) {
    auto A = Matrix::BaseArray({1, 1, 2}, 3.0);
    auto B = Matrix::BaseArray({1, 1, 2}, 7.0);

    EXPECT_EQ((A + B)({0,0,1}), 10.0);
    EXPECT_EQ((A - B)({0,0,1}), -4.0);
}

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

TEST(Matrix, MatrixScalar) {
    auto M = Matrix::Matrix<double>(3,3, 6.0);
    auto p2 = M * 0.5;

    EXPECT_NEAR(p2(1,1), 3.0, 0.0001);
}

TEST(Matrix, ScalarMatrix) {
    auto M = Matrix::Matrix<double>(3,3, 6.0);
    auto p1 = 0.5 * M;

    EXPECT_NEAR(p1(2,2), 3.0, 0.0001);
}

TEST(Matrix, MatrixVecFloat) {
    auto M = Matrix::Matrix<float>(3,3, 6.0);
    auto v = Matrix::Vector<float>(3, 1.0);

    auto p = M * v;
    EXPECT_NEAR(p[0], 18.0, 0.0001);
}

TEST(Matrix, MatrixVecDouble) {
    auto M = Matrix::Matrix<double>(3,3, 6.0);
    auto v = Matrix::Vector<double>(3, 1.0);

    auto p = M * v;
    EXPECT_NEAR(p[0], 18.0, 0.0001);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
