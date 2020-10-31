cmake_minimum_required(VERSION 3.10)
project(nmtools-benchmark-nanobench)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

## setup fmtlib/fmt, may use scripts/install_fmt.sh
find_package(fmt REQUIRED)

## boost (especially type_index)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include(nmtools)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ## include nmtools testing package
    ## TODO: using find_package
    ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/include
)

add_library(nanobench src/nanobench.cpp)

add_executable(
    ${PROJECT_NAME}-ode
    src/ode.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}-ode
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME}-ode PRIVATE nanobench)

add_executable(
    ${PROJECT_NAME}-fibonacci_search
    src/fibonacci_search.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}-fibonacci_search
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME}-fibonacci_search PRIVATE nanobench)

# std::experimental::simd only on gcc 
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
else ()
    add_executable(
        ${PROJECT_NAME}-curvefit
        src/curvefit.cpp
    )
    apply_nmtools(
        TARGET ${PROJECT_NAME}-curvefit
        COMPILE_OPTIONS -O3 -march=native
    )
    target_link_libraries(${PROJECT_NAME}-curvefit PRIVATE nanobench)
endif ()

# std::experimental::simd only on gcc 
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
else()
add_executable(
    ${PROJECT_NAME}-linalg
    src/linalg.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}-linalg
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME}-linalg PRIVATE nanobench)
endif ()

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(NMTOOLS_ROOT_DIR ${PARENT_DIR} DIRECTORY)
add_executable(
    ${PROJECT_NAME}-blas
    # note: test case splitted to multiple files to
    # speed-up compilation when built in parallel
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/clone.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/ones_like.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/zeros_like.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/transpose.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/vvadd.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/mmadd.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/dot.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/outer.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/col_sum.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/row_sum.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/sum.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/vector_norm.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/matrix_norm.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/vsmul.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/msmul.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/mvmul.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/mmmul.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/saxpy.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/blas/gaxpy.cpp
    src/blas.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}-blas
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME}-blas PRIVATE nanobench fmt::fmt)

add_executable(
    ${PROJECT_NAME}-utility
    src/utility.cpp
    # note: test case splitted to multiple files to
    # speed-up compilation when built in parallel
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/array/utility/at.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/array/utility/row.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/array/utility/column.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/array/utility/slice.cpp
    ${NMTOOLS_ROOT_DIR}/tests/src/doctest/array/utility/squeeze.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}-utility
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME}-utility PRIVATE nanobench fmt::fmt)

add_executable(
    ${PROJECT_NAME}
    src/benchmark.cpp
)
apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -O3 -march=native
)
target_link_libraries(${PROJECT_NAME} PRIVATE nanobench)