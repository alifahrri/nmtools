cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-utl-array)

add_executable(${PROJECT_NAME} tests.cpp
    index/compute_strides.cpp
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