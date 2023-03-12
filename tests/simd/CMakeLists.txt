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

if (NMTOOLS_SIMD_TEST_ALL)
    set(NMTOOLS_X86_SIMD_TEST_SOURCES
        x86/simd128.cpp
    )
else (NMTOOLS_SIMD_TEST_ALL)
    set(NMTOOLS_X86_SIMD_TEST_SOURCES "")
endif (NMTOOLS_SIMD_TEST_ALL)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_X86_SIMD_TEST_SOURCES}
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME}-doctest PRIVATE -msse4.1)
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