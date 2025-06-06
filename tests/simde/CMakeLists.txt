cmake_minimum_required(VERSION 3.13)
project(numeric-tests-simde)

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

find_package(PkgConfig)
pkg_check_modules(SIMDE REQUIRED simde)

option(NMTOOLS_SIMDE_TEST_ALL    "test all simde modules"    ON)
option(NMTOOLS_SIMDE_TEST_AVX512 "test simde avx512 modules" OFF)
option(NMTOOLS_SIMDE_TEST_REDUCTION "test simd reduction modules" OFF)
option(NMTOOLS_SIMDE_TEST_MATMUL    "test simde avx512 matmul modules" OFF)

if (NMTOOLS_SIMDE_TEST_ALL)
    set(NMTOOLS_SIMDE_TEST_AVX512 ON CACHE BOOL "test simde avx512" FORCE)
    SET(NMTOOLS_SIMDE_TEST_REDUCTION ON CACHE BOOL "test simd reduction modules" FORCE)
    set(NMTOOLS_SIMDE_TEST_MATMUL ON CACHE BOOL "test simde avx512 matmul modules" FORCE)
endif (NMTOOLS_SIMDE_TEST_ALL)

if (NMTOOLS_SIMDE_TEST_AVX512)
    set(NMTOOLS_SIMDE_TEST_SOURCES ${NMTOOLS_SIMDE_TEST_SOURCES}
        avx512/unary_ufuncs.cpp
        avx512/binary_ufuncs.cpp
        avx512/binary_broadcast.cpp
        avx512/outer_2d.cpp
        avx512/outer_nd.cpp
        avx512/outer_ufuncs.cpp
    )
    if (NMTOOLS_SIMDE_TEST_REDUCTION)
        set(NMTOOLS_SIMDE_TEST_SOURCES ${NMTOOLS_SIMDE_TEST_SOURCES}
            avx512/reduction_ufuncs.cpp
            avx512/reduction_2d.cpp
            avx512/reduction_nd.cpp
        )
    endif (NMTOOLS_SIMDE_TEST_REDUCTION)
    if (NMTOOLS_SIMDE_TEST_MATMUL)
        set(NMTOOLS_SIMDE_TEST_SOURCES ${NMTOOLS_SIMDE_TEST_SOURCES}
            # avx512/matmul.cpp
        )
    endif (NMTOOLS_SIMDE_TEST_MATMUL)
endif (NMTOOLS_SIMDE_TEST_AVX512)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_SIMDE_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
target_compile_options(${PROJECT_NAME}-doctest PRIVATE -march=native)

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
    ${SIMDE_INCLUDE_DIRS}
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)