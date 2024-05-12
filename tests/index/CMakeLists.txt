cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-index)

# TODO: cleanup
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

# TODO: cleanup
include(nmtools)

# TODO: cleanup
# handle emscripten
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    set (EMSCRIPTEN)
endif()
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set (ARM)
endif()

# optionally use boost (esp. for type_id)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

# TODO: remove, trye to detect constexpr math from stdlib
## defer static check to runtime for clang
## since constexpr math not supported
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR EMSCRIPTEN OR ANDROID OR MSYS)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

## disable benchmarks
add_definitions(-DNMTOOLS_TESTING_DOCTEST_DISABLE_BENCH)

option(NMTOOLS_INDEX_TEST_ALL "test all index modules" ON)

if (NMTOOLS_INDEX_TEST_ALL)
    set(ARRAY_INDEX_TEST_SOURCES
        src/argsort.cpp
        src/array_slice.cpp
        src/broadcast_shape.cpp
        src/broadcast_to.cpp
        src/choose.cpp
        src/compress.cpp
        src/compute_indices.cpp
        src/compute_offset.cpp
        src/compute_strides.cpp
        src/concatenate.cpp
        src/conv.cpp
        src/expand_dims.cpp
        src/filter.cpp
        src/free_axes.cpp
        src/gather.cpp
        src/insert_index.cpp
        src/logical_not.cpp
        src/matmul.cpp
        src/moveaxis.cpp
        src/ndenumerate.cpp
        src/ndindex.cpp
        src/nonzero.cpp
        src/normalize_axis.cpp
        src/outer.cpp
        src/pad.cpp
        src/pooling.cpp
        src/remove_dims.cpp
        src/remove_single_dims.cpp
        src/repeat.cpp
        src/reshape.cpp
        src/resize.cpp
        src/reverse.cpp
        src/scatter.cpp
        src/shape_concatenate.cpp
        src/shape_tile.cpp
        src/slice.cpp
        src/take.cpp
        src/take_along_axis.cpp
        src/tile.cpp
        src/sliding_window.cpp
    )
endif (NMTOOLS_INDEX_TEST_ALL)

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ${ARRAY_INDEX_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

option(NMTOOLS_ENABLE_TEST_BENCHMARKS "build benchmark programs" OFF)
if (NMTOOLS_ENABLE_TEST_BENCHMARKS)
    add_definitions(-DNMTOOLS_TESTING_ENABLE_BENCHMARKS)
    add_library(nanobench nanobench.cpp)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE nanobench)
endif()

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)