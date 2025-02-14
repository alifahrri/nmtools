cmake_minimum_required(VERSION 3.13)
project(numeric-tests-hip)

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
# enable_language(HIP)

option(NMTOOLS_HIP_TEST_ALL "test all hip modules" ON)

set(NMTOOLS_HIP_TEST_SOURCES "")

set(NMTOOLS_HIP_TEST_SOURCES ${NMTOOLS_HIP_TEST_SOURCES}
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

    array/broadcast_to.cpp
    array/atleast_1d.cpp
    array/atleast_2d.cpp
    array/atleast_nd.cpp
    array/concatenate.cpp
    array/expand_dims.cpp
    array/flatten.cpp
    array/flip.cpp
    array/hstack.cpp
    array/pad.cpp
    # TODO: fix compile
    # array/pooling.cpp
    array/repeat.cpp
    array/reshape.cpp
    array/resize.cpp
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
    array/vstack.cpp

    array/sum.cpp
    array/cumsum.cpp
    array/matmul.cpp
    array/prod.cpp
    array/cumprod.cpp
    array/mean.cpp

    composition/add_tanh.cpp
    composition/reduce_add_divide.cpp

    array/bilinear.cpp
    array/conv2d.cpp
    array/dot.cpp
    array/kron.cpp
    array/pairwise_distance.cpp
    array/softmax.cpp
    array/stddev.cpp
    array/tensordot.cpp
    array/trace.cpp
    array/var.cpp
    array/vecdot.cpp
    array/vector_norm.cpp
)

## TODO: support nvcc compilation
add_executable(${PROJECT_NAME}-doctest tests.cpp ${NMTOOLS_HIP_TEST_SOURCES})

set(NMTOOLS_TEST_HIP_PATH "/usr/local/hip/" CACHE STRING "manually set hip path")
set(NMTOOLS_TEST_HIP_ARCH "gfx1103" CACHE STRING "manually set hip arch")
set(NMTOOLS_TEST_HIP_ARGS "" CACHE STRING "manually set extra clang hip args")

target_compile_options(${PROJECT_NAME}-doctest PRIVATE
    -Wall -Wextra --std=c++17
    # -x hip
    -Waddress -Wuninitialized
    --offload-arch=${NMTOOLS_TEST_HIP_ARCH} ${NMTOOLS_TEST_HIP_ARGS}
)
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE dl rt pthread)
target_link_directories(${PROJECT_NAME}-doctest PRIVATE "${NMTOOLS_TEST_HIP_PATH}/lib64")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    _GLIBCXX_DEBUG
)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()

target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)