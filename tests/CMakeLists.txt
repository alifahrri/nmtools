cmake_minimum_required(VERSION 3.0.2)
project(numeric-tests)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

enable_testing()
find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME} tests.cpp 
    utility.cpp
    roots/bracketing.cpp
    roots/open.cpp
    optimization/unconstrained.cpp
    integration/trapezoidal.cpp
    differentiation/finite.cpp
    taylor/taylor.cpp
    curvefit/regression.cpp
    curvefit/sinusoid.cpp
    curvefit/interpolation.cpp
    fourier/series.cpp
    utility/utility.cpp
    # fourier/transform.cpp
    ode/euler.cpp
    ode/runge_kutta.cpp
    linalg/elimination.cpp
    linalg/decomposition.cpp
    linalg/matvec.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
add_test(tests ${PROJECT_NAME})

include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
    NAME ${PROJECT_NAME}-coverage 
    EXECUTABLE ${PROJECT_NAME}
    EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "${GTEST_INCLUDE_DIRS}/*" "/usr/*"
)