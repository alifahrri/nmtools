cmake_minimum_required(VERSION 3.10)

add_executable(
    fibonacci_search
    src/fibonacci_search.cpp
)

set_target_properties(
    fibonacci_search
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    fibonacci_search PRIVATE
    -g
)

target_include_directories(
    fibonacci_search PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /app/numeric_tools/include
)

add_executable(
    spline
    src/spline.cpp
)

set_target_properties(
    spline
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    spline PRIVATE
    -g
)

target_include_directories(
    spline PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /app/numeric_tools/include
)