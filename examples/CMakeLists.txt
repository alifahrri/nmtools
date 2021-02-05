cmake_minimum_required(VERSION 3.10)
project(numeric-examples)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

option(BUILD_EXAMPLES_ARRAY "build array example programs" ON)

if (BUILD_EXAMPLES_ARRAY)
    add_subdirectory(nmtools/array)
endif (BUILD_EXAMPLES_ARRAY)