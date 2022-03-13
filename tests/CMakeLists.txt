cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests)
# note cxx_std_20 for target_compile_features doesnt seem to work properly on 3.10.2

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
option(NMTOOLS_TEST_ARRAY_INDEX     "test array index modules"      OFF)
option(NMTOOLS_TEST_ARRAY_UTILITY   "test array utility modules"    OFF)
option(NMTOOLS_TEST_UTILS           "test utils modules"            OFF)
option(NMTOOLS_TEST_NDARRAY         "test ndarray modules"          OFF)
option(NMTOOLS_TEST_ARRAY_VIEW      "test array view modules"       OFF)
option(NMTOOLS_TEST_ARRAY_UFUNCS    "test array ufuncs modules"     OFF)
option(NMTOOLS_TEST_ARRAY_EVAL      "test array evaluation"         OFF)
option(NMTOOLS_TEST_ARRAY_VIEW_NN   "test array nn view modules"    OFF)
option(NMTOOLS_TEST_ARRAY_NN_EVAL   "test array nn eval modules"    OFF)
option(NMTOOLS_TEST_COMPOSITION     "test array view composition"   OFF)
option(NMTOOLS_TEST_EXCEPTION       "test exception error handling" OFF)
option(NMTOOLS_TEST_OPTIONAL        "test optional error handling"  OFF)
option(NMTOOLS_TEST_MISC            "test other modules"            OFF)

if (NMTOOLS_TEST_ALL)
    SET(NMTOOLS_TEST_ARRAY_INDEX     ON CACHE BOOL "test array index modules"      FORCE)
    SET(NMTOOLS_TEST_ARRAY_UTILITY   ON CACHE BOOL "test array utility modules"    FORCE)
    SET(NMTOOLS_TEST_UTILS           ON CACHE BOOL "test utils modules"            FORCE)
    SET(NMTOOLS_TEST_NDARRAY         ON CACHE BOOL "test ndarray modules"          FORCE)
    SET(NMTOOLS_TEST_ARRAY_VIEW      ON CACHE BOOL "test array view modules"       FORCE)
    SET(NMTOOLS_TEST_ARRAY_UFUNCS    ON CACHE BOOL "test array ufuncs modules"     FORCE)
    SET(NMTOOLS_TEST_ARRAY_EVAL      ON CACHE BOOL "test array evaluation"         FORCE)
    SET(NMTOOLS_TEST_ARRAY_VIEW_NN   ON CACHE BOOL "test array nn view modules"    FORCE)
    SET(NMTOOLS_TEST_ARRAY_NN_EVAL   ON CACHE BOOL "test array nn eval modules"    FORCE)
    SET(NMTOOLS_TEST_COMPOSITION     ON CACHE BOOL "test array view composition"   FORCE)
    SET(NMTOOLS_TEST_EXCEPTION       ON CACHE BOOL "test exception error handling" FORCE)
    SET(NMTOOLS_TEST_OPTIONAL        ON CACHE BOOL "test optional error handling"  FORCE)
    SET(NMTOOLS_TEST_MISC            ON CACHE BOOL "test other modules"            FORCE)
endif (NMTOOLS_TEST_ALL)

set(ARRAY_INDEX_TEST_SOURCES
    src/doctest/array/index/argsort.cpp
    src/doctest/array/index/array_slice.cpp
    src/doctest/array/index/broadcast_shape.cpp
    src/doctest/array/index/broadcast_to.cpp
    src/doctest/array/index/choose.cpp
    src/doctest/array/index/compress.cpp
    src/doctest/array/index/compute_indices.cpp
    src/doctest/array/index/compute_offset.cpp
    src/doctest/array/index/compute_strides.cpp
    src/doctest/array/index/concatenate.cpp
    src/doctest/array/index/conv.cpp
    src/doctest/array/index/expand_dims.cpp
    src/doctest/array/index/filter.cpp
    src/doctest/array/index/free_axes.cpp
    src/doctest/array/index/gather.cpp
    src/doctest/array/index/insert_index.cpp
    src/doctest/array/index/logical_not.cpp
    src/doctest/array/index/ndenumerate.cpp
    src/doctest/array/index/ndindex.cpp
    src/doctest/array/index/nonzero.cpp
    src/doctest/array/index/normalize_axis.cpp
    src/doctest/array/index/outer.cpp
    src/doctest/array/index/pooling.cpp
    src/doctest/array/index/remove_dims.cpp
    src/doctest/array/index/remove_single_dims.cpp
    src/doctest/array/index/repeat.cpp
    src/doctest/array/index/reverse.cpp
    src/doctest/array/index/scatter.cpp
    src/doctest/array/index/shape_concatenate.cpp
    src/doctest/array/index/shape_repeat.cpp
    src/doctest/array/index/shape_tile.cpp
    src/doctest/array/index/slice.cpp
    src/doctest/array/index/take.cpp
    src/doctest/array/index/take_along_axis.cpp
    src/doctest/array/index/tile.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_INDEX)
    set(ARRAY_INDEX_TEST_SOURCES "")
endif ()

set(UTILS_TEST_SOURCES
    src/doctest/array/utils/isequal.cpp
    src/doctest/array/utils/isclose.cpp
    src/doctest/array/utils/to_string.cpp
)
if (NOT NMTOOLS_TEST_UTILS)
    set(UTILS_TEST_SOURCES "")
endif ()

set(ARRAY_UTILITY_TEST_SOURCES
    src/doctest/array/utility/at.cpp
    src/doctest/array/utility/apply_at.cpp
    src/doctest/array/utility/cast.cpp
    src/doctest/array/utility/flatten_either.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_UTILITY)
    set (ARRAY_UTILITY_TEST_SOURCES "")
endif ()

set(NDARRAY_TEST_SOURCES
    src/doctest/array/fixed/ndarray.cpp
    src/doctest/array/hybrid/ndarray.cpp
    src/doctest/array/dynamic/ndarray.cpp
)
if (NOT NMTOOLS_TEST_NDARRAY)
    set(NDARRAY_TEST_SOURCES "")
endif ()

set(ARRAY_VIEW_TEST_SOURCES
    src/doctest/array/view/arange.cpp
    src/doctest/array/view/argsort.cpp
    src/doctest/array/view/array_slice.cpp
    src/doctest/array/view/atleast_1d.cpp
    src/doctest/array/view/atleast_2d.cpp
    src/doctest/array/view/atleast_3d.cpp
    src/doctest/array/view/broadcast_to.cpp
    src/doctest/array/view/broadcast_arrays.cpp
    src/doctest/array/view/concatenate.cpp
    src/doctest/array/view/compress.cpp
    src/doctest/array/view/expand_dims.cpp
    src/doctest/array/view/flatten.cpp
    src/doctest/array/view/flip.cpp
    src/doctest/array/view/full.cpp
    src/doctest/array/view/matmul.cpp
    src/doctest/array/view/mean.cpp
    src/doctest/array/view/moveaxis.cpp
    src/doctest/array/view/mutable_flatten.cpp
    src/doctest/array/view/mutable_ref.cpp
    src/doctest/array/view/mutable_slice.cpp
    src/doctest/array/view/ones.cpp
    src/doctest/array/view/pad.cpp
    src/doctest/array/view/pooling.cpp
    src/doctest/array/view/ref.cpp
    src/doctest/array/view/ref/initializer_list.cpp
    src/doctest/array/view/repeat.cpp
    src/doctest/array/view/reshape.cpp
    src/doctest/array/view/slice.cpp
    src/doctest/array/view/split.cpp
    src/doctest/array/view/squeeze.cpp
    src/doctest/array/view/stddev.cpp
    src/doctest/array/view/take_along_axis.cpp
    src/doctest/array/view/take.cpp
    src/doctest/array/view/tile.cpp
    src/doctest/array/view/transpose.cpp
    src/doctest/array/view/ufunc.cpp
    src/doctest/array/view/var.cpp
    src/doctest/array/view/where.cpp
    src/doctest/array/view/zeros.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_VIEW)
    set (ARRAY_VIEW_TEST_SOURCES "")
endif ()

set(EXCEPTION_TEST_SOURCES
    # exception tests
    src/doctest/error/array/view/broadcast_arrays_exception.cpp
    src/doctest/error/array/view/broadcast_to_exception.cpp
)
if (NOT NMTOOLS_TEST_EXCEPTION)
    set (EXCEPTION_TEST_SOURCES "")
endif ()

set(OPTIONAL_TEST_SOURCES
    src/doctest/error/array/view/broadcast_arrays_optional.cpp
    src/doctest/error/array/view/broadcast_to_optional.cpp
)
if (NOT NMTOOLS_TEST_OPTIONAL)
    set (OPTIONAL_TEST_SOURCES "")
endif ()


set(ARRAY_UFUNCS_TEST_SOURCES
    src/doctest/array/view/cumprod.cpp
    src/doctest/array/view/cumsum.cpp
    src/doctest/array/view/prod.cpp
    src/doctest/array/view/sum.cpp
    src/doctest/array/view/ufuncs/add.cpp
    src/doctest/array/view/ufuncs/amax.cpp
    src/doctest/array/view/ufuncs/amin.cpp
    src/doctest/array/view/ufuncs/arccos.cpp
    src/doctest/array/view/ufuncs/arccosh.cpp
    src/doctest/array/view/ufuncs/arcsin.cpp
    src/doctest/array/view/ufuncs/arcsinh.cpp
    src/doctest/array/view/ufuncs/arctan.cpp
    src/doctest/array/view/ufuncs/arctanh.cpp
    src/doctest/array/view/ufuncs/arctan2.cpp
    src/doctest/array/view/ufuncs/bitwise_and.cpp
    src/doctest/array/view/ufuncs/bitwise_or.cpp
    src/doctest/array/view/ufuncs/bitwise_xor.cpp
    src/doctest/array/view/ufuncs/cbrt.cpp
    src/doctest/array/view/ufuncs/ceil.cpp
    src/doctest/array/view/ufuncs/clip.cpp
    src/doctest/array/view/ufuncs/cos.cpp
    src/doctest/array/view/ufuncs/cosh.cpp
    src/doctest/array/view/ufuncs/divide.cpp
    src/doctest/array/view/ufuncs/equal.cpp
    src/doctest/array/view/ufuncs/exp.cpp
    src/doctest/array/view/ufuncs/exp2.cpp
    src/doctest/array/view/ufuncs/expm1.cpp
    src/doctest/array/view/ufuncs/fabs.cpp
    src/doctest/array/view/ufuncs/floor.cpp
    src/doctest/array/view/ufuncs/fmax.cpp
    src/doctest/array/view/ufuncs/fmin.cpp
    src/doctest/array/view/ufuncs/fmod.cpp
    src/doctest/array/view/ufuncs/greater.cpp
    src/doctest/array/view/ufuncs/greater_equal.cpp
    src/doctest/array/view/ufuncs/hypot.cpp
    src/doctest/array/view/ufuncs/invert.cpp
    src/doctest/array/view/ufuncs/isfinite.cpp
    src/doctest/array/view/ufuncs/isinf.cpp
    src/doctest/array/view/ufuncs/isnan.cpp
    src/doctest/array/view/ufuncs/ldexp.cpp
    src/doctest/array/view/ufuncs/left_shift.cpp
    src/doctest/array/view/ufuncs/less.cpp
    src/doctest/array/view/ufuncs/less_equal.cpp
    src/doctest/array/view/ufuncs/log.cpp
    src/doctest/array/view/ufuncs/log1p.cpp
    src/doctest/array/view/ufuncs/log2.cpp
    src/doctest/array/view/ufuncs/log10.cpp
    src/doctest/array/view/ufuncs/logical_and.cpp
    src/doctest/array/view/ufuncs/logical_not.cpp
    src/doctest/array/view/ufuncs/logical_or.cpp
    src/doctest/array/view/ufuncs/logical_xor.cpp
    src/doctest/array/view/ufuncs/maximum.cpp
    src/doctest/array/view/ufuncs/minimum.cpp
    src/doctest/array/view/ufuncs/multiply.cpp
    src/doctest/array/view/ufuncs/negative.cpp
    src/doctest/array/view/ufuncs/not_equal.cpp
    src/doctest/array/view/ufuncs/positive.cpp
    src/doctest/array/view/ufuncs/power.cpp
    src/doctest/array/view/ufuncs/reciprocal.cpp
    src/doctest/array/view/ufuncs/right_shift.cpp
    src/doctest/array/view/ufuncs/rint.cpp
    src/doctest/array/view/ufuncs/signbit.cpp
    src/doctest/array/view/ufuncs/sin.cpp
    src/doctest/array/view/ufuncs/sinh.cpp
    src/doctest/array/view/ufuncs/sqrt.cpp
    src/doctest/array/view/ufuncs/square.cpp
    src/doctest/array/view/ufuncs/subtract.cpp
    src/doctest/array/view/ufuncs/tan.cpp
    src/doctest/array/view/ufuncs/tanh.cpp
    src/doctest/array/view/ufuncs/trunc.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_UFUNCS)
    set (ARRAY_UFUNCS_TEST_SOURCES "")
endif ()

set(COMPOSITION_TEST_SOURCES
    src/doctest/array/composition/mean_subtract.cpp
    src/doctest/array/composition/subtract_fabs_square.cpp
    src/doctest/array/composition/square_sum_divide.cpp
)
if (NOT NMTOOLS_TEST_COMPOSITION)
    set(COMPOSITION_TEST_SOURCES "")
endif ()

set(ARRAY_EVAL_TEST_SOURCES
    src/doctest/array/array/arange.cpp
    src/doctest/array/array/atleast_1d.cpp
    src/doctest/array/array/atleast_2d.cpp
    src/doctest/array/array/atleast_3d.cpp
    src/doctest/array/array/broadcast_to.cpp
    src/doctest/array/array/compress.cpp
    src/doctest/array/array/concatenate.cpp
    src/doctest/array/array/cumprod.cpp
    src/doctest/array/array/cumsum.cpp
    src/doctest/array/array/expand_dims.cpp
    src/doctest/array/array/flatten.cpp
    src/doctest/array/array/flip.cpp
    src/doctest/array/array/full.cpp
    src/doctest/array/array/matmul.cpp
    src/doctest/array/array/mean.cpp
    src/doctest/array/array/moveaxis.cpp
    src/doctest/array/array/ones.cpp
    src/doctest/array/array/pad.cpp
    src/doctest/array/array/prod.cpp
    src/doctest/array/array/pooling.cpp
    src/doctest/array/array/repeat.cpp
    src/doctest/array/array/reshape.cpp
    src/doctest/array/array/slice.cpp
    src/doctest/array/array/squeeze.cpp
    src/doctest/array/array/stddev.cpp
    src/doctest/array/array/sum.cpp
    src/doctest/array/array/split.cpp
    src/doctest/array/array/take.cpp
    src/doctest/array/array/tile.cpp
    src/doctest/array/array/transpose.cpp
    src/doctest/array/array/var.cpp
    src/doctest/array/array/where.cpp
    src/doctest/array/array/zeros.cpp
    src/doctest/array/array/ufuncs/add.cpp
    src/doctest/array/array/ufuncs/amax.cpp
    src/doctest/array/array/ufuncs/amin.cpp
    src/doctest/array/array/ufuncs/arccos.cpp
    src/doctest/array/array/ufuncs/arccosh.cpp
    src/doctest/array/array/ufuncs/arcsin.cpp
    src/doctest/array/array/ufuncs/arcsinh.cpp
    src/doctest/array/array/ufuncs/arctan.cpp
    src/doctest/array/array/ufuncs/arctan2.cpp
    src/doctest/array/array/ufuncs/arctanh.cpp
    src/doctest/array/array/ufuncs/bitwise_and.cpp
    src/doctest/array/array/ufuncs/bitwise_or.cpp
    src/doctest/array/array/ufuncs/bitwise_xor.cpp
    src/doctest/array/array/ufuncs/ceil.cpp
    src/doctest/array/array/ufuncs/clip.cpp
    src/doctest/array/array/ufuncs/cos.cpp
    src/doctest/array/array/ufuncs/cosh.cpp
    src/doctest/array/array/ufuncs/divide.cpp
    src/doctest/array/array/ufuncs/equal.cpp
    src/doctest/array/array/ufuncs/exp.cpp
    src/doctest/array/array/ufuncs/exp2.cpp
    src/doctest/array/array/ufuncs/expm1.cpp
    src/doctest/array/array/ufuncs/fabs.cpp
    src/doctest/array/array/ufuncs/floor.cpp
    src/doctest/array/array/ufuncs/fmax.cpp
    src/doctest/array/array/ufuncs/fmin.cpp
    src/doctest/array/array/ufuncs/fmod.cpp
    src/doctest/array/array/ufuncs/greater_equal.cpp
    src/doctest/array/array/ufuncs/greater.cpp
    src/doctest/array/array/ufuncs/hypot.cpp
    src/doctest/array/array/ufuncs/invert.cpp
    src/doctest/array/array/ufuncs/isfinite.cpp
    src/doctest/array/array/ufuncs/isinf.cpp
    src/doctest/array/array/ufuncs/isnan.cpp
    src/doctest/array/array/ufuncs/ldexp.cpp
    src/doctest/array/array/ufuncs/left_shift.cpp
    src/doctest/array/array/ufuncs/less_equal.cpp
    src/doctest/array/array/ufuncs/less.cpp
    src/doctest/array/array/ufuncs/log.cpp
    src/doctest/array/array/ufuncs/log1p.cpp
    src/doctest/array/array/ufuncs/log2.cpp
    src/doctest/array/array/ufuncs/log10.cpp
    src/doctest/array/array/ufuncs/logical_and.cpp
    src/doctest/array/array/ufuncs/logical_not.cpp
    src/doctest/array/array/ufuncs/logical_or.cpp
    src/doctest/array/array/ufuncs/logical_xor.cpp
    src/doctest/array/array/ufuncs/maximum.cpp
    src/doctest/array/array/ufuncs/minimum.cpp
    src/doctest/array/array/ufuncs/multiply.cpp
    src/doctest/array/array/ufuncs/negative.cpp
    src/doctest/array/array/ufuncs/not_equal.cpp
    src/doctest/array/array/ufuncs/positive.cpp
    src/doctest/array/array/ufuncs/power.cpp
    src/doctest/array/array/ufuncs/reciprocal.cpp
    src/doctest/array/array/ufuncs/right_shift.cpp
    src/doctest/array/array/ufuncs/rint.cpp
    src/doctest/array/array/ufuncs/signbit.cpp
    src/doctest/array/array/ufuncs/sin.cpp
    src/doctest/array/array/ufuncs/sinh.cpp
    src/doctest/array/array/ufuncs/sqrt.cpp
    src/doctest/array/array/ufuncs/square.cpp
    src/doctest/array/array/ufuncs/subtract.cpp
    src/doctest/array/array/ufuncs/tan.cpp
    src/doctest/array/array/ufuncs/tanh.cpp
    src/doctest/array/array/ufuncs/trunc.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_EVAL)
    set (ARRAY_EVAL_TEST_SOURCES "")
endif ()

set(VIEW_NN_TEST_SOURCES
    src/doctest/array/view/activations/celu.cpp
    src/doctest/array/view/activations/elu.cpp
    src/doctest/array/view/activations/hardshrink.cpp
    src/doctest/array/view/activations/hardswish.cpp
    src/doctest/array/view/activations/hardtanh.cpp
    src/doctest/array/view/activations/leaky_relu.cpp
    src/doctest/array/view/activations/log_sigmoid.cpp
    src/doctest/array/view/activations/mish.cpp
    src/doctest/array/view/activations/prelu.cpp
    src/doctest/array/view/activations/relu.cpp
    src/doctest/array/view/activations/relu6.cpp
    src/doctest/array/view/activations/selu.cpp
    src/doctest/array/view/activations/silu.cpp
    src/doctest/array/view/activations/sigmoid.cpp
    src/doctest/array/view/activations/softplus.cpp
    src/doctest/array/view/activations/softshrink.cpp
    src/doctest/array/view/activations/softsign.cpp
    src/doctest/array/view/activations/tanhshrink.cpp
    src/doctest/array/view/conv.cpp
    src/doctest/array/view/batch_norm.cpp
    src/doctest/array/view/softmax.cpp
    src/doctest/array/view/softmin.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_VIEW_NN)
    set (VIEW_NN_TEST_SOURCES "")
endif ()

set(EVAL_NN_TEST_SOURCES
    src/doctest/array/array/activations/celu.cpp
    src/doctest/array/array/activations/elu.cpp
    src/doctest/array/array/activations/hardshrink.cpp
    src/doctest/array/array/activations/hardswish.cpp
    src/doctest/array/array/activations/hardtanh.cpp
    src/doctest/array/array/activations/leaky_relu.cpp
    src/doctest/array/array/activations/log_sigmoid.cpp
    src/doctest/array/array/activations/mish.cpp
    src/doctest/array/array/activations/prelu.cpp
    src/doctest/array/array/activations/relu.cpp
    src/doctest/array/array/activations/relu6.cpp
    src/doctest/array/array/activations/selu.cpp
    src/doctest/array/array/activations/sigmoid.cpp
    src/doctest/array/array/activations/silu.cpp
    src/doctest/array/array/activations/softplus.cpp
    src/doctest/array/array/activations/softsign.cpp
    src/doctest/array/array/activations/softshrink.cpp
    src/doctest/array/array/activations/tanhshrink.cpp
    src/doctest/array/array/conv.cpp
    src/doctest/array/array/batch_norm.cpp
    src/doctest/array/array/softmax.cpp
    src/doctest/array/array/softmin.cpp
)
if (NOT NMTOOLS_TEST_ARRAY_NN_EVAL)
    set (EVAL_NN_TEST_SOURCES "")
endif ()

set(MISC_TEST_SOURCES
    src/doctest/array/misc/constants.cpp
)
if (NOT NMTOOLS_TEST_MISC)
    set (MISC_TEST_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest src/doctest/tests.cpp 
    ## array detail
    ${ARRAY_INDEX_TEST_SOURCES}
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
    ## misc
    ${MISC_TEST_SOURCES}
)

# Workaround for testing for error handling,
# the error handling can be using exception or optional via macro,
# but when testing for both exception and optional in the same executable,
# only one mechanism works
# for now, make executables for each handing mechanism
add_executable(${PROJECT_NAME}-doctest-exception src/doctest/tests.cpp
    ## exception handling
    ${EXCEPTION_TEST_SOURCES}
)
add_executable(${PROJECT_NAME}-doctest-optional src/doctest/tests.cpp
    ## optional
    ${OPTIONAL_TEST_SOURCES}
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

target_compile_features(${PROJECT_NAME}-doctest-exception PRIVATE cxx_std_17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest-exception PRIVATE doctest::doctest)
endif()

target_compile_features(${PROJECT_NAME}-doctest-optional PRIVATE cxx_std_17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest-optional PRIVATE doctest::doctest)
endif()

option(NMTOOLS_ENABLE_TEST_BENCHMARKS "build benchmark programs" OFF)
if (NMTOOLS_ENABLE_TEST_BENCHMARKS)
    add_definitions(-DNMTOOLS_TESTING_ENABLE_BENCHMARKS)
    add_library(nanobench src/nanobench.cpp)
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
# TODO: this may not be portable across compiler, detect compiler
target_compile_options(${PROJECT_NAME}-doctest PRIVATE
    -ftemplate-backtrace-limit=0
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest-exception
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest-exception PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest-optional
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest-optional PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(NMTOOLS_DEFER_STATIC_CHECK "defer static check to runtime for testing purpose" OFF)
if (NMTOOLS_DEFER_STATIC_CHECK)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()


option(NMTOOLS_ADDRESS_SANITIZER "build with -fsanitize=address" OFF)
message(STATUS "NMTOOLS_ADDRESS_SANITIZER ${ADDRESS_SANITIZER}")

# from https://gist.github.com/jlblancoc/44be9d4d466f0a973b1f3808a8e56782
# TODO: findout if can be used for private target instead
# TODO: find out if can be used with other compiler
# TODO: provide option to disable/enable
if (NMTOOLS_ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
endif (NMTOOLS_ADDRESS_SANITIZER)

option(NMTOOLS_UNDEFINED_SANITIZER "build with -fsanitize=undefined" OFF)
message(STATUS "NMTOOLS_UNDEFINED_SANITIZER ${NMTOOLS_UNDEFINED_SANITIZER}")

if (NMTOOLS_UNDEFINED_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=undefined")
endif (NMTOOLS_UNDEFINED_SANITIZER)

option(NMTOOLS_CODE_COVERAGE "build with code coverage reporting" OFF)
message(STATUS "CODE_COVERAGE ${CODE_COVERAGE}")
if (NMTOOLS_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-doctest-coverage 
        EXECUTABLE ${PROJECT_NAME}-doctest
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "/usr/*"
    )
endif (NMTOOLS_CODE_COVERAGE)

# for emscripten, generate js main
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    message(" * C++ compiler: Emscripten")
    message(STATUS "Emscripten detected")
    option(JS_ONLY "build javascript only for emscripten" OFF)
    if(JS_ONLY)
        message(STATUS "Setting compilation target to native JavaScript")
        set(CMAKE_EXECUTABLE_SUFFIX ".js")
        set_target_properties(
            ${PROJECT_NAME}-doctest
            PROPERTIES LINK_FLAGS "--emrun -s EXPORTED_FUNCTIONS='[_main]'"
        )
    else(JS_ONLY)
        message(STATUS "Setting compilation target to WASM")
        set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
        set_target_properties(
            ${PROJECT_NAME}-doctest
            PROPERTIES LINK_FLAGS "--emrun -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
        )
    endif(JS_ONLY)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(NMTOOLS_BUILD_META_TESTS "build metafunctions test programs" ON)
if (NMTOOLS_BUILD_META_TESTS)
    add_subdirectory(src/meta)
endif (NMTOOLS_BUILD_META_TESTS)

option(NMTOOLS_BUILD_UTL_TESTS "build utl tests programs" ON)
if (NMTOOLS_BUILD_UTL_TESTS)
    add_subdirectory(src/utl/utl)
    add_subdirectory(src/utl/meta)
    add_subdirectory(src/utl/array)
endif (NMTOOLS_BUILD_UTL_TESTS)