#include <cmath>

#include <gtest/gtest.h>

#include "../include/numcalc/numcalc.h"

template<typename T>
T de_solve(const T &x, const T &y) {
    return std::exp(x);
}

TEST(explicit_fde, solve_euler) {
    auto solver = numcalc::explicit_fde::Euler<float>(0.0, 1.0);
    auto solution = (solver.run(de_solve<float>, 100)).solution();

    auto last = solution.back().second;

    EXPECT_NEAR(last, exp(1), 0.01);
}

TEST(explicit_fde, solve_rk4) {
    auto solver = numcalc::explicit_fde::RK4<double>(0.0, 1.0);
    auto solution = (solver.run(de_solve<double>, 100)).solution();

    auto last = solution.back().second;

    EXPECT_NEAR(last, exp(1), 0.0001);
}
