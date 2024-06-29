cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-functional)

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

option(NMTOOLS_FUNCTIONAL_TEST_ALL "test all functional modules" ON)

if (NMTOOLS_FUNCTIONAL_TEST_ALL)
    set(FUNCTIONAL_TEST_SOURCES
        src/composition/add_add.cpp
        src/composition/add_flatten.cpp
        src/composition/flatten_add.cpp
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
        src/activations/sigmoid.cpp
        src/activations/silu.cpp
        src/activations/softplus.cpp
        src/activations/softshrink.cpp
        src/activations/softsign.cpp
        src/activations/tanhshrink.cpp
        src/ufuncs/add.cpp
        src/ufuncs/arccos.cpp
        src/ufuncs/arccosh.cpp
        src/ufuncs/arcsin.cpp
        src/ufuncs/arcsinh.cpp
        src/ufuncs/arctan.cpp
        src/ufuncs/arctanh.cpp
        src/ufuncs/arctan2.cpp
        src/ufuncs/cbrt.cpp
        src/ufuncs/ceil.cpp
        # TODO: this compiles forever, fix
        # src/ufuncs/clip.cpp
        src/ufuncs/cos.cpp
        src/ufuncs/cosh.cpp
        src/ufuncs/exp.cpp
        src/ufuncs/exp2.cpp
        src/ufuncs/expm1.cpp
        src/ufuncs/fabs.cpp
        src/ufuncs/floor.cpp
        src/ufuncs/invert.cpp
        src/ufuncs/isfinite.cpp
        src/ufuncs/isinf.cpp
        src/ufuncs/isnan.cpp
        src/ufuncs/log.cpp
        src/ufuncs/log1p.cpp
        src/ufuncs/log2.cpp
        src/ufuncs/log10.cpp
        src/ufuncs/multiply.cpp
        src/ufuncs/negative.cpp
        src/ufuncs/positive.cpp
        src/ufuncs/reciprocal.cpp
        src/ufuncs/rint.cpp
        src/ufuncs/signbit.cpp
        src/ufuncs/sin.cpp
        src/ufuncs/sinh.cpp
        src/ufuncs/sqrt.cpp
        src/ufuncs/tan.cpp
        src/ufuncs/tanh.cpp
        src/atleast_1d.cpp
        src/atleast_2d.cpp
        src/atleast_3d.cpp
        src/atleast_nd.cpp
        src/broadcast_to.cpp
        src/conv.cpp
        src/compress.cpp
        src/concatenate.cpp
        src/cumprod.cpp
        src/cumsum.cpp
        src/expand_dims.cpp
        src/flatten.cpp
        src/flip.cpp
        src/hstack.cpp
        src/reshape.cpp
        src/stack.cpp
        src/matmul.cpp
        src/mean.cpp
        src/moveaxis.cpp
        src/pad.cpp
        src/prod.cpp
        src/pooling.cpp
        src/repeat.cpp
        src/resize.cpp
        src/roll.cpp
        src/slice.cpp
        src/softmax.cpp
        src/softmin.cpp
        src/squeeze.cpp
        src/stddev.cpp
        src/sum.cpp
        src/take.cpp
        src/tile.cpp
        src/transpose.cpp
        src/var.cpp
        src/vstack.cpp
        src/where.cpp

        src/graph/transpose.cpp
        src/graph/reshape.cpp
        src/graph/batch_norm.cpp
        src/graph/broadcast_to.cpp
        src/graph/tanh.cpp
        src/graph/multiply.cpp
        src/graph/reduce_add_tanh.cpp
        src/graph/multiply_tanh.cpp
        src/graph/multiply_add_tanh.cpp
        src/graph/mean.cpp
        src/graph/var.cpp
        src/graph/stddev.cpp
        src/graph/softmax.cpp
        src/graph/softmin.cpp

        src/misc/ct_map.cpp
        src/misc/ct_digraph.cpp

        src/arange.cpp

        src/composition/reduce_add_tanh.cpp
        src/composition/multiply_tanh.cpp
        src/composition/multiply_add.cpp
        src/composition/multiply_add_tanh.cpp
        src/composition/add_tanh.cpp
        src/composition/reduce_add_divide.cpp
        src/composition/divide_subtract.cpp
        src/composition/subtract_fabs.cpp
        src/composition/subtract_fabs_square.cpp
        src/composition/fabs_square.cpp
        src/composition/fabs_square_sum.cpp
        src/composition/square_sum.cpp
        src/composition/square_sum_divide.cpp
        src/composition/sum_divide.cpp
        src/composition/reduce_maximum_subtract.cpp
        src/composition/reduce_maximum_subtract_exp.cpp
        src/composition/subtract_exp.cpp

        src/combinator/bury.cpp
        src/combinator/dig.cpp
        src/combinator/swap.cpp
        src/combinator/dup.cpp
    )
endif()

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## functional
    ${FUNCTIONAL_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

option( NMTOOLS_KWARGS_INIT "enable kwargs tests using designated initializers (c++20)" OFF)
if (NMTOOLS_KWARGS_INIT)
    target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_20)
    target_compile_definitions( ${PROJECT_NAME}-doctest PRIVATE NMTOOLS_TESTING_KWARGS_INIT )
else ()
    target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
endif ()
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
target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    # NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)