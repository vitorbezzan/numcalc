#include <cmath>
#include <cstdlib>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"


float der_sine_float(const float &x) {
    return std::sin(x);
}

double der_sine_double(const double &x) {
    return std::sin(x);
}

TEST(Derivatives, TestDerivativeFloat) {
    float increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        float cos_v = std::cos(i * increment);
        float d =
                Derivatives::derivative(&der_sine_float, i * increment, (float) 0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}

TEST(Derivatives, TestDerivativeDouble) {
    double increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        double cos_v = std::cos(i * increment);
        double d = Derivatives::derivative(&der_sine_double, i * increment,
                                           (double) 0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}
