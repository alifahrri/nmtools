cmake_minimum_required(VERSION 3.10.2)
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
)

## TODO: support nvcc compilation
add_executable(${PROJECT_NAME}-doctest tests.cpp ${NMTOOLS_SYCL_TEST_SOURCES})

set(NMTOOLS_TEST_SYCL_ARGS "" CACHE STRING "manually set extra syclcc args")

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17 ${NMTOOLS_TEST_SYCL_ARGS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE _GLIBCXX_DEBUG)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()