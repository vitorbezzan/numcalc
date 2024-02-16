#include <gtest/gtest.h>

#include "tests/base_array.cpp"
#include "tests/derivatives.cpp"
#include "tests/matrix.cpp"
#include "tests/newton.cpp"
#include "tests/vector.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
