cmake_minimum_required(VERSION 3.10)
project(numeric-benchmark)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

option(BUILD_NANOBENCH "build nanobench benchmark programs" ON)
option(BUILD_GOOGLE_BENCHMARK "build google benchmark programs" ON)

if(BUILD_NANOBENCH)
    add_subdirectory(nanobench)
endif()
if(BUILD_GOOGLE_BENCHMARK)
    add_subdirectory(benchmark)
endif()