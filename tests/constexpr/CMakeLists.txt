cmake_minimum_required(VERSION 3.13)
project(numeric-tests-constexpr)

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

set(NMTOOLS_CONSTEXPR_TEST_SOURCES
    src/atleast_1d.cpp
    src/atleast_2d.cpp
    src/atleast_nd.cpp
    src/broadcast_arrays.cpp
    src/broadcast_to.cpp
    src/matmul.cpp
    src/moveaxis.cpp
    src/pad.cpp
    src/roll.cpp
    src/transpose.cpp
)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_CONSTEXPR_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17)

if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()