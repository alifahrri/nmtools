cmake_minimum_required(VERSION 3.0.2)
project(numeric-tests)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()
find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME} src/gtest/tests.cpp 
    src/gtest/roots/bracketing.cpp
    src/gtest/roots/open.cpp
    src/gtest/optimization/unconstrained.cpp
    src/gtest/integration/trapezoidal.cpp
    src/gtest/differentiation/finite.cpp
    src/gtest/taylor/taylor.cpp
    src/gtest/curvefit/regression.cpp
    src/gtest/curvefit/sinusoid.cpp
    src/gtest/curvefit/interpolation.cpp
    src/gtest/utility/utility.cpp
    src/gtest/ode/euler.cpp
    src/gtest/ode/runge_kutta.cpp
    src/gtest/linalg/elimination.cpp
    src/gtest/linalg/decomposition.cpp
    src/gtest/blas/blas.cpp
    src/gtest/array/dynamic.cpp
    src/gtest/array/fixed.cpp
    src/gtest/array/utility.cpp
    src/gtest/array/linalg.cpp
)

## disable benchmarks
add_definitions(-DNMTOOLS_TESTING_DOCTEST_DISABLE_BENCH)
## may use scripts/install_doctest.sh to install
find_package(doctest REQUIRED)

add_executable(${PROJECT_NAME}-doctest src/doctest/tests.cpp 
    ## blas module
    src/doctest/blas/clone.cpp
    src/doctest/blas/ones_like.cpp
    src/doctest/blas/zeros_like.cpp
    src/doctest/blas/transpose.cpp
    src/doctest/blas/vvadd.cpp
    src/doctest/blas/mmadd.cpp
    src/doctest/blas/dot.cpp
    src/doctest/blas/outer.cpp
    src/doctest/blas/col_sum.cpp
    src/doctest/blas/row_sum.cpp
    src/doctest/blas/sum.cpp
    src/doctest/blas/vector_norm.cpp
    src/doctest/blas/matrix_norm.cpp
    src/doctest/blas/vsmul.cpp
    src/doctest/blas/msmul.cpp
    src/doctest/blas/mvmul.cpp
    src/doctest/blas/mmmul.cpp
    src/doctest/blas/saxpy.cpp
    src/doctest/blas/gaxpy.cpp
    ## array utility
    src/doctest/array/utility/at.cpp
    src/doctest/array/utility/row.cpp
    src/doctest/array/utility/column.cpp
    src/doctest/array/utility/slice.cpp
    src/doctest/array/utility/squeeze.cpp
    ## metafunctions
    src/doctest/meta.cpp
)
target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)

apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
add_test(tests ${PROJECT_NAME})

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
    NAME ${PROJECT_NAME}-coverage 
    EXECUTABLE ${PROJECT_NAME}
    EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "${GTEST_INCLUDE_DIRS}/*" "/usr/*"
)