cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-cuda)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

# optionally use boost (esp. for type_id)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()
# enable_language(CUDA)

option(NMTOOLS_CUDA_TEST_ALL "test all cuda modules" ON)

set(NMTOOLS_CUDA_TEST_SOURCES "")

set(NMTOOLS_CUDA_TEST_SOURCES ${NMTOOLS_CUDA_TEST_SOURCES}
    array/activations/relu.cpp
    array/activations/relu6.cpp
    array/activations/celu.cpp
    array/activations/elu.cpp
    array/activations/hardshrink.cpp
    array/activations/hardswish.cpp
    array/activations/hardtanh.cpp
    array/activations/leaky_relu.cpp
    array/activations/log_sigmoid.cpp
    array/activations/mish.cpp
    array/activations/prelu.cpp
    array/activations/selu.cpp
    array/activations/sigmoid.cpp
    array/activations/silu.cpp
    array/activations/softplus.cpp
    array/activations/softshrink.cpp
    array/activations/softsign.cpp
    array/activations/tanhshrink.cpp

    array/ufuncs/arccos.cpp
    array/ufuncs/arccosh.cpp
    array/ufuncs/arcsin.cpp
    array/ufuncs/arcsinh.cpp
    array/ufuncs/arctan.cpp
    array/ufuncs/arctanh.cpp
    array/ufuncs/cbrt.cpp
    array/ufuncs/ceil.cpp
    array/ufuncs/cos.cpp
    array/ufuncs/cosh.cpp
    array/ufuncs/exp.cpp
    array/ufuncs/exp2.cpp
    array/ufuncs/expm1.cpp
    array/ufuncs/fabs.cpp
    array/ufuncs/floor.cpp
    array/ufuncs/invert.cpp
    array/ufuncs/isfinite.cpp
    array/ufuncs/isinf.cpp
    array/ufuncs/isnan.cpp
    array/ufuncs/log.cpp
    array/ufuncs/log2.cpp
    array/ufuncs/log1p.cpp
    array/ufuncs/log10.cpp
    array/ufuncs/negative.cpp
    array/ufuncs/positive.cpp
    array/ufuncs/reciprocal.cpp
    array/ufuncs/rint.cpp
    array/ufuncs/signbit.cpp
    array/ufuncs/sin.cpp
    array/ufuncs/sinh.cpp
    array/ufuncs/sqrt.cpp
    array/ufuncs/tan.cpp
    array/ufuncs/tanh.cpp

    array/ufuncs/add.cpp
    array/ufuncs/multiply.cpp

    array/reductions/add.cpp
    array/reductions/multiply.cpp

    array/outer/add.cpp
    array/outer/multiply.cpp

    array/accumulations/add.cpp
    array/accumulations/multiply.cpp

    # TODO: fix runtime
    # array/broadcast_to.cpp
    array/atleast_1d.cpp
    array/atleast_2d.cpp
    array/atleast_3d.cpp
    array/concatenate.cpp
    array/expand_dims.cpp
    array/flatten.cpp
    array/flip.cpp
    # TODO: fix runtime
    # array/pad.cpp
    array/pooling.cpp
    array/repeat.cpp
    # TODO: fix runtime
    # array/reshape.cpp
    # array/resize.cpp
    array/slice.cpp
    array/squeeze.cpp
    array/tile.cpp
    array/transpose.cpp
    array/where.cpp
    array/moveaxis.cpp
    array/arange.cpp
    array/zeros.cpp
    array/ones.cpp
    array/full.cpp

    array/sum.cpp
    array/cumsum.cpp
    array/matmul.cpp
    array/prod.cpp
    array/cumprod.cpp
    array/mean.cpp
)

## TODO: support nvcc compilation
add_executable(${PROJECT_NAME}-doctest tests.cpp ${NMTOOLS_CUDA_TEST_SOURCES})

set(NMTOOLS_TEST_CUDA_PATH "/usr/local/cuda/" CACHE STRING "manually set cuda path")
set(NMTOOLS_TEST_CUDA_ARCH "sm_60" CACHE STRING "manually set cuda arch")
set(NMTOOLS_TEST_CUDA_ARGS "" CACHE STRING "manually set extra clang cuda args")

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -Wall -Wextra --std=c++17 -x cuda --cuda-path=${NMTOOLS_TEST_CUDA_PATH} --cuda-gpu-arch=${NMTOOLS_TEST_CUDA_ARCH} ${NMTOOLS_TEST_CUDA_ARGS})
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE cudart_static dl rt pthread)
target_link_directories(${PROJECT_NAME}-doctest PRIVATE "${NMTOOLS_TEST_CUDA_PATH}/lib64")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE _GLIBCXX_DEBUG)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()