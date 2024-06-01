#ifndef NMTOOLS_TESTING_DATA_INDEX_RESHAPE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_RESHAPE_HPP

#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_reshape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1]     = {12};
        inline int newshape[2]  = {12,1};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{12_ct,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {3,4};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{3_ct,4_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[1]    = {12};
        inline int newshape[4] = {1,2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[2] = {12,1};
        inline int newshape[4] = {2,1,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        inline auto newshape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {12,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{12_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[1]    = {12};
        inline int newshape[2] = {3,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{3_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[1]    = {12};
        inline int newshape[4] = {1,2,-1,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,"-1"_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[2] = {12,1};
        inline int newshape[4] = {-1,1,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        inline auto newshape_ct = nmtools_tuple{"-1"_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[1]     = {12};
        inline int newshape[2]  = {-1,-1};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{"-1"_ct,"-1"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[1]     = {12};
        inline int newshape[2]  = {7,-1};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{7_ct,"-1"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[1]     = {12};
        inline int newshape[4]  = {1,9,-1,2};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{1_ct,9_ct,"-1"_ct,2_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[1]     = {12};
        inline int newshape[2]  = {12,12};
        inline auto shape_ct    = nmtools_tuple{12_ct};
        inline auto newshape_ct = nmtools_tuple{12_ct,12_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto result = meta::Nothing;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_shape_reshape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[1]     = {12};
        constexpr inline int newshape[2]  = {12,1};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{12_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[1]    = {12};
        constexpr inline int newshape[2] = {3,4};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{3_ct,4_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[1]    = {12};
        constexpr inline int newshape[4] = {1,2,3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[2] = {12,1};
        constexpr inline int newshape[4] = {2,1,3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{2_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[1]    = {12};
        constexpr inline int newshape[2] = {12,-1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{12_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[2] = {12,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int shape[1]    = {12};
        constexpr inline int newshape[2] = {3,-1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{3_ct,"-1"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline int result[2] = {3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int shape[1]    = {12};
        constexpr inline int newshape[4] = {1,2,-1,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{1_ct,2_ct,"-1"_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int result[4] = {1,2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int shape[2] = {12,1};
        constexpr inline int newshape[4] = {-1,1,3,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct,1_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{"-1"_ct,1_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline int result[4] = {2,1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline int shape[1]     = {12};
        constexpr inline int newshape[2]  = {-1,-1};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{"-1"_ct,"-1"_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int shape[1]     = {12};
        constexpr inline int newshape[2]  = {7,-1};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{7_ct,"-1"_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline int shape[1]     = {12};
        constexpr inline int newshape[4]  = {1,9,-1,2};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{1_ct,9_ct,"-1"_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto result = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline int shape[1]     = {12};
        constexpr inline int newshape[2]  = {12,12};
        constexpr inline auto shape_ct    = nmtools_tuple{12_ct};
        constexpr inline auto newshape_ct = nmtools_tuple{12_ct,12_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto result = meta::Nothing;
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_RESHAPE_HPP