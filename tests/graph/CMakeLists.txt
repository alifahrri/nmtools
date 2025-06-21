cmake_minimum_required(VERSION 3.13)
project(numeric-tests-compute-graph)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

if(NMTOOLS_INCLUDE_DIR)
    message(STATUS "    NMTOOLS_INCLUDE_DIR: ${NMTOOLS_INCLUDE_DIR}")
else()
    message(STATUS "trying to find nmtools")
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    message(STATUS "    NMTOOLS_INCLUDE_DIR: ${NMTOOLS_INCLUDE_DIR}")
endif()

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

option(NMTOOLS_COMPUTE_GRAPH_TEST_ALL "test all graph modules" ON)

option(NMTOOLS_COMPUTE_GRAPH_TEST_GRAPH     "test all expression graph modules"      OFF)

set(GRAPH_TEST_GRAPH_SOURCES
    src/add.cpp
    src/avg_pool2d.cpp
    src/batch_norm.cpp
    src/bilinear.cpp
    src/broadcast_to.cpp
    src/conv2d.cpp
    src/cosine_similarity.cpp
    src/dot.cpp
    src/group_norm.cpp
    src/instance_norm.cpp
    src/kron.cpp
    src/layer_norm.cpp
    src/matmul.cpp
    src/max_pool2d.cpp
    src/mean.cpp
    src/pad.cpp
    src/pairwise_distance.cpp
    src/reshape.cpp
    src/softmax.cpp
    src/stddev.cpp
    src/tensordot.cpp
    src/trace.cpp
    src/tri.cpp
    src/var.cpp
    src/vecdot.cpp
    src/vector_norm.cpp
    src/vstack.cpp
)

if (NMTOOLS_COMPUTE_GRAPH_TEST_ALL)
    set(NMTOOLS_COMPUTE_GRAPH_TEST_GRAPH      ON CACHE BOOL "test expression graph modules"  FORCE)
endif()

if (NOT ${NMTOOLS_COMPUTE_GRAPH_TEST_GRAPH})
    set(GRAPH_TEST_GRAPH_SOURCES "")
endif()

set(GRAPH_TEST_SOURCES
    ${GRAPH_TEST_GRAPH_SOURCES}
)

add_executable(${PROJECT_NAME}-doctest tests.cpp 
    ## functional
    ${GRAPH_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17 -mcmodel=large)
target_link_options(${PROJECT_NAME}-doctest PRIVATE -mcmodel=large -flto -Wl,-allow-multiple-definition)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)
target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    # NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)