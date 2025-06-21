#ifndef NMTOOLS_TESTING_DATA_INDEX_REPEAT_HPP
#define NMTOOLS_TESTING_DATA_INDEX_REPEAT_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2] = {2,2};
        inline int repeats  = 3;
        inline auto axis    = None;
        inline auto shape_ct   = nmtools_tuple{2_ct,2_ct};
        inline auto repeats_ct = 3_ct;
        inline auto shape_cl   = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[1] = {12};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {2,2};
        inline int repeats  = 3;
        inline auto axis    = 0;
        inline auto shape_ct   = nmtools_tuple{2_ct,2_ct};
        inline auto repeats_ct = 3_ct;
        inline auto axis_ct    = 0_ct;
        inline auto shape_cl   = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {6,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2] = {2,2};
        inline int repeats  = 3;
        inline auto axis    = 1;
        inline auto shape_ct   = nmtools_tuple{2_ct,2_ct};
        inline auto repeats_ct = 3_ct;
        inline auto axis_ct    = 1_ct;
        inline auto shape_cl   = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2]   = {2,2};
        inline int repeats[2] = {1,2};
        inline auto axis    = 1;
        inline auto shape_ct   = nmtools_tuple{2_ct,2_ct};
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = 1_ct;
        inline auto shape_cl   = to_clipped(shape_ct);
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[2]   = {2,2};
        inline int repeats[2] = {1,2};
        inline auto axis    = 0;
        inline auto shape_ct   = nmtools_tuple{2_ct,2_ct};
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = 0_ct;
        inline auto shape_cl   = to_clipped(shape_ct);
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {3,2};
    }
}


NMTOOLS_TESTING_DECLARE_CASE(constexpr_shape_repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[2] = {2,2};
        constexpr inline int repeats  = 3;
        constexpr inline auto axis    = None;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int shape[1] = {12};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[2] = {2,2};
        constexpr inline int repeats  = 3;
        constexpr inline auto axis    = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int shape[2] = {6,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[2] = {2,2};
        constexpr inline int repeats  = 3;
        constexpr inline auto axis    = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int shape[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[2]   = {2,2};
        constexpr inline int repeats[2] = {1,2};
        constexpr inline auto axis      = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(repeats)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[2]   = {2,2};
        constexpr inline int repeats[2] = {1,2};
        constexpr inline auto axis      = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(repeats)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int shape[2] = {3,2};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[2] = {2,2};
        inline int indices  = 7;
        inline int repeats  = 2;
        inline auto axis = None;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[2] = {2,2};
        inline int indices  = 6;
        inline int repeats  = 2;
        inline auto axis = None;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[2] = {2,2};
        inline int indices  = 5;
        inline int repeats  = 2;
        inline auto axis = None;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {5,0};
        inline int repeats  = 3;
        inline auto axis    = 0;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {5,1};
        inline int repeats  = 3;
        inline auto axis    = 0;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {2,0};
        inline int repeats[2] = {1,2};
        inline auto axis    = 0;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {1,0};
        inline int repeats[2] = {1,2};
        inline auto axis    = 0;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {0,0};
        inline int repeats[2] = {1,2};
        inline auto axis    = 0;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {0,0};
        inline int repeats[2] = {1,2};
        inline auto axis    = 1;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {0,1};
        inline int repeats[2] = {1,2};
        inline auto axis    = 1;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[2]   = {2,2};
        inline int indices[2] = {1,2};
        inline int repeats[2] = {1,2};
        inline auto axis    = 1;
        inline auto shape_ct = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto repeats_ct = nmtools_tuple{1_ct,2_ct};
        inline auto repeats_cl = to_clipped(repeats_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[2] = {1,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_REPEAT_HPP