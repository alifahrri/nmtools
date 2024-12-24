cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-utl)

option(NMTOOLS_UTL_TEST_ALL "test all utl modules" ON)

add_executable(${PROJECT_NAME} tests.cpp
    src/array.cpp
    src/tuple.cpp
    src/maybe.cpp
    src/either.cpp
    src/vector.cpp
    src/clipped_integer.cpp
    src/static_queue.cpp
    src/static_vector.cpp
    src/tuplev2.cpp
)
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -std=c++17
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=0
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(numeric-tests-utl PRIVATE coverage_config)
endif (NMTOOLS_CODE_COVERAGE)