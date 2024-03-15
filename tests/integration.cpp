#include <cmath>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"

template<typename T>
T to_integrate(const T &x) {
    return std::sin(x);
}

TEST(integration_1d, rectangle) {
    auto subdivision = M_PI / 10;
    auto result = numcalc::integration_1d::Rectangle<double>().integrate(to_integrate<double>, 0.0, M_PI, 10);

    auto maximum_error = (M_PI / 24) * std::pow(subdivision, 2);
    auto error = std::fabs(result - 2);

    EXPECT_NEAR(error, maximum_error, 0.01);
}

TEST(integration_1d, trapezium) {
    auto result = numcalc::integration_1d::Trapezium<double>().integrate(to_integrate<double>, 0.0, M_PI, 10);

    auto maximum_error = std::fabs((std::pow(M_PI, 3) / 1200));
    auto error = std::fabs(result - 2);

    EXPECT_LE(error, maximum_error);
}

TEST(integration_1d, simpson) {
    auto subdivision = M_PI / 10;
    auto result = numcalc::integration_1d::Simpson<double>().integrate(to_integrate<double>, 0.0, M_PI, 10);

    auto maximum_error = (M_PI / 180) * std::pow(subdivision, 4);
    auto error = std::fabs(result - 2);

    EXPECT_LE(error, maximum_error);
}