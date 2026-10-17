#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_COL_MAJOR_STRIDES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_COL_MAJOR_STRIDES_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(compute_col_major_strides)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[1] = {3};
        inline auto shape_ct = nmtools_tuple{3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int32_t result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[2] = {3,2};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct};
        inline auto shape_mx1 = nmtools_tuple{3,2_ct};
        inline auto shape_mx2 = nmtools_tuple{3_ct,2};
        inline auto shape_nl1 = nmtools_array{null_int(),null_int(2)};
        inline auto shape_nl2 = nmtools_array{null_int(3),null_int()};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // col-major: stride[k] = product of shape[0..k-1]
        inline int32_t result[2] = {1,3};
        inline auto result_nl1 = nmtools_array{null_int(1),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(1),null_int(3)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[3] = {3,2,1};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct,1_ct};
        inline auto shape_nl1 = nmtools_array{null_int(),null_int(2),null_int(1)};
        inline auto shape_nl2 = nmtools_array{null_int(3),null_int(),null_int(1)};
        inline auto shape_mx1 = nmtools_tuple{3,2_ct,1_ct};
        inline auto shape_mx2 = nmtools_tuple{3_ct,2,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int32_t result[3] = {1,3,6};
        inline auto result_nl1 = nmtools_array{null_int(1),null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(1),null_int(3),null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[3] = {3,2,3};
        inline auto shape_ct  = nmtools_tuple{3_ct,2_ct,3_ct};
        inline auto shape_nl1 = nmtools_array{null_int(),null_int(2),null_int(3)};
        inline auto shape_nl2 = nmtools_array{null_int(3),null_int(),null_int(3)};
        inline auto shape_mx1 = nmtools_tuple{3,2_ct,3_ct};
        inline auto shape_mx2 = nmtools_tuple{3_ct,2,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int32_t result[3] = {1,3,6};
        inline auto result_nl1 = nmtools_array{null_int(1),null_int(),null_int()};
        inline auto result_nl2 = nmtools_array{null_int(1),null_int(3),null_int()};
    }

    // leading ones; row-major and col-major coincide only when all but
    // one axis are one
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int32_t shape[3] = {1,1,12};
        inline auto shape_ct  = nmtools_tuple{1_ct,1_ct,12_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int32_t result[3] = {1,1,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_COL_MAJOR_STRIDES_HPP
