cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-vector)

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

option(NMTOOLS_VECTOR_TEST_ALL "test all vector modules" OFF)
option(NMTOOLS_VECTOR_TEST_128 "test vector 128 simd modules" OFF)
option(NMTOOLS_VECTOR_TEST_256 "test vector 256 simd modules" OFF)
option(NMTOOLS_VECTOR_TEST_512 "test vector 512 simd modules" OFF)

if (NMTOOLS_VECTOR_TEST_ALL)
    SET(NMTOOLS_VECTOR_TEST_128 ON CACHE BOOL "test vector 128 simd" FORCE)
    SET(NMTOOLS_VECTOR_TEST_256 ON CACHE BOOL "test vector 256 simd" FORCE)
    SET(NMTOOLS_VECTOR_TEST_512 ON CACHE BOOL "test vector 512 simd" FORCE)
endif (NMTOOLS_VECTOR_TEST_ALL)

set(NMTOOLS_VECTOR_TEST_SOURCES "")

if (NMTOOLS_VECTOR_TEST_128)
    set(NMTOOLS_VECTOR_TEST_SOURCES ${NMTOOLS_VECTOR_TEST_SOURCES}
        binary_vector128.cpp
        binary_vector128_broadcast.cpp
        matmul_vector128.cpp
        unary_vector128.cpp
        reduction_vector128.cpp
    )
endif (NMTOOLS_VECTOR_TEST_128)

if (NMTOOLS_VECTOR_TEST_256)
    set(NMTOOLS_VECTOR_TEST_SOURCES ${NMTOOLS_VECTOR_TEST_SOURCES}
        binary_vector256.cpp
        binary_vector256_broadcast.cpp
        matmul_vector256.cpp
        unary_vector256.cpp
        reduction_vector256.cpp
    )
endif (NMTOOLS_VECTOR_TEST_256)

if (NMTOOLS_VECTOR_TEST_512)
    set(NMTOOLS_VECTOR_TEST_SOURCES ${NMTOOLS_VECTOR_TEST_SOURCES}
        binary_vector512.cpp
        binary_vector512_broadcast.cpp
        matmul_vector512.cpp
        reduction_vector512.cpp
        unary_vector512.cpp
    )
endif (NMTOOLS_VECTOR_TEST_512)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_VECTOR_TEST_SOURCES}
)

set(NMTOOLS_VECTOR_TEST_ARCH "-march=native" CACHE STRING "manually set target arch")

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME}-doctest PRIVATE ${NMTOOLS_VECTOR_TEST_ARCH})

# when trying to compile with uint16 dtype:
# error: AVX512F vector return without AVX512F enabled changes the ABI
# note: the ABI for passing parameters with 64-byte alignment has changed in GCC 4.6
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -Wno-psabi)
endif ()

target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)