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

TEST(derivatives, derivative_float) {
    float increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        float cos_v = std::cos(i * increment);
        float d =
                numcalc::derivatives::derivative(&der_sine_float, i * increment, (float) 0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}

TEST(derivatives, derivative_double) {
    double increment = 0.01;
    for (int i = 0; i <= 100; i++) {
        double cos_v = std::cos(i * increment);
        double d = numcalc::derivatives::derivative(&der_sine_double, i * increment,
                                                    (double) 0.001);

        EXPECT_TRUE(std::fabs(cos_v - d) < 0.001);
    }
}
