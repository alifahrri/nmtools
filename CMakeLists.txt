cmake_minimum_required(VERSION 3.0.2)
project(numeric)

include_directories(include)
add_compile_options(-std=c++17)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(numeric_tests tests/tests.cpp 
    tests/roots/bracketing.cpp
    tests/roots/open.cpp
    tests/optimization/unconstrained.cpp
    tests/integration/trapezoidal.cpp
    tests/differentiation/finite.cpp
    tests/taylor/taylor.cpp
    tests/curvefit/sinusoid.cpp
    tests/fourier/series.cpp
    tests/utility/utility.cpp
    tests/fourier/transform.cpp
)
target_link_libraries(numeric_tests ${GTEST_BOTH_LIBRARIES} pthread)
target_compile_options(numeric_tests PRIVATE -g)
add_test(all_numeric_tests numeric_tests)

# include(GoogleTest)
# add_executable(numeric_tests tests/tests.cpp tests/roots/bisection.cpp)
# gtest_add_test(TARGET numeric_tests)