#ifndef NMTOOLS_TESTING_DATA_INDEX_IS_ROW_MAJOR_HPP
#define NMTOOLS_TESTING_DATA_INDEX_IS_ROW_MAJOR_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(is_row_major)
{
    using namespace literals;

    // canonical row-major strides
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {4,1};
        inline constexpr auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline constexpr auto strides_ct = nmtools_tuple{4_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = true;
    }

    // col-major strides are not row-major
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {1,3};
        inline constexpr auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline constexpr auto strides_ct = nmtools_tuple{1_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = false;
    }

    // broadcast zero-stride on a degenerate dim is don't care
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[2] = {1,4};
        inline int32_t strides[2] = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = true;
    }

    // broadcast zero-stride on a real dim is not row-major
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[2] = {2,4};
        inline int32_t strides[2] = {0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = false;
    }

    // padded leading dimension is not row-major
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {5,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = false;
    }

    // unknown stride cannot prove a match
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int32_t shape[2] = {3,4};
        inline auto strides = nmtools_array{null_int(),null_int(1)};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = false;
    }

    // known nullable strides still match
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int32_t shape[2] = {3,4};
        inline auto strides = nmtools_array{null_int(4),null_int(1)};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = true;
    }

    // maybe-wrapped strides propagate to a maybe result
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {4,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = nmtools_maybe<bool>{true};
    }

    // 1d
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int32_t shape[1] = {5};
        inline int32_t strides[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = true;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(is_col_major)
{
    using namespace literals;

    // canonical col-major strides
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {1,3};
        inline constexpr auto shape_ct = nmtools_tuple{3_ct,4_ct};
        inline constexpr auto strides_ct = nmtools_tuple{1_ct,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = true;
    }

    // row-major strides are not col-major
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {4,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = false;
    }

    // zero-stride on a degenerate dim is don't care
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[2] = {4,1};
        inline int32_t strides[2] = {1,0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = true;
    }

    // padded col-major with gaps is not dense col-major
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[2] = {3,4};
        inline int32_t strides[2] = {1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(strides)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = false;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_IS_ROW_MAJOR_HPP
