cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-utility)

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
    src/small_vector.cpp
    src/at.cpp
    src/apply_at.cpp
    src/cast.cpp
    src/data.cpp
    src/flatten_either.cpp
    src/isequal.cpp
    src/isclose.cpp
    src/to_string.cpp
)
add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)
target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

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