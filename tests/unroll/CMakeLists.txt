cmake_minimum_required(VERSION 3.13)
project(numeric-tests-unroll)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

enable_testing()

if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR EMSCRIPTEN OR ANDROID OR MSYS)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

add_executable(${PROJECT_NAME}-doctest
    tests.cpp
    context.cpp
    src/add.cpp
    src/multiply.cpp
    src/subtract.cpp
    src/divide.cpp
    src/sin.cpp
    src/cos.cpp
    src/tan.cpp
    src/sinh.cpp
    src/cosh.cpp
    src/tanh.cpp
    src/exp.cpp
    src/exp2.cpp
    src/log.cpp
    src/log1p.cpp
    src/log2.cpp
    src/log10.cpp
    src/maximum.cpp
    src/minimum.cpp
    src/less.cpp
    src/less_equal.cpp
    src/greater.cpp
    src/greater_equal.cpp
    src/sum.cpp
    src/prod.cpp
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)
