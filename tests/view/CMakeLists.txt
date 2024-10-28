cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-view)

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

option(NMTOOLS_VIEW_TEST_ALL             "test all view modules" ON)
option(NMTOOLS_VIEW_TEST_ARRAY_VIEW      "test array view modules"       OFF)
option(NMTOOLS_VIEW_TEST_ARRAY_UFUNCS    "test array ufuncs modules"     OFF)
option(NMTOOLS_VIEW_TEST_ARRAY_VIEW_NN   "test array nn view modules"    OFF)
option(NMTOOLS_VIEW_TEST_COMPOSITION     "test array view composition"   OFF)
option(NMTOOLS_VIEW_TEST_CONV            "test array view conv"          OFF)

if (NMTOOLS_VIEW_TEST_ALL)
    SET(NMTOOLS_VIEW_TEST_ARRAY_VIEW      ON CACHE BOOL "test array view modules"       FORCE)
    SET(NMTOOLS_VIEW_TEST_ARRAY_UFUNCS    ON CACHE BOOL "test array ufuncs modules"     FORCE)
    SET(NMTOOLS_VIEW_TEST_ARRAY_VIEW_NN   ON CACHE BOOL "test array nn view modules"    FORCE)
    SET(NMTOOLS_VIEW_TEST_COMPOSITION     ON CACHE BOOL "test array view composition"   FORCE)
    SET(NMTOOLS_VIEW_TEST_CONV            ON CACHE BOOL "test array view conv"          FORCE)
endif (NMTOOLS_VIEW_TEST_ALL)

set(ARRAY_VIEW_1_TEST_SOURCES
    src/alias.cpp
    src/arange.cpp
    src/argsort.cpp
    ## TODO: fix
    # src/array_slice.cpp
    src/atleast_1d.cpp
    src/atleast_2d.cpp
    src/atleast_nd.cpp
    src/broadcast_to.cpp
    src/broadcast_arrays.cpp
    src/column_stack.cpp
    src/concatenate.cpp
    src/compress.cpp
    src/diagflat.cpp
    src/diagonal.cpp
    src/dstack.cpp
    src/expand_dims.cpp
    src/expand.cpp
    src/eye.cpp
    src/flatten.cpp
    src/flip.cpp
    src/full.cpp
    src/full_like.cpp
    src/hstack.cpp
    src/identity.cpp
    src/linspace.cpp
    # split matmul to avoid high peak memory
    # src/matmul.cpp
    src/mean.cpp
    src/moveaxis.cpp
    src/mutable_flatten.cpp
    src/mutable_ref.cpp
    src/mutable_reshape.cpp
    src/mutable_slice.cpp
)
set(ARRAY_VIEW_2_TEST_SOURCES
    src/ones.cpp
    src/ones_like.cpp
    src/pad.cpp
    src/pooling.cpp
    src/ref.cpp
    src/ref/initializer_list.cpp
    src/repeat.cpp
    src/reshape.cpp
    src/resize.cpp
    src/roll.cpp
    src/slice.cpp
    src/split.cpp
    src/squeeze.cpp
    src/stack.cpp
    src/stddev.cpp
    src/swapaxes.cpp
    src/take_along_axis.cpp
    src/take.cpp
    src/tile.cpp
    src/trace.cpp
    src/transpose.cpp
    src/tri.cpp
    src/tril.cpp
    src/triu.cpp
    src/var.cpp
    src/vstack.cpp
    src/where.cpp
    src/zeros.cpp
    src/zeros_like.cpp
    src/sliding_window.cpp
)
set (ARRAY_MATMUL_1_TEST_SOURCES
    src/matmul-1.cpp
)
set (ARRAY_MATMUL_2_TEST_SOURCES
    src/matmul-2.cpp
)
set (ARRAY_MATMUL_3_TEST_SOURCES
    src/matmul-3.cpp
)
if (NOT NMTOOLS_VIEW_TEST_ARRAY_VIEW)
    set (ARRAY_VIEW_1_TEST_SOURCES "")
    set (ARRAY_VIEW_2_TEST_SOURCES "")
    set (ARRAY_MATMUL_1_TEST_SOURCES "")
    set (ARRAY_MATMUL_2_TEST_SOURCES "")
    set (ARRAY_MATMUL_3_TEST_SOURCES "")
endif ()

## TODO: rename to math
set(ARRAY_UFUNCS_1_TEST_SOURCES
    src/cumprod.cpp
    src/cumsum.cpp
    src/dot.cpp
    src/inner.cpp
    src/kron.cpp
    src/outer.cpp
    src/prod.cpp
    src/sum.cpp
    src/tensordot.cpp
    src/vecdot.cpp
    src/vector_norm.cpp
    src/ufuncs/add.cpp
    src/ufuncs/amax.cpp
    src/ufuncs/amin.cpp
    src/ufuncs/arccos.cpp
    src/ufuncs/arccosh.cpp
    src/ufuncs/arcsin.cpp
    src/ufuncs/arcsinh.cpp
    src/ufuncs/arctan.cpp
    src/ufuncs/arctanh.cpp
    src/ufuncs/arctan2.cpp
    src/ufuncs/bitwise_and.cpp
    src/ufuncs/bitwise_or.cpp
    src/ufuncs/bitwise_xor.cpp
    src/ufuncs/cbrt.cpp
    src/ufuncs/ceil.cpp
    src/ufuncs/degrees.cpp
    src/ufuncs/deg2rad.cpp
    ## TODO: fix
    # src/ufuncs/clip.cpp
    src/ufuncs/cos.cpp
    src/ufuncs/cosh.cpp
    src/ufuncs/divide.cpp
    src/ufuncs/equal.cpp
    src/ufuncs/exp.cpp
    src/ufuncs/exp2.cpp
    src/ufuncs/expm1.cpp
    src/ufuncs/fabs.cpp
    src/ufuncs/floor.cpp
    src/ufuncs/fmax.cpp
    src/ufuncs/fmin.cpp
    src/ufuncs/fmod.cpp
    src/ufuncs/greater.cpp
    src/ufuncs/greater_equal.cpp
    src/ufuncs/hypot.cpp
    src/ufuncs/invert.cpp
    src/ufuncs/isfinite.cpp
    src/ufuncs/isinf.cpp
    src/ufuncs/isnan.cpp
)

set(ARRAY_UFUNCS_2_TEST_SOURCES
    src/ufuncs/ldexp.cpp
    src/ufuncs/left_shift.cpp
    src/ufuncs/less.cpp
    src/ufuncs/less_equal.cpp
    src/ufuncs/log.cpp
    src/ufuncs/log1p.cpp
    src/ufuncs/log2.cpp
    src/ufuncs/log10.cpp
    src/ufuncs/logical_and.cpp
    src/ufuncs/logical_not.cpp
    src/ufuncs/logical_or.cpp
    src/ufuncs/logical_xor.cpp
    src/ufuncs/maximum.cpp
    src/ufuncs/minimum.cpp
    src/ufuncs/multiply.cpp
    src/ufuncs/negative.cpp
    src/ufuncs/not_equal.cpp
    src/ufuncs/positive.cpp
    src/ufuncs/power.cpp
    src/ufuncs/radians.cpp
    src/ufuncs/rad2deg.cpp
    src/ufuncs/reciprocal.cpp
    src/ufuncs/right_shift.cpp
    src/ufuncs/rint.cpp
    src/ufuncs/signbit.cpp
    src/ufuncs/sin.cpp
    src/ufuncs/sinh.cpp
    src/ufuncs/sqrt.cpp
    src/ufuncs/square.cpp
    src/ufuncs/subtract.cpp
    src/ufuncs/tan.cpp
    src/ufuncs/tanh.cpp
    src/ufuncs/trunc.cpp
)
if (NOT NMTOOLS_VIEW_TEST_ARRAY_UFUNCS)
    set (ARRAY_UFUNCS_1_TEST_SOURCES "")
    set (ARRAY_UFUNCS_2_TEST_SOURCES "")
endif ()

set(COMPOSITION_TEST_SOURCES
    src/composition/mean_subtract.cpp
    src/composition/subtract_fabs_square.cpp
    src/composition/square_sum_divide.cpp
)
if (NOT NMTOOLS_VIEW_TEST_COMPOSITION)
    set(COMPOSITION_TEST_SOURCES "")
endif ()

set(VIEW_NN_TEST_SOURCES
    src/activations/celu.cpp
    src/activations/elu.cpp
    src/activations/hardshrink.cpp
    src/activations/hardswish.cpp
    src/activations/hardtanh.cpp
    src/activations/leaky_relu.cpp
    src/activations/log_sigmoid.cpp
    src/activations/mish.cpp
    src/activations/prelu.cpp
    src/activations/relu.cpp
    src/activations/relu6.cpp
    src/activations/selu.cpp
    src/activations/silu.cpp
    src/activations/sigmoid.cpp
    src/activations/softplus.cpp
    src/activations/softshrink.cpp
    src/activations/softsign.cpp
    src/activations/tanhshrink.cpp
    src/batch_norm.cpp
    src/group_norm.cpp
    src/instance_norm.cpp
    src/layer_norm.cpp
    src/softmax.cpp
    src/softmin.cpp
)

set(VIEW_CONV_TEST_SOURCES
    src/conv1d-1.cpp
    src/conv1d-2.cpp
    src/conv1d-3.cpp
    src/conv1d-4.cpp
    src/conv1d-5.cpp
    src/conv1d-6.cpp
    src/conv1d-7.cpp
    src/conv1d-8.cpp
    src/conv1d-9.cpp
    src/conv1d-10.cpp
    src/conv1d-11.cpp
    src/conv1d-12.cpp
    src/conv1d-13.cpp
    src/conv1d-14.cpp
    src/conv1d-15.cpp
    src/conv1d-16.cpp
    src/conv1d-17.cpp
    src/conv1d-18.cpp
    src/conv2d-1.cpp
    src/conv2d-2.cpp
    src/conv2d-3.cpp
    src/conv2d-4.cpp
    src/conv2d-5.cpp
    src/conv2d-6.cpp
    src/conv2d-7.cpp
    src/conv2d-8.cpp
    src/conv2d-9.cpp
    src/conv2d-10.cpp
    src/conv2d-11.cpp
    src/conv2d-12.cpp
    src/conv2d-13.cpp
    src/conv2d-14.cpp
)

if (NOT NMTOOLS_VIEW_TEST_ARRAY_VIEW_NN)
    set (VIEW_NN_TEST_SOURCES "")
endif ()

if (NOT NMTOOLS_VIEW_TEST_CONV)
    set (VIEW_CONV_TEST_SOURCES "")
endif ()

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## split matmul to avoid high memory peak
    ${ARRAY_MATMUL_1_TEST_SOURCES}
    ## view part 1
    ${ARRAY_VIEW_1_TEST_SOURCES}
    ## split matmul to avoid high memory peak
    ${ARRAY_MATMUL_2_TEST_SOURCES}
    ## view part 2
    ${ARRAY_VIEW_2_TEST_SOURCES}
    ## ufuncs
    ${ARRAY_UFUNCS_1_TEST_SOURCES}
    ## split matmul to avoid high memory peak
    ${ARRAY_MATMUL_3_TEST_SOURCES}
    ## ufuncs part 2
    ${ARRAY_UFUNCS_2_TEST_SOURCES}
    ## array view nn
    ${VIEW_NN_TEST_SOURCES}
    ## view composition
    ${COMPOSITION_TEST_SOURCES}
    ## view conv tests
    ${VIEW_CONV_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
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
    target_link_libraries(numeric-tests-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)