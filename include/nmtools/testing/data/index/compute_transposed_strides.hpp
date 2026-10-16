#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_TRANSPOSED_STRIDES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_TRANSPOSED_STRIDES_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(compute_transposed_strides)
{
    using namespace literals;

    // (3,8) row-major strides {8,1}, transpose(1,0) -> {1,8}
    // see testing/data/array/stride.hpp case15
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[2] = {3,8};
        inline auto shape_ct  = nmtools_tuple{3_ct,8_ct};
        inline auto shape_mx1 = nmtools_tuple{3,8_ct};
        inline int32_t axes[2] = {1,0};
        inline auto axes_ct = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int32_t result[2] = {1,8};
    }

    // (2,4,3) row-major strides {12,3,1}, full reverse -> {1,3,12}
    // see testing/data/array/stride.hpp case16
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[3] = {2,4,3};
        inline int32_t axes[3] = {2,1,0};
        inline auto axes_ct = nmtools_tuple{2_ct,1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int32_t result[3] = {1,3,12};
    }

    // (2,4,3) row-major strides {12,3,1}, transpose(2,0,1) -> {1,12,3}
    // see testing/data/array/stride.hpp case17
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[3] = {2,4,3};
        inline auto shape_ct  = nmtools_tuple{2_ct,4_ct,3_ct};
        inline int32_t axes[3] = {2,0,1};
        inline auto axes_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int32_t result[3] = {1,12,3};
    }

    // default axes (None) reverses the strides
    // (4,8) row-major strides {8,1} -> {1,8}, a col-major layout
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[2] = {4,8};
        inline auto shape_ct = nmtools_tuple{4_ct,8_ct};
        inline auto axes = None;
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int32_t result[2] = {1,8};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_TRANSPOSED_STRIDES_HPP
