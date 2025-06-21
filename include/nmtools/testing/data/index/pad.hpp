#ifndef NMTOOLS_TESTING_DATA_INDEX_PAD_HPP
#define NMTOOLS_TESTING_DATA_INDEX_PAD_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(index, parse_pad_width)
{
    // see array pad case1
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int pad_width[2][2] = {
            {0,0},
            {2,0},
        };
        NMTOOLS_CAST_ARRAYS(pad_width)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int pads[4] = {0,2,0,0};
    }

    // see array pad case2
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int pad_width[2][2] = {
            {0,0},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(pad_width)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int pads[4] = {0,2,0,2};
    }

    // see array pad case3
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int pad_width[2][2] = {
            {1,0},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(pad_width)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int pads[4] = {1,2,0,2};
    }

    // see array pad case4
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int pad_width[2][2] = {
            {1,3},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(pad_width)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int pads[4] = {1,2,3,2};
    }

    // see array pad case5
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int pad_width[3][2] = {
            {0,2},
            {1,0},
            {1,1},
        };
        NMTOOLS_CAST_ARRAYS(pad_width)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int pads[6] = {0,1,1,2,0,1};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, parse_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int pad[4] = {2,0,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(pad)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(pad)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4] = {0,2,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int pad[4] = {2,2,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(pad)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4] = {0,2,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int pad[4] = {2,2,0,1};
        NMTOOLS_CAST_INDEX_ARRAYS(pad)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,2,0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int pad[4] = {2,2,1,3};
        NMTOOLS_CAST_INDEX_ARRAYS(pad)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int pad[6] = {1,1,1,0,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(pad)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[6] = {0,1,1,2,0,1};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, shape_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2] = {3,2};
        inline int pads[4] = {0,2,0,0};
        inline auto shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto pads_ct = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {3,2};
        inline int pads[4] = {0,2,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2] = {3,2};
        inline int pads[4] = {1,2,0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {4,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2] = {3,2};
        inline int pads[4] = {1,2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {7,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,3,2};
        inline int pads[6] = {1,0,0,1,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {3,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline auto shape = nmtools_tuple{3_ct,2_ct};
        inline auto pads = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
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
        constexpr inline int pads[4] = {0,2,0,0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pads[4] = {0,2,0,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[2] = {3,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pads[4] = {1,2,0,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[2] = {4,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[2] = {3,2};
        constexpr inline int pads[4] = {1,2,3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[2] = {7,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[3] = {1,3,2};
        constexpr inline int pads[6] = {1,0,0,1,0,0};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[3] = {3,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto shape     = nmtools_tuple{3_ct,2_ct};
        constexpr inline auto pads = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
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
        inline int pads[4] = {0,2,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
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
        inline int pads[4] = {0,2,0,0};
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(dst_shape);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {1,1};
    }
} // NMTOOLS_TESTING_DECLARE_CASE(index, pad)

#endif // NMTOOLS_TESTING_DATA_INDEX_PAD_HPP