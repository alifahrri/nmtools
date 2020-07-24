cmake_minimum_required(VERSION 3.10)
project(nmtools-example)

add_executable(
    ${PROJECT_NAME}-fibonacci_search
    src/fibonacci_search.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-fibonacci_search
    COMPILE_OPTIONS "-g"
)

add_executable(
    ${PROJECT_NAME}-spline
    src/spline.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-spline
    COMPILE_OPTIONS "-g"
)

add_executable(
    ${PROJECT_NAME}-ode
    src/ode.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-ode
    COMPILE_OPTIONS "-g"
)

add_executable(
    ${PROJECT_NAME}-elimination
    src/elimination.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-elimination
    COMPILE_OPTIONS "-g"
)

add_executable(
    ${PROJECT_NAME}-decomposition
    src/decomposition.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-decomposition
    COMPILE_OPTIONS "-g"
)

add_executable(
    ${PROJECT_NAME}-curvefit
    src/curvefit.cpp
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-curvefit
    COMPILE_OPTIONS "-g"
)