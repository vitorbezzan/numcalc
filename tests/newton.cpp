#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"


float test_sine_float(const float &x) {
    return std::sin(x);
}

double test_sine_double(const double &x) {
    return std::sin(x);
}

TEST(root, newton_float) {
    float x0 = 0.75 * M_PI;
    auto n = numcalc::root::Newton(&test_sine_float, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}

TEST(root, newton_double) {
    double x0 = 0.75 * M_PI;
    auto n = numcalc::root::Newton(&test_sine_double, x0);

    EXPECT_TRUE(std::fabs(M_PI - n.run()) < 0.001);
}
