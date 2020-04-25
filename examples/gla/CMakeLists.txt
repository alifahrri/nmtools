cmake_minimum_required(VERSION 3.10)

add_executable(
    dynamic
    src/dynamic.cpp
)

set_target_properties(
    dynamic
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    dynamic PRIVATE
    -g
)

target_include_directories(
    dynamic PRIVATE
    ## TODO : properly find package instead of directly specifying include dir
    /usr/local/include/eigen3
    /app/numeric_tools/include
)

target_link_libraries(
    dynamic PRIVATE
    armadillo
)