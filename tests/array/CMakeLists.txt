cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

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

option(NMTOOLS_TEST_ALL             "test all modules"              ON)
option(NMTOOLS_TEST_ARRAY_UTILITY   "test array utility modules"    OFF)
option(NMTOOLS_TEST_UTILS           "test utils modules"            OFF)
option(NMTOOLS_TEST_NDARRAY         "test ndarray modules"          OFF)
option(NMTOOLS_TEST_ARRAY_UFUNCS    "test array ufuncs modules"     OFF)
option(NMTOOLS_TEST_ARRAY_EVAL      "test array evaluation"         OFF)
option(NMTOOLS_TEST_ARRAY_NN_EVAL   "test array nn eval modules"    OFF)
option(NMTOOLS_TEST_ARRAY_CONV_EVAL "test array conv eval modules"  OFF)
option(NMTOOLS_TEST_COMPOSITION     "test array view composition"   OFF)
option(NMTOOLS_TEST_MISC            "test other modules"            OFF)

if (NMTOOLS_TEST_ALL)
    SET(NMTOOLS_TEST_ARRAY_UTILITY   ON CACHE BOOL "test array utility modules"    FORCE)
    SET(NMTOOLS_TEST_UTILS           ON CACHE BOOL "test utils modules"            FORCE)
    SET(NMTOOLS_TEST_NDARRAY         ON CACHE BOOL "test ndarray modules"          FORCE)
    SET(NMTOOLS_TEST_ARRAY_UFUNCS    ON CACHE BOOL "test array ufuncs modules"     FORCE)
    SET(NMTOOLS_TEST_ARRAY_EVAL      ON CACHE BOOL "test array evaluation"         FORCE)
    SET(NMTOOLS_TEST_ARRAY_NN_EVAL   ON CACHE BOOL "test array nn eval modules"    FORCE)
    SET(NMTOOLS_TEST_ARRAY_CONV_EVAL ON CACHE BOOL "test array conv eval modules"  FORCE)
    SET(NMTOOLS_TEST_COMPOSITION     ON CACHE BOOL "test array view composition"   FORCE)
    SET(NMTOOLS_TEST_MISC            ON CACHE BOOL "test other modules"            FORCE)
endif (NMTOOLS_TEST_ALL)

set(NDARRAY_TEST_SOURCES
    ndarray/ndarray.cpp
    ndarray/fixed.cpp
    ndarray/dynamic.cpp
    ndarray/hybrid.cpp
)
if (NOT NMTOOLS_TEST_NDARRAY)
    set(NDARRAY_TEST_SOURCES "")
endif ()

set(ARRAY_EVAL_TEST_SOURCES
    array/arange.cpp
    array/atleast_1d.cpp
    array/atleast_2d.cpp
    array/atleast_nd.cpp
    # array/broadcast_arrays.cpp
    array/broadcast_to.cpp
    array/bilinear.cpp
    array/column_stack.cpp
    array/compress.cpp
    array/concatenate.cpp
    array/cosine_similarity.cpp
    array/cumprod.cpp
    array/cumsum.cpp
    array/diagflat.cpp
    array/diagonal.cpp
    array/dstack.cpp
    array/dot.cpp
    array/expand_dims.cpp
    array/expand.cpp
    array/eye.cpp
    array/flatten.cpp
    array/flip.cpp
    array/full.cpp
    array/full_like.cpp
    array/group_norm.cpp
    array/hstack.cpp
    array/identity.cpp
    array/inner.cpp
    # break matmul to multiple files to avoid high memory peak
    # array/matmul.cpp
    array/instance_norm.cpp
    array/kron.cpp
    array/linspace.cpp
    array/mean.cpp
    array/moveaxis.cpp
    array/ones.cpp
    array/ones_like.cpp
    array/outer.cpp
    array/layer_norm.cpp
    array/linear.cpp
    array/pad.cpp
    array/pairwise_distance.cpp
    array/prod.cpp
    array/pooling.cpp
    array/repeat.cpp
    array/reshape.cpp
    array/resize.cpp
    array/roll.cpp
    array/slice.cpp
    array/sliding_window.cpp
    array/squeeze.cpp
    array/stack.cpp
    array/stddev.cpp
    array/sum.cpp
    array/split.cpp
    array/swapaxes.cpp
    array/take.cpp
    array/tensordot.cpp
    array/tile.cpp
    array/trace.cpp
    array/tri.cpp
    array/tril.cpp
    array/triu.cpp
    array/transpose.cpp
    array/var.cpp
    array/vecdot.cpp
    array/vector_norm.cpp
    array/vstack.cpp
    array/where.cpp
    array/zeros.cpp
    array/zeros_like.cpp
)
set(ARRAY_UFUNCS_TEST_SOURCES
    # array/ufuncs/add.cpp
    array/ufuncs/amax.cpp
    array/ufuncs/amin.cpp
    array/ufuncs/arccos.cpp
    array/ufuncs/arccosh.cpp
    array/ufuncs/arcsin.cpp
    array/ufuncs/arcsinh.cpp
    array/ufuncs/arctan.cpp
    array/ufuncs/arctan2.cpp
    array/ufuncs/arctanh.cpp
    array/ufuncs/bitwise_and.cpp
    array/ufuncs/bitwise_or.cpp
    array/ufuncs/bitwise_xor.cpp
    array/ufuncs/ceil.cpp
    # TODO: this compiles forever, fix
    # array/ufuncs/clip.cpp
    array/ufuncs/cos.cpp
    array/ufuncs/cosh.cpp
    array/ufuncs/degrees.cpp
    array/ufuncs/deg2rad.cpp
    array/ufuncs/divide.cpp
    array/ufuncs/equal.cpp
    array/ufuncs/exp.cpp
    array/ufuncs/exp2.cpp
    array/ufuncs/expm1.cpp
    array/ufuncs/fabs.cpp
    array/ufuncs/floor.cpp
    array/ufuncs/fmax.cpp
    array/ufuncs/fmin.cpp
    array/ufuncs/fmod.cpp
    array/ufuncs/greater_equal.cpp
    array/ufuncs/greater.cpp
    array/ufuncs/hypot.cpp
    array/ufuncs/invert.cpp
    array/ufuncs/isfinite.cpp
    array/ufuncs/isinf.cpp
    array/ufuncs/isnan.cpp
    array/ufuncs/ldexp.cpp
    array/ufuncs/left_shift.cpp
    array/ufuncs/less_equal.cpp
    array/ufuncs/less.cpp
    array/ufuncs/log.cpp
    array/ufuncs/log1p.cpp
    array/ufuncs/log2.cpp
    array/ufuncs/log10.cpp
    array/ufuncs/logical_and.cpp
    array/ufuncs/logical_not.cpp
    array/ufuncs/logical_or.cpp
    array/ufuncs/logical_xor.cpp
    array/ufuncs/maximum.cpp
    array/ufuncs/minimum.cpp
    array/ufuncs/multiply.cpp
    array/ufuncs/negative.cpp
    array/ufuncs/not_equal.cpp
    array/ufuncs/positive.cpp
    array/ufuncs/power.cpp
    array/ufuncs/radians.cpp
    array/ufuncs/rad2deg.cpp
    array/ufuncs/reciprocal.cpp
    array/ufuncs/right_shift.cpp
    array/ufuncs/rint.cpp
    array/ufuncs/signbit.cpp
    array/ufuncs/sin.cpp
    array/ufuncs/sinh.cpp
    array/ufuncs/sqrt.cpp
    array/ufuncs/square.cpp
    array/ufuncs/subtract.cpp
    array/ufuncs/tan.cpp
    array/ufuncs/tanh.cpp
    array/ufuncs/trunc.cpp
)
set(ARRAY_MATMUL_1_TEST_SOURCES
    array/matmul-1.cpp
)
set(ARRAY_MATMUL_2_TEST_SOURCES
    array/matmul-2.cpp
)
set(ARRAY_MATMUL_3_TEST_SOURCES
    array/matmul-3.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_EVAL)
    set (ARRAY_EVAL_TEST_SOURCES "")
    set (ARRAY_MATMUL_1_TEST_SOURCES "")
    set (ARRAY_MATMUL_2_TEST_SOURCES "")
    set (ARRAY_MATMUL_3_TEST_SOURCES "")
endif ()

if (NOT NMTOOLS_TEST_ARRAY_UFUNCS)
    set (ARRAY_UFUNCS_TEST_SOURCES "")
endif ()

set(EVAL_NN_TEST_SOURCES
    array/activations/celu.cpp
    array/activations/elu.cpp
    array/activations/hardshrink.cpp
    array/activations/hardswish.cpp
    array/activations/hardtanh.cpp
    array/activations/leaky_relu.cpp
    array/activations/log_sigmoid.cpp
    array/activations/mish.cpp
    array/activations/prelu.cpp
    array/activations/relu.cpp
    array/activations/relu6.cpp
    array/activations/selu.cpp
    array/activations/sigmoid.cpp
    array/activations/silu.cpp
    array/activations/softplus.cpp
    array/activations/softsign.cpp
    array/activations/softshrink.cpp
    array/activations/tanhshrink.cpp
    array/batch_norm.cpp
    array/softmax.cpp
    array/softmin.cpp
)

set(EVAL_CONV_TEST_SOURCES
    array/conv1d-1.cpp
    array/conv1d-2.cpp
    array/conv1d-3.cpp
    array/conv1d-4.cpp
    array/conv1d-5.cpp
    array/conv1d-6.cpp
    array/conv1d-7.cpp
    array/conv1d-8.cpp
    array/conv1d-9.cpp
    array/conv1d-10.cpp
    array/conv1d-11.cpp
    array/conv1d-12.cpp
    array/conv1d-13.cpp
    array/conv1d-14.cpp
    array/conv1d-15.cpp
    array/conv1d-16.cpp
    array/conv1d-17.cpp
    array/conv1d-18.cpp
    array/conv2d-1.cpp
    array/conv2d-2.cpp
    array/conv2d-3.cpp
    array/conv2d-4.cpp
    array/conv2d-5.cpp
    array/conv2d-6.cpp
    array/conv2d-7.cpp
    array/conv2d-8.cpp
    array/conv2d-9.cpp
    array/conv2d-10.cpp
    array/conv2d-11.cpp
    array/conv2d-12.cpp
    array/conv2d-13.cpp
    array/conv2d-14.cpp
)

if (NOT NMTOOLS_TEST_ARRAY_CONV_EVAL)
    set (EVAL_CONV_TEST_SOURCES "")
endif ()

if (NOT NMTOOLS_TEST_ARRAY_NN_EVAL)
    set (EVAL_NN_TEST_SOURCES "")
endif ()

set(MISC_TEST_SOURCES
    misc/constants.cpp
    misc/clipped_integer.cpp
)
if (NOT NMTOOLS_TEST_MISC)
    set (MISC_TEST_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## split matmul srcs to reduce peak memory
    ${ARRAY_MATMUL_1_TEST_SOURCES}
    ## ndarray
    ${NDARRAY_TEST_SOURCES}
    ## split matmul srcs to reduce peak memory
    ${ARRAY_MATMUL_2_TEST_SOURCES}
    ## ufuncs
    ${ARRAY_UFUNCS_TEST_SOURCES}
    ## split matmul srcs to reduce peak memory
    ${ARRAY_MATMUL_3_TEST_SOURCES}
    ## array evaluation
    ${ARRAY_EVAL_TEST_SOURCES}
    ## array eval nn
    ${EVAL_NN_TEST_SOURCES}
    ## misc
    ${MISC_TEST_SOURCES}
    ## conv
    ${EVAL_CONV_TEST_SOURCES}
)

add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

option(NMTOOLS_ENABLE_TEST_BENCHMARKS "build benchmark programs" OFF)
if (NMTOOLS_ENABLE_TEST_BENCHMARKS)
    add_definitions(-DNMTOOLS_TESTING_ENABLE_BENCHMARKS)
    add_library(nanobench nanobench.cpp)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE nanobench)
endif()

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${NMTOOLS_INCLUDE_DIR}
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(numeric-tests-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)