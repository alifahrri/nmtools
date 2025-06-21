cmake_minimum_required(VERSION 3.13)
project(numeric-tests-network)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

## TODO: remove
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

# TODO: remove, trye to detect constexpr math from stdlib
## defer static check to runtime for clang
## since constexpr math not supported
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR EMSCRIPTEN OR ANDROID OR MSYS)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

option(NMTOOLS_NETWORK_TEST_ALL "test all network modules" ON)

option(NMTOOLS_NETWORK_TEST_META "test network meta modules" OFF)
option(NMTOOLS_NETWORK_TEST_DIGRAPH "test network digraph modules" OFF)

set(NETWORK_TEST_META_SOURCES
    meta.cpp
)

set(NETWORK_TEST_DIGRAPH_SOURCES
    src/add_edge.cpp
    src/compose.cpp
    src/contracted_edge.cpp
    src/filter_node_arity.cpp
    src/filter_nodes.cpp
    src/has_path.cpp
    src/in_degree.cpp
    src/is_directed_acyclic_graph.cpp
    src/out_degree.cpp
    src/out_edges.cpp
    src/predecessors.cpp
    src/topological_generations.cpp
    src/topological_sort.cpp

    src/digraph.cpp
    src/expression_tree.cpp
)

if (NMTOOLS_NETWORK_TEST_ALL)
    set(NMTOOLS_NETWORK_TEST_META ON CACHE BOOL "test network meta modules" FORCE)
    set(NMTOOLS_NETWORK_TEST_DIGRAPH ON CACHE BOOL "test network digraph modules" FORCE)
endif()

if(NOT ${NMTOOLS_NETWORK_TEST_META})
    set(NETWORK_TEST_META_SOURCES "")
endif()

if(NOT ${NMTOOLS_NETWORK_TEST_DIGRAPH})
    set(NETWORK_TEST_DIGRAPH_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ## meta
    ${NETWORK_TEST_META_SOURCES}
    ${NETWORK_TEST_DIGRAPH_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

## TODO: remove
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
target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE
    # NMTOOLS_ISCLOSE_NAN_HANDLING=1
    NMTOOLS_ISCLOSE_INF_HANDLING=1
)