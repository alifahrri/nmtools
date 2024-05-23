cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-doctest-meta)

set( META_VIEW_TEST_SOURCES
    array/view/accumulate.cpp
    array/view/broadcast_to.cpp
    array/view/compress.cpp
    array/view/concatenate.cpp
    array/view/full.cpp
    array/view/matmul.cpp
    array/view/moveaxis.cpp
    array/view/outer.cpp
    array/view/pad.cpp
    array/view/pooling.cpp
    array/view/prod.cpp
    array/view/reduce.cpp
    array/view/repeat.cpp
    array/view/reshape.cpp
    array/view/take.cpp
    array/view/tile.cpp
    array/view/transpose.cpp
    array/view/ufunc.cpp
    array/view/var.cpp
    array/view/where.cpp
)

set( META_EVAL_TEST_SOURCES
    array/eval/arange.cpp
    array/eval/broadcast_to.cpp
    array/eval/concatenate.cpp
    array/eval/full.cpp
    array/eval/matmul.cpp
    array/eval/prod.cpp
    array/eval/reduce.cpp
    array/eval/repeat.cpp
    array/eval/take.cpp
    array/eval/tile.cpp
    array/eval/ufunc.cpp
    array/eval/where.cpp
)

set( META_INDEX_TEST_SOURCES
    array/index/arange.cpp
    array/index/broadcast_shape.cpp
    array/index/broadcast_to.cpp
    array/index/argsort.cpp
    array/index/choose.cpp
    array/index/compute_indices.cpp
    array/index/compute_strides.cpp
    array/index/concatenate.cpp
    array/index/conv.cpp
    array/index/expand_dims.cpp
    array/index/gather.cpp
    array/index/insert_index.cpp
    array/index/logical_not.cpp
    array/index/matmul.cpp
    array/index/nonzero.cpp
    array/index/pooling.cpp
    array/index/remove_dims.cpp
    array/index/remove_single_dims.cpp
    array/index/repeat.cpp
    array/index/reshape.cpp
    array/index/reverse.cpp
    array/index/scatter.cpp
    array/index/slice.cpp
    array/index/split.cpp
    array/index/sum.cpp
    array/index/take_along_axis.cpp
    array/index/where.cpp
)

set( META_TRAIT_TEST_SOURCES
    traits/ndarray.cpp
    traits/has_template_get.cpp
    traits/has_type.cpp
    traits/has_square_bracket.cpp
    traits/is_base_of.cpp
    traits/is_class.cpp
    traits/is_clipped_integer.cpp
    traits/is_destructible.cpp
    traits/is_index.cpp
    traits/is_index_array.cpp
    traits/is_integer.cpp
    traits/is_num.cpp
    traits/is_pod.cpp
    traits/is_reference.cpp
    traits/is_slice_index_array.cpp
    traits/is_slice_index.cpp
)

set( META_TRANSFORM_TEST_SOURCES
    transform/add_reference.cpp
    transform/apply.cpp
    transform/common_type.cpp
    transform/get_common_type.cpp
    transform/get_either_left.cpp
    transform/get_either_right.cpp
    transform/get_element_type.cpp
    transform/get_element_or_common_type.cpp
    transform/hybrid_ndarray_max_size.cpp
    transform/remove_reference.cpp
    transform/replace_element_type.cpp
    transform/nested_array_dim.cpp
    transform/promote_index.cpp
    transform/remove_nested_array_extents.cpp
    transform/resize_fixed_ndarray.cpp
    transform/resize_hybrid_ndarray_max_size.cpp
    transform/transform_bounded_array.cpp
    transform/to_value.cpp
)

set( META_UTILITY_TEST_SOURCES
    utility/flatten_either.cpp
)

add_executable(${PROJECT_NAME} tests.cpp 
    ## metafunctions
    forward.cpp
    integral_constant.cpp
    loop.cpp
    make_index_sequence.cpp
    array/cast_kind.cpp
    array/ndarray.cpp
    array/boost.cpp
    array/stl.cpp
    array/fixed.cpp
    array/hybrid.cpp
    array/error_type.cpp
    ${META_EVAL_TEST_SOURCES}
    ${META_VIEW_TEST_SOURCES}
    ${META_INDEX_TEST_SOURCES}
    ${META_TRAIT_TEST_SOURCES}
    ${META_TRANSFORM_TEST_SOURCES}
    ${META_UTILITY_TEST_SOURCES}
)
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

# omg
if ((NOT EMSCRIPTEN) AND (NOT ANDROID))
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
    if (doctest_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)
    endif()
endif()

apply_nmtools(
    TARGET ${PROJECT_NAME}
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# for now, force metafunctions test to defer static check
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    DEFER_STATIC_CHECK
)
# useful for debugging metafunctions
# TODO: this may not be portable across compiler, detect compiler
target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=0
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(numeric-tests-doctest-meta PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)