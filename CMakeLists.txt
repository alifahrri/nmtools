cmake_minimum_required(VERSION 3.0.2)
project(numeric)

include_directories(include)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(numeric_tests tests/tests.cpp 
    tests/roots/bracketing.cpp
    tests/roots/open.cpp
)
target_link_libraries(numeric_tests ${GTEST_BOTH_LIBRARIES} pthread)
add_test(all_numeric_tests numeric_tests)

# include(GoogleTest)
# add_executable(numeric_tests tests/tests.cpp tests/roots/bisection.cpp)
# gtest_add_test(TARGET numeric_tests)