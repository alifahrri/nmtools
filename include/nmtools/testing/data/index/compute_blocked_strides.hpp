#ifndef NMTOOLS_TESTING_DATA_INDEX_COMPUTE_BLOCKED_STRIDES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_COMPUTE_BLOCKED_STRIDES_HPP

#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(compute_blocked_strides)
{
    using namespace literals;

    // 8x8 blocked into 4x2 tiles, grid row-major, inner column-major
    // -> blocked column major, see testing/data/array/stride.hpp case18
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t shape[2] = {8,8};
        inline int32_t block[2] = {4,2};
        inline constexpr auto shape_ct = nmtools_tuple{8_ct,8_ct};
        inline constexpr auto block_ct = nmtools_tuple{4_ct,2_ct};
        inline constexpr auto grid_order  = nmtools_tuple{1_ct,0_ct};
        inline constexpr auto inner_order = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(block)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = nmtools_tuple{
            nmtools_tuple{32,1}
            ,nmtools_tuple{8,4}
        };
    }

    // same blocking, grid row-major, inner row-major
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t shape[2] = {8,8};
        inline int32_t block[2] = {4,2};
        inline constexpr auto shape_ct = nmtools_tuple{8_ct,8_ct};
        inline constexpr auto block_ct = nmtools_tuple{4_ct,2_ct};
        inline constexpr auto grid_order  = nmtools_tuple{1_ct,0_ct};
        inline constexpr auto inner_order = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(block)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = nmtools_tuple{
            nmtools_tuple{32,2}
            ,nmtools_tuple{8,1}
        };
    }

    // same blocking, grid column-major, inner column-major
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t shape[2] = {8,8};
        inline int32_t block[2] = {4,2};
        inline constexpr auto shape_ct = nmtools_tuple{8_ct,8_ct};
        inline constexpr auto block_ct = nmtools_tuple{4_ct,2_ct};
        inline constexpr auto grid_order  = nmtools_tuple{0_ct,1_ct};
        inline constexpr auto inner_order = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(block)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_tuple{
            nmtools_tuple{8,1}
            ,nmtools_tuple{16,4}
        };
    }

    // same blocking, grid column-major, inner row-major
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t shape[2] = {8,8};
        inline int32_t block[2] = {4,2};
        inline constexpr auto shape_ct = nmtools_tuple{8_ct,8_ct};
        inline constexpr auto block_ct = nmtools_tuple{4_ct,2_ct};
        inline constexpr auto grid_order  = nmtools_tuple{0_ct,1_ct};
        inline constexpr auto inner_order = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(block)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = nmtools_tuple{
            nmtools_tuple{8,2}
            ,nmtools_tuple{16,1}
        };
    }

    // non-square: 6x4 blocked into 3x2 tiles, grid row-major, inner column-major
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int32_t shape[2] = {6,4};
        inline int32_t block[2] = {3,2};
        inline constexpr auto shape_ct = nmtools_tuple{6_ct,4_ct};
        inline constexpr auto block_ct = nmtools_tuple{3_ct,2_ct};
        inline constexpr auto grid_order  = nmtools_tuple{1_ct,0_ct};
        inline constexpr auto inner_order = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(block)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = nmtools_tuple{
            nmtools_tuple{12,1}
            ,nmtools_tuple{6,3}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_COMPUTE_BLOCKED_STRIDES_HPP
