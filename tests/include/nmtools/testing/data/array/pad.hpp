#ifndef NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2] = {3,2};
        inline int pad_width[4] = {0,2,0,0};
        inline auto shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto pad_width_ct = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {3,2};
        inline int pad_width[4] = {0,2,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2] = {3,2};
        inline int pad_width[4] = {1,2,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2] = {3,2};
        inline int pad_width[4] = {1,2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {7,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,3,2};
        inline int pad_width[6] = {1,0,0,1,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {3,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline auto shape = nmtools_tuple{3_ct,2_ct};
        inline auto pad_width = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = nmtools_tuple{3_ct,4_ct};
    }
} // NMTOOLS_TESTING_DECLARE_CASE(index, shape_pad)

NMTOOLS_TESTING_DECLARE_CASE(index, constexpr_shape_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pad_width[4] = {0,2,0,0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pad_width[4] = {0,2,0,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[2] = {3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pad_width[4] = {1,2,0,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[2] = {4,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pad_width[4] = {1,2,3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[2] = {7,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[3] = {1,3,2};
        constexpr inline int pad_width[6] = {1,0,0,1,0,0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[3] = {3,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto shape     = nmtools_tuple{3_ct,2_ct};
        constexpr inline auto pad_width = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto result = nmtools_tuple{3_ct,4_ct};
    }
} // NMTOOLS_TESTING_DECLARE_CASE(index, shape_pad)

NMTOOLS_TESTING_DECLARE_CASE(index, pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[2]   = {0,0};
        inline int src_shape[2] = {3,2};
        inline int dst_shape[2] = {3,4};
        inline int pad_width[4] = {0,2,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2]   = {1,3};
        inline int src_shape[2] = {3,2};
        inline int dst_shape[2] = {3,4};
        inline int pad_width[4] = {0,2,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {1,1};
    }
} // NMTOOLS_TESTING_DECLARE_CASE(index, pad)

NMTOOLS_TESTING_DECLARE_CASE(array, pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pad_width[4] = {0,2,0,0};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3][4] = {
            {0,0,0,1},
            {0,0,2,3},
            {0,0,4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pad_width[4] = {0,2,0,2};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][6] = {
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pad_width[4] = {1,2,0,2};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4][6] = {
            {0,0,0,0,0,0},
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pad_width[4] = {1,2,3,2};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[7][6] = {
            {0,0,0,0,0,0},
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int pad_width[6] = {0,1,1,2,0,1};
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pad_width);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4][4][4] = {{{ 0,  0,  0,  0},
        { 0,  0,  1,  0},
        { 0,  2,  3,  0},
        { 0,  4,  5,  0}},

       {{ 0,  0,  0,  0},
        { 0,  6,  7,  0},
        { 0,  8,  9,  0},
        { 0, 10, 11,  0}},

       {{ 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0}},

       {{ 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP