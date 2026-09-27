cmake_minimum_required(VERSION 3.13)
project(numeric-tests-runtime)

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

add_executable(${PROJECT_NAME}-doctest tests.cpp
    array.cpp
    node.cpp
    computational_graph.cpp

    src/broadcast_to.cpp
    src/reshape.cpp

    src/add.cpp
    src/multiply.cpp
    src/subtract.cpp
    src/divide.cpp

    src/sum.cpp
    src/prod.cpp

    src/cos.cpp
    src/cosh.cpp
    src/sin.cpp
    src/sinh.cpp
    src/exp.cpp
    src/exp2.cpp
    src/expm1.cpp
    src/fabs.cpp
    src/floor.cpp
    src/invert.cpp
    src/isfinite.cpp
    src/isinf.cpp
    src/isnan.cpp
    src/log.cpp
    src/log1p.cpp
    src/log2.cpp
    src/log10.cpp
    src/negative.cpp
    src/reciprocal.cpp
    src/rint.cpp
    src/signbit.cpp
    src/sqrt.cpp
    src/square.cpp
    src/tan.cpp
    src/tanh.cpp
    src/trunc.cpp
    src/arccos.cpp
    src/arccosh.cpp
    src/arcsin.cpp
    src/arcsinh.cpp
    src/arctan.cpp
    src/arctanh.cpp
    src/cbrt.cpp
    src/ceil.cpp
)

add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE
    -std=c++17
    # -fexcess-precision=standard
)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

target_link_libraries(${PROJECT_NAME}-doctest PRIVATE nmtoolsrt)

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)