cmake_minimum_required(VERSION 3.13)
project(numeric-tests-utl-meta)

add_executable(${PROJECT_NAME} tests.cpp
    ## metafunctions test sources
    src/fixed_ndarray_shape.cpp
    src/get_either_type.cpp
    src/get_common_type.cpp
    src/get_element_type.cpp
    src/get_element_or_common_type.cpp
    src/get_maybe_type.cpp
    src/len.cpp
    src/nested_array_dim.cpp
    src/replace_element_type.cpp
    src/resize_fixed_ndarray.cpp
    src/fixed_dim.cpp
    src/fixed_size.cpp
    src/fixed_shape.cpp
    src/bounded_dim.cpp
    src/bounded_size.cpp
    ## traits
    src/is_ndarray.cpp
    src/is_maybe.cpp
    src/is_either.cpp
    src/is_tuple.cpp
    src/is_fixed_index_array.cpp
    src/is_index_array.cpp
    src/is_constant_index_array.cpp
    src/has_at.cpp
    src/has_square_bracket.cpp
    src/has_size.cpp
    src/has_value_type.cpp
    ## meta view
    src/broadcast_to.cpp
)
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

# disable stl but still use std::string
target_compile_definitions(${PROJECT_NAME} PRIVATE
    NMTOOLS_DISABLE_STL
    NMTOOLS_STRING=std::string
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -std=c++17
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(numeric-tests-utl-meta     PRIVATE coverage_config)
endif (NMTOOLS_CODE_COVERAGE)