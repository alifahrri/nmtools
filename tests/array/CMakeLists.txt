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
option(NMTOOLS_TEST_ARRAY_VIEW      "test array view modules"       OFF)
option(NMTOOLS_TEST_ARRAY_UFUNCS    "test array ufuncs modules"     OFF)
option(NMTOOLS_TEST_ARRAY_EVAL      "test array evaluation"         OFF)
option(NMTOOLS_TEST_ARRAY_VIEW_NN   "test array nn view modules"    OFF)
option(NMTOOLS_TEST_ARRAY_NN_EVAL   "test array nn eval modules"    OFF)
option(NMTOOLS_TEST_COMPOSITION     "test array view composition"   OFF)
option(NMTOOLS_TEST_FUNCTIONAL      "test functional module"        OFF)
option(NMTOOLS_TEST_MISC            "test other modules"            OFF)

if (NMTOOLS_TEST_ALL)
    SET(NMTOOLS_TEST_ARRAY_UTILITY   ON CACHE BOOL "test array utility modules"    FORCE)
    SET(NMTOOLS_TEST_UTILS           ON CACHE BOOL "test utils modules"            FORCE)
    SET(NMTOOLS_TEST_NDARRAY         ON CACHE BOOL "test ndarray modules"          FORCE)
    SET(NMTOOLS_TEST_ARRAY_VIEW      ON CACHE BOOL "test array view modules"       FORCE)
    SET(NMTOOLS_TEST_ARRAY_UFUNCS    ON CACHE BOOL "test array ufuncs modules"     FORCE)
    SET(NMTOOLS_TEST_ARRAY_EVAL      ON CACHE BOOL "test array evaluation"         FORCE)
    SET(NMTOOLS_TEST_ARRAY_VIEW_NN   ON CACHE BOOL "test array nn view modules"    FORCE)
    SET(NMTOOLS_TEST_ARRAY_NN_EVAL   ON CACHE BOOL "test array nn eval modules"    FORCE)
    SET(NMTOOLS_TEST_COMPOSITION     ON CACHE BOOL "test array view composition"   FORCE)
    SET(NMTOOLS_TEST_FUNCTIONAL      ON CACHE BOOL "test functional module"        FORCE)
    SET(NMTOOLS_TEST_MISC            ON CACHE BOOL "test other modules"            FORCE)
endif (NMTOOLS_TEST_ALL)

set(UTILS_TEST_SOURCES
    utils/isequal.cpp
    utils/isclose.cpp
    utils/to_string.cpp
)
if (NOT NMTOOLS_TEST_UTILS)
    set(UTILS_TEST_SOURCES "")
endif ()

set(ARRAY_UTILITY_TEST_SOURCES
    utility/at.cpp
    utility/apply_at.cpp
    utility/cast.cpp
    utility/data.cpp
    utility/flatten_either.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_UTILITY)
    set (ARRAY_UTILITY_TEST_SOURCES "")
endif ()

set(NDARRAY_TEST_SOURCES
    ndarray/ndarray.cpp
    ndarray/fixed.cpp
    ndarray/dynamic.cpp
    ndarray/hybrid.cpp
)
if (NOT NMTOOLS_TEST_NDARRAY)
    set(NDARRAY_TEST_SOURCES "")
endif ()

set(ARRAY_VIEW_TEST_SOURCES
    view/arange.cpp
    view/argsort.cpp
    view/array_slice.cpp
    view/atleast_1d.cpp
    view/atleast_2d.cpp
    view/atleast_3d.cpp
    view/broadcast_to.cpp
    view/broadcast_arrays.cpp
    view/concatenate.cpp
    view/compress.cpp
    view/expand_dims.cpp
    view/flatten.cpp
    view/flip.cpp
    view/full.cpp
    view/matmul.cpp
    view/mean.cpp
    view/moveaxis.cpp
    view/mutable_flatten.cpp
    view/mutable_ref.cpp
    view/mutable_slice.cpp
    view/ones.cpp
    view/pad.cpp
    view/pooling.cpp
    view/ref.cpp
    view/ref/initializer_list.cpp
    view/repeat.cpp
    view/reshape.cpp
    view/resize.cpp
    view/slice.cpp
    view/split.cpp
    view/squeeze.cpp
    view/stddev.cpp
    view/take_along_axis.cpp
    view/take.cpp
    view/tile.cpp
    view/transpose.cpp
    view/ufunc.cpp
    view/var.cpp
    view/where.cpp
    view/zeros.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_VIEW)
    set (ARRAY_VIEW_TEST_SOURCES "")
endif ()

set(ARRAY_UFUNCS_TEST_SOURCES
    view/cumprod.cpp
    view/cumsum.cpp
    view/prod.cpp
    view/sum.cpp
    view/ufuncs/add.cpp
    view/ufuncs/amax.cpp
    view/ufuncs/amin.cpp
    view/ufuncs/arccos.cpp
    view/ufuncs/arccosh.cpp
    view/ufuncs/arcsin.cpp
    view/ufuncs/arcsinh.cpp
    view/ufuncs/arctan.cpp
    view/ufuncs/arctanh.cpp
    view/ufuncs/arctan2.cpp
    view/ufuncs/bitwise_and.cpp
    view/ufuncs/bitwise_or.cpp
    view/ufuncs/bitwise_xor.cpp
    view/ufuncs/cbrt.cpp
    view/ufuncs/ceil.cpp
    view/ufuncs/clip.cpp
    view/ufuncs/cos.cpp
    view/ufuncs/cosh.cpp
    view/ufuncs/divide.cpp
    view/ufuncs/equal.cpp
    view/ufuncs/exp.cpp
    view/ufuncs/exp2.cpp
    view/ufuncs/expm1.cpp
    view/ufuncs/fabs.cpp
    view/ufuncs/floor.cpp
    view/ufuncs/fmax.cpp
    view/ufuncs/fmin.cpp
    view/ufuncs/fmod.cpp
    view/ufuncs/greater.cpp
    view/ufuncs/greater_equal.cpp
    view/ufuncs/hypot.cpp
    view/ufuncs/invert.cpp
    view/ufuncs/isfinite.cpp
    view/ufuncs/isinf.cpp
    view/ufuncs/isnan.cpp
    view/ufuncs/ldexp.cpp
    view/ufuncs/left_shift.cpp
    view/ufuncs/less.cpp
    view/ufuncs/less_equal.cpp
    view/ufuncs/log.cpp
    view/ufuncs/log1p.cpp
    view/ufuncs/log2.cpp
    view/ufuncs/log10.cpp
    view/ufuncs/logical_and.cpp
    view/ufuncs/logical_not.cpp
    view/ufuncs/logical_or.cpp
    view/ufuncs/logical_xor.cpp
    view/ufuncs/maximum.cpp
    view/ufuncs/minimum.cpp
    view/ufuncs/multiply.cpp
    view/ufuncs/negative.cpp
    view/ufuncs/not_equal.cpp
    view/ufuncs/positive.cpp
    view/ufuncs/power.cpp
    view/ufuncs/reciprocal.cpp
    view/ufuncs/right_shift.cpp
    view/ufuncs/rint.cpp
    view/ufuncs/signbit.cpp
    view/ufuncs/sin.cpp
    view/ufuncs/sinh.cpp
    view/ufuncs/sqrt.cpp
    view/ufuncs/square.cpp
    view/ufuncs/subtract.cpp
    view/ufuncs/tan.cpp
    view/ufuncs/tanh.cpp
    view/ufuncs/trunc.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_UFUNCS)
    set (ARRAY_UFUNCS_TEST_SOURCES "")
endif ()

set(COMPOSITION_TEST_SOURCES
    composition/mean_subtract.cpp
    composition/subtract_fabs_square.cpp
    composition/square_sum_divide.cpp
)
if (NOT NMTOOLS_TEST_COMPOSITION)
    set(COMPOSITION_TEST_SOURCES "")
endif ()

set(ARRAY_EVAL_TEST_SOURCES
    array/arange.cpp
    array/atleast_1d.cpp
    array/atleast_2d.cpp
    array/atleast_3d.cpp
    array/broadcast_arrays.cpp
    array/broadcast_to.cpp
    array/compress.cpp
    array/concatenate.cpp
    array/cumprod.cpp
    array/cumsum.cpp
    array/expand_dims.cpp
    array/flatten.cpp
    array/flip.cpp
    array/full.cpp
    array/matmul.cpp
    array/mean.cpp
    array/moveaxis.cpp
    array/ones.cpp
    array/pad.cpp
    array/prod.cpp
    array/pooling.cpp
    array/repeat.cpp
    array/reshape.cpp
    # array/resize.cpp
    array/slice.cpp
    array/squeeze.cpp
    array/stddev.cpp
    array/sum.cpp
    array/split.cpp
    array/take.cpp
    array/tile.cpp
    array/transpose.cpp
    array/var.cpp
    array/where.cpp
    array/zeros.cpp
    array/ufuncs/add.cpp
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
    array/ufuncs/clip.cpp
    array/ufuncs/cos.cpp
    array/ufuncs/cosh.cpp
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
if (NOT NMTOOLS_TEST_ARRAY_EVAL)
    set (ARRAY_EVAL_TEST_SOURCES "")
endif ()

set(VIEW_NN_TEST_SOURCES
    view/activations/celu.cpp
    view/activations/elu.cpp
    view/activations/hardshrink.cpp
    view/activations/hardswish.cpp
    view/activations/hardtanh.cpp
    view/activations/leaky_relu.cpp
    view/activations/log_sigmoid.cpp
    view/activations/mish.cpp
    view/activations/prelu.cpp
    view/activations/relu.cpp
    view/activations/relu6.cpp
    view/activations/selu.cpp
    view/activations/silu.cpp
    view/activations/sigmoid.cpp
    view/activations/softplus.cpp
    view/activations/softshrink.cpp
    view/activations/softsign.cpp
    view/activations/tanhshrink.cpp
    view/conv.cpp
    view/conv-2.cpp
    view/conv-3.cpp
    view/conv-4.cpp
    view/batch_norm.cpp
    view/softmax.cpp
    view/softmin.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_VIEW_NN)
    set (VIEW_NN_TEST_SOURCES "")
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
    array/conv.cpp
    array/conv-2.cpp
    array/conv-3.cpp
    array/conv-4.cpp
    array/batch_norm.cpp
    array/softmax.cpp
    array/softmin.cpp
)
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

set(FUNCTIONAL_TEST_SOURCES
    functional/composition/add_add.cpp
    functional/composition/add_flatten.cpp
    functional/composition/flatten_add.cpp
    functional/activations/celu.cpp
    functional/activations/elu.cpp
    functional/activations/hardshrink.cpp
    functional/activations/hardswish.cpp
    functional/activations/hardtanh.cpp
    functional/activations/leaky_relu.cpp
    functional/activations/log_sigmoid.cpp
    functional/activations/mish.cpp
    functional/activations/prelu.cpp
    functional/activations/relu.cpp
    functional/activations/relu6.cpp
    functional/activations/selu.cpp
    functional/activations/sigmoid.cpp
    functional/activations/silu.cpp
    functional/activations/softplus.cpp
    functional/activations/softshrink.cpp
    functional/activations/softsign.cpp
    functional/activations/tanhshrink.cpp
    functional/ufuncs/add.cpp
    functional/ufuncs/arccos.cpp
    functional/ufuncs/arccosh.cpp
    functional/ufuncs/arcsin.cpp
    functional/ufuncs/arcsinh.cpp
    functional/ufuncs/arctan.cpp
    functional/ufuncs/arctanh.cpp
    functional/ufuncs/arctan2.cpp
    functional/ufuncs/cbrt.cpp
    functional/ufuncs/ceil.cpp
    functional/ufuncs/clip.cpp
    functional/ufuncs/cos.cpp
    functional/ufuncs/cosh.cpp
    functional/ufuncs/exp.cpp
    functional/ufuncs/exp2.cpp
    functional/ufuncs/expm1.cpp
    functional/ufuncs/fabs.cpp
    functional/ufuncs/floor.cpp
    functional/ufuncs/invert.cpp
    functional/ufuncs/isfinite.cpp
    functional/ufuncs/isinf.cpp
    functional/ufuncs/isnan.cpp
    functional/ufuncs/log.cpp
    functional/ufuncs/log1p.cpp
    functional/ufuncs/log2.cpp
    functional/ufuncs/log10.cpp
    functional/ufuncs/multiply.cpp
    functional/ufuncs/negative.cpp
    functional/ufuncs/positive.cpp
    functional/ufuncs/reciprocal.cpp
    functional/ufuncs/rint.cpp
    functional/ufuncs/signbit.cpp
    functional/ufuncs/sin.cpp
    functional/ufuncs/sinh.cpp
    functional/ufuncs/sqrt.cpp
    functional/ufuncs/tan.cpp
    functional/ufuncs/tanh.cpp
    functional/atleast_1d.cpp
    functional/atleast_2d.cpp
    functional/atleast_3d.cpp
    functional/broadcast_to.cpp
    functional/conv.cpp
    functional/compress.cpp
    functional/concatenate.cpp
    functional/cumprod.cpp
    functional/cumsum.cpp
    functional/expand_dims.cpp
    functional/flatten.cpp
    functional/flip.cpp
    functional/reshape.cpp
    functional/matmul.cpp
    functional/mean.cpp
    functional/moveaxis.cpp
    functional/pad.cpp
    functional/prod.cpp
    functional/pooling.cpp
    functional/repeat.cpp
    functional/slice.cpp
    functional/softmax.cpp
    functional/softmin.cpp
    functional/squeeze.cpp
    functional/stddev.cpp
    functional/sum.cpp
    functional/take.cpp
    functional/tile.cpp
    functional/transpose.cpp
    functional/var.cpp
    functional/where.cpp
)
if (NOT NMTOOLS_TEST_FUNCTIONAL)
    set (FUNCTIONAL_TEST_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## utility function
    ${UTILS_TEST_SOURCES}
    ## array utility
    ${ARRAY_UTILITY_TEST_SOURCES}
    ## ndarray
    ${NDARRAY_TEST_SOURCES}
    ## view
    ${ARRAY_VIEW_TEST_SOURCES}
    ## ufuncs
    ${ARRAY_UFUNCS_TEST_SOURCES}
    ## array evaluation
    ${ARRAY_EVAL_TEST_SOURCES}
    ## array view nn
    ${VIEW_NN_TEST_SOURCES}
    ## array eval nn
    ${EVAL_NN_TEST_SOURCES}
    ## view composition
    ${COMPOSITION_TEST_SOURCES}
    ## functional
    ${FUNCTIONAL_TEST_SOURCES}
    ## misc
    ${MISC_TEST_SOURCES}
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