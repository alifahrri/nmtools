cmake_minimum_required(VERSION 3.10)
project(nmtools-benchmark-bm)

find_package(benchmark REQUIRED)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

add_executable(
    ${PROJECT_NAME}
    src/benchmark.cpp
)

target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -O3 -march=native
)