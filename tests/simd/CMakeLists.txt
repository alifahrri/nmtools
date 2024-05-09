cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-simd)

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

option(NMTOOLS_SIMD_TEST_ALL "test all simd modules" OFF)
option(NMTOOLS_SIMD_TEST_SSE "test x86 sse simd modules" OFF)
option(NMTOOLS_SIMD_TEST_AVX "test x86 avx simd modules" OFF)
option(NMTOOLS_SIMD_TEST_REDUCTION "test simd reduction modules" OFF)
option(NMTOOLS_SIMD_TEST_INDEX "test index simd modules" OFF)

if (NMTOOLS_SIMD_TEST_ALL)
    SET(NMTOOLS_SIMD_TEST_SSE ON CACHE BOOL "test x86 sse simd" FORCE)
    SET(NMTOOLS_SIMD_TEST_AVX ON CACHE BOOL "test x86 avx simd" FORCE)
    SET(NMTOOLS_SIMD_TEST_INDEX ON CACHE BOOL "test index simd" FORCE)
    SET(NMTOOLS_SIMD_TEST_REDUCTION ON CACHE BOOL "test simd reduction modules" FORCE)
endif (NMTOOLS_SIMD_TEST_ALL)

set(NMTOOLS_SIMD_TEST_SOURCES "")

if (NMTOOLS_SIMD_TEST_SSE)
    set(NMTOOLS_SIMD_TEST_SOURCES ${NMTOOLS_SIMD_TEST_SOURCES}
        x86/unary_sse.cpp
        x86/binary_sse.cpp
        x86/matmul_sse.cpp
        x86/outer_sse.cpp
        x86/outer_2d_sse.cpp
        x86/outer_nd_sse.cpp
    )
    if (NMTOOLS_SIMD_TEST_REDUCTION)
        set(NMTOOLS_SIMD_TEST_SOURCES ${NMTOOLS_SIMD_TEST_SOURCES}
            x86/reduction_sse.cpp
            x86/reduction_2d_sse.cpp
            x86/reduction_nd_sse.cpp
        )
    endif (NMTOOLS_SIMD_TEST_REDUCTION)
endif (NMTOOLS_SIMD_TEST_SSE)

if (NMTOOLS_SIMD_TEST_AVX)
    set(NMTOOLS_SIMD_TEST_SOURCES ${NMTOOLS_SIMD_TEST_SOURCES}
        x86/unary_avx.cpp
        x86/binary_avx.cpp
        x86/binary_avx_broadcast.cpp
        x86/matmul_avx.cpp
        x86/outer_avx.cpp
        x86/outer_2d_avx.cpp
        x86/outer_nd_avx.cpp
    )
    if (NMTOOLS_SIMD_TEST_REDUCTION)
        set(NMTOOLS_SIMD_TEST_SOURCES ${NMTOOLS_SIMD_TEST_SOURCES}
            x86/reduction_avx.cpp
            x86/reduction_2d_avx.cpp
            x86/reduction_nd_avx.cpp
        )
    endif (NMTOOLS_SIMD_TEST_REDUCTION)
endif (NMTOOLS_SIMD_TEST_AVX)

if (NMTOOLS_SIMD_TEST_INDEX)
    set(NMTOOLS_SIMD_TEST_SOURCES ${NMTOOLS_SIMD_TEST_SOURCES}
        index/simd_index.cpp
        index/simd_matmul.cpp
        index/simd_reduction.cpp
        index/simd_outer.cpp
    )
endif (NMTOOLS_SIMD_TEST_INDEX)
add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_SIMD_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
if (NMTOOLS_SIMD_TEST_SSE)
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -msse4.1 -msse -msse2 -msse3)
endif (NMTOOLS_SIMD_TEST_SSE)
if (NMTOOLS_SIMD_TEST_AVX)
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -mavx2 -mfma)
endif (NMTOOLS_SIMD_TEST_AVX)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
endif()
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -msimd128)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()

target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)