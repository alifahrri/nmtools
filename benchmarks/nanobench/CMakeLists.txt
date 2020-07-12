cmake_minimum_required(VERSION 3.10)

add_executable(
    ode_benchmark
    src/ode.cpp
)

set_target_properties(
    ode_benchmark
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    ode_benchmark PRIVATE
    -O3 -march=native
)

target_include_directories(
    ode_benchmark PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /opt/nanobench/include
    /app/numeric_tools/include
    include
)

add_executable(
    fibonacci_search_benchmark
    src/fibonacci_search.cpp
)

set_target_properties(
    fibonacci_search_benchmark
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    fibonacci_search_benchmark PRIVATE
    -O3 -march=native
)

target_include_directories(
    fibonacci_search_benchmark PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /opt/nanobench/include
    /app/numeric_tools/include
    include
)

add_executable(
    cubic_spline_benchmark
    src/spline.cpp
)

set_target_properties(
    cubic_spline_benchmark
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    cubic_spline_benchmark PRIVATE
    -O3 -march=native
)

target_include_directories(
    cubic_spline_benchmark PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /opt/nanobench/include
    /app/numeric_tools/include
    include
)

add_executable(
    linalg_benchmark
    src/linalg.cpp
)

set_target_properties(
    linalg_benchmark
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    linalg_benchmark PRIVATE
    -O3 -march=native
)

target_include_directories(
    linalg_benchmark PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /opt/nanobench/include
    /app/numeric_tools/include
    include
)

add_executable(
    benchmark
    src/benchmark.cpp
)

set_target_properties(
    benchmark
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    benchmark PRIVATE
    -O3 -march=native
)

target_include_directories(
    benchmark PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /opt/nanobench/include
    /app/numeric_tools/include
    include
)