cmake_minimum_required(VERSION 3.10)
project(nmtools-array-example)

include_directories(
    ${NMTOOLS_INCLUDE_DIR}
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-frelaxed-template-template-args)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}-tile
    src/tile.cpp
)

add_executable(
    ${PROJECT_NAME}-repeat
    src/repeat.cpp
)

add_executable(
    ${PROJECT_NAME}-reshape
    src/reshape.cpp
)

add_executable(
    ${PROJECT_NAME}-transpose
    src/transpose.cpp
)

add_executable(
    ${PROJECT_NAME}-broadcast_to
    src/broadcast_to.cpp
)

add_executable(
    ${PROJECT_NAME}-expand_dims
    src/expand_dims.cpp
)

add_executable(
    ${PROJECT_NAME}-squeeze
    src/squeeze.cpp
)

add_executable(
    ${PROJECT_NAME}-flatten
    src/flatten.cpp
)