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
        src/ufuncs/clip.cpp
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
        src/broadcast_to.cpp
        src/conv.cpp
        src/compress.cpp
        src/concatenate.cpp
        src/cumprod.cpp
        src/cumsum.cpp
        src/expand_dims.cpp
        src/flatten.cpp
        src/flip.cpp
        src/reshape.cpp
        src/matmul.cpp
        src/mean.cpp
        src/moveaxis.cpp
        src/pad.cpp
        src/prod.cpp
        src/pooling.cpp
        src/repeat.cpp
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
        src/where.cpp
    )
endif()

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## functional
    ${FUNCTIONAL_TEST_SOURCES}
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