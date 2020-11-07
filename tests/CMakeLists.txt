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

# workaround for clang since gcc has constexpr math but clang doesnt
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(GTEST_SOURCE
        # src/gtest/roots/bracketing.cpp
        # src/gtest/roots/open.cpp
        # src/gtest/optimization/unconstrained.cpp
        # src/gtest/integration/trapezoidal.cpp
        # src/gtest/differentiation/finite.cpp
        # src/gtest/taylor/taylor.cpp
        # src/gtest/curvefit/regression.cpp
        # src/gtest/curvefit/sinusoid.cpp
        # src/gtest/curvefit/interpolation.cpp
        # src/gtest/utility/utility.cpp
        # src/gtest/ode/euler.cpp
        # src/gtest/ode/runge_kutta.cpp
        # src/gtest/linalg/elimination.cpp
        # src/gtest/linalg/decomposition.cpp
        # src/gtest/blas/blas.cpp
        # src/gtest/array/dynamic.cpp
        # src/gtest/array/fixed.cpp
        # src/gtest/array/utility.cpp
        # src/gtest/array/linalg.cpp
    )
else()
    set(GTEST_SOURCE
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
endif()

add_executable(${PROJECT_NAME} src/gtest/tests.cpp 
    ${GTEST_SOURCE}
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
    ## array detail
    src/doctest/array/detail.cpp
    ## array utility
    src/doctest/array/utility/at.cpp
    src/doctest/array/utility/row.cpp
    src/doctest/array/utility/column.cpp
    src/doctest/array/utility/slice.cpp
    src/doctest/array/utility/squeeze.cpp
    ## ndarray
    src/doctest/array/fixed/ndarray.cpp
    src/doctest/array/dynamic/ndarray.cpp
    ## view
    src/doctest/array/view/ref.cpp
    src/doctest/array/view/mutable_ref.cpp
    src/doctest/array/view/slice.cpp
    src/doctest/array/view/mutable_slice.cpp
    src/doctest/array/view/transpose.cpp
    src/doctest/array/view/flatten.cpp
)
target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)

add_executable(${PROJECT_NAME}-doctest-meta src/doctest/tests.cpp 
    ## metafunctions
    src/doctest/meta.cpp
    src/doctest/meta/traits/ndarray.cpp
    src/doctest/meta/traits/has_square_bracket.cpp
    src/doctest/meta/transform/get_element_type.cpp
    src/doctest/meta/transform/remove_nested_array_extents.cpp
    src/doctest/meta/get_container_value_type.cpp
    src/doctest/meta/blas/mmadd.cpp
    src/doctest/meta/blas/mmmul.cpp
    src/doctest/meta/blas/dot.cpp
)
target_compile_features(${PROJECT_NAME}-doctest-meta PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-doctest-meta PRIVATE doctest::doctest)

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

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest-meta
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest-meta PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(ADDRESS_SANITIZER "build with -fsanitize=address" OFF)
message(STATUS "ADDRESS_SANITIZER ${ADDRESS_SANITIZER}")

# from https://gist.github.com/jlblancoc/44be9d4d466f0a973b1f3808a8e56782
# TODO: findout if can be used for private target instead
# TODO: find out if can be used with other compiler
# TODO: provide option to disable/enable
if (ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
endif (ADDRESS_SANITIZER)

option(CODE_COVERAGE "build with code coverage reporting" OFF)
message(STATUS "CODE_COVERAGE ${CODE_COVERAGE}")
if (CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-coverage 
        EXECUTABLE ${PROJECT_NAME}
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "${GTEST_INCLUDE_DIRS}/*" "/usr/*"
    )
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-doctest-coverage 
        EXECUTABLE ${PROJECT_NAME}-doctest
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "/usr/*"
    )
endif (CODE_COVERAGE)