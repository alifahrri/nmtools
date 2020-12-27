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

## defer static check to runtime for clang
## since constexpr math not supported
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

## disable benchmarks
add_definitions(-DNMTOOLS_TESTING_DOCTEST_DISABLE_BENCH)
## may use scripts/install_doctest.sh to install
find_package(doctest REQUIRED)

option(TEST_ALL             "test all modules"              ON)
option(TEST_BLAS            "test blas modules"             OFF)
option(TEST_ARRAY_DETAIL    "test array detail modules"     OFF)
option(TEST_ARRAY_UTILITY   "test array utility modules"    OFF)
option(TEST_UTILS           "test utils modules"            OFF)
option(TEST_NDARRAY         "test ndarray modules"          OFF)
option(TEST_ARRAY_VIEW      "test array view modules"       OFF)
option(TEST_MISC            "test other modules"            OFF)

if (TEST_ALL)
    SET(TEST_BLAS           ON CACHE BOOL "test blas modules"           FORCE)
    SET(TEST_ARRAY_DETAIL   ON CACHE BOOL "test array detail modules"   FORCE)
    SET(TEST_ARRAY_UTILITY  ON CACHE BOOL "test array utility modules"  FORCE)
    SET(TEST_UTILS          ON CACHE BOOL "test utils modules"          FORCE)
    SET(TEST_NDARRAY        ON CACHE BOOL "test ndarray modules"        FORCE)
    SET(TEST_ARRAY_VIEW     ON CACHE BOOL "test array view modules"     FORCE)
    SET(TEST_MISC           ON CACHE BOOL "test other modules"          FORCE)
endif (TEST_ALL)

set(BLAS_TEST_SOURCES
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
)
if (NOT TEST_BLAS)
    set(BLAS_TEST_SOURCES "")
endif ()

set(ARRAY_DETAIL_TEST_SOURCES
    src/doctest/array/shape.cpp
    src/doctest/array/index/compute_indices.cpp
    src/doctest/array/index/compute_offset.cpp
    src/doctest/array/index/compute_strides.cpp
    src/doctest/array/index/gather.cpp
    src/doctest/array/index/indices_pack.cpp
    src/doctest/array/index/reverse.cpp
    src/doctest/array/index/scatter.cpp
)
if (NOT TEST_ARRAY_DETAIL)
    set(ARRAY_DETAIL_TEST_SOURCES "")
endif ()

set(UTILS_TEST_SOURCES
    src/doctest/utils/isequal.cpp
    src/doctest/utils/isclose.cpp
    src/doctest/utils/to_string.cpp
)
if (NOT TEST_UTILS)
    set(UTILS_TEST_SOURCES "")
endif ()

set(ARRAY_UTILITY_TEST_SOURCES
    src/doctest/array/utility/at.cpp
    src/doctest/array/utility/apply_at.cpp
    src/doctest/array/utility/cast.cpp
    src/doctest/array/utility/clone.cpp
    src/doctest/array/utility/row.cpp
    src/doctest/array/utility/column.cpp
    src/doctest/array/utility/slice.cpp
    src/doctest/array/utility/squeeze.cpp
    src/doctest/array/utility/zeros_like.cpp
)
if (NOT TEST_ARRAY_UTILITY)
    set (ARRAY_UTILITY_TEST_SOURCES "")
endif ()

set(NDARRAY_TEST_SOURCES
    src/doctest/array/fixed/vector.cpp
    src/doctest/array/fixed/matrix.cpp
    src/doctest/array/dynamic/matrix.cpp
    src/doctest/array/fixed/ndarray.cpp
    src/doctest/array/dynamic/ndarray.cpp
)
if (NOT TEST_NDARRAY)
    set(NDARRAY_TEST_SOURCES "")
endif ()

set(ARRAY_VIEW_TEST_SOURCES
    src/doctest/array/view/flatten.cpp
    src/doctest/array/view/mutable_flatten.cpp
    src/doctest/array/view/mutable_ref.cpp
    src/doctest/array/view/mutable_slice.cpp
    src/doctest/array/view/ref.cpp
    src/doctest/array/view/ref/initializer_list.cpp
    src/doctest/array/view/reshape.cpp
    src/doctest/array/view/slice.cpp
    src/doctest/array/view/transpose.cpp
)
if (NOT TEST_ARRAY_VIEW)
    set (ARRAY_VIEW_TEST_SOURCES "")
endif ()

set(MISC_TEST_SOURCES
    src/doctest/misc/constants.cpp
)
if (NOT TEST_MISC)
    set (MISC_TEST_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest src/doctest/tests.cpp 
    ## blas module
    ${BLAS_TEST_SOURCES}
    ## array detail
    ${ARRAY_DETAIL_TEST_SOURCES}
    ## utility function
    ${UTILS_TEST_SOURCES}
    ## array utility
    ${ARRAY_UTILITY_TEST_SOURCES}
    ## ndarray
    ${NDARRAY_TEST_SOURCES}
    ## view
    ${ARRAY_VIEW_TEST_SOURCES}
    ## misc
    ${MISC_TEST_SOURCES}
)
target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)

add_executable(${PROJECT_NAME}-doctest-meta src/doctest/tests.cpp 
    ## metafunctions
    src/doctest/meta.cpp
    src/doctest/meta/traits/apply_conjunction.cpp
    src/doctest/meta/traits/apply_disjunction.cpp
    src/doctest/meta/traits/compose_logical_and.cpp
    src/doctest/meta/traits/compose_logical_or.cpp
    src/doctest/meta/traits/ndarray.cpp
    src/doctest/meta/traits/has_template_get.cpp
    src/doctest/meta/traits/has_type.cpp
    src/doctest/meta/traits/has_square_bracket.cpp
    src/doctest/meta/transform/accumulate.cpp
    src/doctest/meta/transform/apply.cpp
    src/doctest/meta/transform/constant.cpp
    src/doctest/meta/transform/constant_to_sequence.cpp
    src/doctest/meta/transform/gather.cpp
    src/doctest/meta/transform/get_element_type.cpp
    src/doctest/meta/transform/replace_element_type.cpp
    src/doctest/meta/transform/nested_array_dim.cpp
    src/doctest/meta/transform/reduce.cpp
    src/doctest/meta/transform/remove_nested_array_extents.cpp
    src/doctest/meta/transform/replace_at.cpp
    src/doctest/meta/transform/sequence.cpp
    src/doctest/meta/transform/split_at.cpp
    src/doctest/meta/transform/scatter.cpp
    src/doctest/meta/get_container_value_type.cpp
    src/doctest/meta/blas/mmadd.cpp
    src/doctest/meta/blas/mmmul.cpp
    src/doctest/meta/blas/dot.cpp
    src/doctest/meta/blas/row.cpp
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

option(DEFER_STATIC_CHECK "defer static check to runtime for testing purpose" OFF)
if (DEFER_STATIC_CHECK)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()


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