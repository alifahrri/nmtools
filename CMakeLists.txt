cmake_minimum_required(VERSION 3.0.2)
project(numeric)

add_compile_options(-std=c++17)

include_directories(include)
add_compile_options(-std=c++17)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(numeric_tests tests/tests.cpp 
    tests/utility.cpp
    tests/roots/bracketing.cpp
    tests/roots/open.cpp
    tests/optimization/unconstrained.cpp
    tests/integration/trapezoidal.cpp
    tests/differentiation/finite.cpp
    tests/taylor/taylor.cpp
    tests/curvefit/sinusoid.cpp
    tests/curvefit/spline.cpp
    tests/fourier/series.cpp
    tests/utility/utility.cpp
    tests/fourier/transform.cpp
    tests/ode/euler.cpp
    tests/ode/runge_kutta.cpp
    tests/linalg/elimination.cpp
)
target_link_libraries(numeric_tests ${GTEST_BOTH_LIBRARIES} pthread)
target_compile_options(numeric_tests PRIVATE -g)
add_test(all_numeric_tests numeric_tests)

# include(GoogleTest)
# add_executable(numeric_tests tests/tests.cpp tests/roots/bisection.cpp)
# gtest_add_test(TARGET numeric_tests)

option(BUILD_EXAMPLES "build example programs" OFF)
option(BUILD_BENCHMARKS "build benchmark programs" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif(BUILD_BENCHMARKS)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
    NAME ${PROJECT_NAME}_coverage 
    EXECUTABLE numeric_tests
    EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "${GTEST_INCLUDE_DIRS}/*" "/usr/*"
)