cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-utl)

option(NMTOOLS_UTL_TEST_ALL "test all utl modules" ON)

add_executable(${PROJECT_NAME} tests.cpp
    src/array.cpp
    src/tuple.cpp
    src/maybe.cpp
    src/either.cpp
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -std=c++17
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=0
)

if (NMTOOLS_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-coverage
        EXECUTABLE ${PROJECT_NAME}
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "/usr/*"
    )
endif (NMTOOLS_CODE_COVERAGE)