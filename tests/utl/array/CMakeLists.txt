cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-utl-array)

add_executable(${PROJECT_NAME} tests.cpp
    index/compute_strides.cpp
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
    target_link_libraries(numeric-tests-utl-array    PRIVATE coverage_config)
endif (NMTOOLS_CODE_COVERAGE)