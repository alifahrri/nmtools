cmake_minimum_required(VERSION 3.13)
project(numeric-tests-sycl)

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

find_package(OpenMP)

enable_testing()

option(NMTOOLS_SYCL_TEST_ALL "test all sycl modules" ON)
set(NMTOOLS_SYCL_TEST_SOURCES "")

set(NMTOOLS_SYCL_TEST_SOURCES ${NMTOOLS_SYCL_TEST_SOURCES}
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
    array/activations/softshrink.cpp
    array/activations/softsign.cpp
    array/activations/tanhshrink.cpp

    array/ufuncs/add.cpp
    array/ufuncs/multiply.cpp

    array/reductions/add.cpp
    array/reductions/multiply.cpp

    array/accumulations/add.cpp
    array/accumulations/multiply.cpp

    array/outer/add.cpp
    array/outer/multiply.cpp

    array/resize.cpp
    array/atleast_1d.cpp
    array/atleast_2d.cpp
    array/atleast_nd.cpp
    array/broadcast_to.cpp
    array/concatenate.cpp
    array/expand_dims.cpp
    array/flatten.cpp
    array/flip.cpp
    array/hstack.cpp
    array/pad.cpp
    array/pooling.cpp
    array/repeat.cpp
    array/reshape.cpp
    array/slice.cpp
    array/squeeze.cpp
    array/stack.cpp
    array/tile.cpp
    array/transpose.cpp
    array/where.cpp
    array/moveaxis.cpp
    array/arange.cpp
    array/full.cpp
    array/ones.cpp
    array/vstack.cpp
    array/zeros.cpp

    array/sum.cpp
    array/cumsum.cpp
    array/matmul.cpp
    array/prod.cpp
    array/cumprod.cpp
    array/mean.cpp

    ## TODO: fix compile on cuda
    # composition/add_tanh.cpp
    # composition/divide_subtract.cpp
    # composition/fabs_square_sum.cpp
    # composition/fabs_square.cpp
    # composition/multiply_add.cpp
    # composition/multiply_tanh.cpp
    # composition/multiply_add_tanh.cpp
    # composition/reduce_add_divide.cpp
    # composition/reduce_add_tanh.cpp
    # composition/reduce_maximum_subtract_exp.cpp
    # composition/square_sum_divide.cpp
    # composition/square_sum.cpp
    # composition/subtract_exp.cpp
    # composition/subtract_fabs_square.cpp
    # composition/subtract_fabs.cpp
    # composition/sum_divide.cpp
)

## TODO: support nvcc compilation
add_executable(${PROJECT_NAME}-doctest tests.cpp ${NMTOOLS_SYCL_TEST_SOURCES})
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

set(NMTOOLS_TEST_SYCL_ARGS "" CACHE STRING "manually set extra syclcc args")

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17 ${NMTOOLS_TEST_SYCL_ARGS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    _GLIBCXX_DEBUG
)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()

if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE OpenMP::OpenMP_CXX)
endif()

target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)