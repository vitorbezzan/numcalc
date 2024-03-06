#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"

template<typename T>
T test_sine(const T &x) {
    return std::sin(x);
}

TEST(root, newton_float) {
    float x0 = 0.75 * M_PI;
    auto n = numcalc::root::Newton(test_sine<float>, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}

TEST(root, newton_double) {
    double x0 = 0.75 * M_PI;
    auto n = numcalc::root::Newton(test_sine<double>, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}
