cmake_minimum_required(VERSION 3.13)
project(numeric-tests-transform)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

## TODO: remove
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

option(NMTOOLS_TRANSFORM_TEST_ALL "test all transform modules" ON)

option(NMTOOLS_TRANSFORM_TEST_FUSION    "test all graph fusion modules"        OFF)
option(NMTOOLS_TRANSFORM_TEST_LINEARIZE "test all graph linearizer modules"    OFF)
option(NMTOOLS_TRANSFORM_TEST_APPLY     "test all graph apply modules"         OFF)

set(TRANSFORM_TEST_LINEARIZE_SOURCES
    src/linearize/avg_pool2d.cpp
    src/linearize/batch_norm.cpp
    src/linearize/conv2d.cpp
    src/linearize/group_norm.cpp
    src/linearize/instance_norm.cpp
    src/linearize/matmul.cpp
    src/linearize/softmax.cpp
    src/linearize/var.cpp
    src/linearize/layer_norm.cpp
    src/linearize/stddev.cpp
    src/linearize/cosine_similarity.cpp
    src/linearize/kron.cpp
    src/linearize/max_pool2d.cpp
    src/linearize/dot.cpp
    src/linearize/vector_norm.cpp
    src/linearize/vecdot.cpp
    src/linearize/trace.cpp
    src/linearize/tensordot.cpp
    src/linearize/pad.cpp
    src/linearize/pairwise_distance.cpp
    src/linearize/bilinear.cpp
    src/linearize/vstack.cpp
    src/linearize/mean.cpp
    src/linearize/tri.cpp
)

set(TRANSFORM_TEST_APPLY_SOURCES
    src/apply/avg_pool2d.cpp
    src/apply/batch_norm.cpp
    src/apply/conv2d.cpp
    src/apply/group_norm.cpp
    src/apply/instance_norm.cpp
    src/apply/matmul.cpp
    src/apply/softmax.cpp
    src/apply/var.cpp
    src/apply/layer_norm.cpp
    src/apply/max_pool2d.cpp
    src/apply/stddev.cpp
    src/apply/cosine_similarity.cpp
    src/apply/kron.cpp
    src/apply/dot.cpp
    src/apply/vector_norm.cpp
    src/apply/vecdot.cpp
    src/apply/trace.cpp
    src/apply/tensordot.cpp
    src/apply/pad.cpp
    src/apply/pairwise_distance.cpp
    src/apply/bilinear.cpp
    src/apply/vstack.cpp
)

set(TRANSFORM_TEST_FUSION_SOURCES
    src/unary_fusion.cpp
    src/binary_fusion.cpp
)

if (NMTOOLS_TRANSFORM_TEST_ALL)
    set(NMTOOLS_TRANSFORM_TEST_FUSION    ON CACHE BOOL "test graph fusion modules" FORCE)
    set(NMTOOLS_TRANSFORM_TEST_LINEARIZE ON CACHE BOOL "test graph linearizer modules" FORCE)
    set(NMTOOLS_TRANSFORM_TEST_APPLY     ON CACHE BOOL "test graph apply modules"      FORCE)
endif()

if(NOT ${NMTOOLS_TRANSFORM_TEST_LINEARIZE})
    set(TRANSFORM_TEST_LINEARIZE_SOURCES "")
endif()

if(NOT ${NMTOOLS_TRANSFORM_TEST_APPLY})
    set(TRANSFORM_TEST_APPLY_SOURCES "")
endif()

if (NOT ${NMTOOLS_TRANSFORM_TEST_FUSION})
    set(TRANSFORM_TEST_FUSION_SOURCES "")
endif()

set(TRANSFORM_TEST_SOURCES
    ${TRANSFORM_TEST_LINEARIZE_SOURCES}
    ${TRANSFORM_TEST_APPLY_SOURCES}
    ${TRANSFORM_TEST_FUSION_SOURCES}
)

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## functional
    ${TRANSFORM_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

## TODO: remove
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
target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    # NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)