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

if (APPLE)
    execute_process(
            COMMAND brew --prefix
            RESULT_VARIABLE HOMEBREW
            OUTPUT_VARIABLE HOMEBREW_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS Homebrew Prefix: ${HOMEBREW_PREFIX})

    set(CMAKE_PREFIX_PATH
            "${HOMEBREW_PREFIX}"
            "${HOMEBREW_PREFIX}/opt/openblas"
            "${HOMEBREW_PREFIX}/opt/lapack"
    )

    list(TRANSFORM CMAKE_PREFIX_PATH APPEND "/include"
            OUTPUT_VARIABLE CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}")

    set(CMAKE_FIND_FRAMEWORK NEVER)
    set(CMAKE_FIND_APPBUNDLE NEVER)

    set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH FALSE)
    set(CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH FALSE)

    include_directories(
            "${HOMEBREW_PREFIX}/opt/openblas/include"
            "${HOMEBREW_PREFIX}/opt/lapack/include"
    )

    add_executable(run_tests tests.cpp)
    target_link_libraries(run_tests GTest::gtest GTest::gtest_main cblas lapack pthread)

    add_library(numcalc SHARED library.cpp)
    target_link_libraries(numcalc cblas lapack pthread)

elseif (UNIX)
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)

    message(STATUS BLAS found: ${BLAS_LIBRARIES})
    message(STATUS LAPACK found: ${LAPACK_LIBRARIES})

    add_executable(run_tests tests.cpp)
    target_link_libraries(run_tests GTest::gtest GTest::gtest_main ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)

    add_library(numcalc SHARED library.cpp)
    target_link_libraries(numcalc ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} pthread)

endif ()
