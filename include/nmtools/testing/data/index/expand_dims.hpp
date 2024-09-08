#ifndef NMTOOLS_TESTING_DATA_INDEX_EXPAND_DIMS_HPP
#define NMTOOLS_TESTING_DATA_INDEX_EXPAND_DIMS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, shape_expand_dims)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {0};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {1};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{1_ct};
        inline auto axes_cl  = nmtools_tuple{"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[4] = {1,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {3};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{3_ct};
        inline auto axes_cl  = nmtools_tuple{"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int expected[4] = {1,2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {0,1};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct,1_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {0,2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{0_ct,2_ct};
        inline auto axes_cl  = nmtools_tuple{"0:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {1,2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{1_ct,2_ct};
        inline auto axes_cl  = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int expected[5] = {1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[2]  = {2,3};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct,3_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int expected[5] = {1,2,1,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[3]  = {2,3,0};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{2_ct,3_ct,0_ct};
        inline auto axes_cl  = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"0:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int expected[6] = {1,1,1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {-4};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{"-4"_ct};
        inline auto axes_cl  = nmtools_tuple{"-4:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {-3};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{"-3"_ct};
        inline auto axes_cl  = nmtools_tuple{"-3:[1]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int expected[4] = {1,1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {-2};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{"-2"_ct};
        inline auto axes_cl  = nmtools_tuple{"-2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int expected[4] = {1,2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int shape[3] = {1,2,3};
        inline int axes[1]  = {-1};
        inline auto shape_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct};
        inline auto axes_ct  = nmtools_tuple{"-1"_ct};
        inline auto axes_cl  = nmtools_tuple{"-1:[3]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(axes);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int expected[4] = {1,2,3,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_EXPAND_DIMS_HPP