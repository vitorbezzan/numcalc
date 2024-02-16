cmake_minimum_required(VERSION 3.27)

project(numcalc LANGUAGES CXX)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_FEATURE 1)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
set(VERSION "${VERSION}.${VERSION_FEATURE}.${VERSION_PATCH}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

message( STATUS BLAS found: ${BLAS_LIBRARIES} )
message( STATUS LAPACK found: ${LAPACK_LIBRARIES} )

# Test suite executable
add_executable(
    run_tests tests.cpp
)
target_link_libraries(run_tests ${GTEST_LIBRARIES} cblas lapack pthread)

# Library object
add_library(
        numcalc SHARED
        library.cpp
        include/numcalc/rootfind.h
        include/numcalc/numcalc.h
        include/numcalc/derivative.h
        include/numcalc/rootfind_newton.h
        include/numcalc/base_array.h
        include/numcalc/vector.h
        include/numcalc/matrix.h
)
target_link_libraries(numcalc cblas lapack pthread)
