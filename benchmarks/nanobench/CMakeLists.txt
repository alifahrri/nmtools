cmake_minimum_required(VERSION 3.10)
project(nmtools-benchmark-nanobench)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(
    ${PROJECT_NAME}-ode
    src/ode.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-ode
    COMPILE_OPTIONS -O3 -march=native
)

add_executable(
    ${PROJECT_NAME}-fibonacci_search
    src/fibonacci_search.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-fibonacci_search
    COMPILE_OPTIONS -O3 -march=native
)

add_executable(
    ${PROJECT_NAME}-cubic_spline
    src/spline.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-cubic_spline
    COMPILE_OPTIONS -O3 -march=native
)

add_executable(
    ${PROJECT_NAME}-linalg
    src/linalg.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-linalg
    COMPILE_OPTIONS -O3 -march=native
)

add_executable(
    ${PROJECT_NAME}
    src/benchmark.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -O3 -march=native
)