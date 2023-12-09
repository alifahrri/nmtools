#ifndef NMTOOLS_TESTING_DATA_INDEX_SLICE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_SLICE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(index, shape_slice)
{
    using nmtools_tuple;
    using namespace nm::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{1,2};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{1,3};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,2};
        inline auto slice2 = tuple{None,-1};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {2,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = 0;
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = tuple{None,-1};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None,-1};
        inline auto slice2 = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None,-1};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{None,None};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{None,2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[2] = {2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{1,None};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{1,None,2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{3,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{3,None,2};
        inline auto slice1 = tuple{1,None,-2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{1,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{2,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{1,None,4};
        inline auto shape_ct = tuple{4_ct,2_ct};
        inline auto shape_cl = tuple{"4:[4]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int result[2] = {4,1};
    }

    // a[...,:]
    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{None,None};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int result[3] = {2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{None,Last};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int result[3] = {2,3,1};
    }

    // a[...,0:-1]
    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{0,Last};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = tuple{0ul,Last};
        inline auto slice1  = Ellipsis;
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int result[3] = {1,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int result[2] = {3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 0;
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 1;
        inline auto shape_ct = tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"1:[1]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int result[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 1;
        inline auto slice2  = 0;
        inline auto shape_ct = tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"1:[1]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        inline auto shape_ct = tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"1:[1]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Last;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        inline auto shape_ct = tuple{2_ct,1_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"1:[1]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int result[2] = {1,3};
    }

    // a[...,0:-1:-1]
    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{0,Last,-1};
        inline auto shape_ct = tuple{2_ct,3_ct,2_ct};
        inline auto shape_cl = tuple{"2:[2]"_ct,"3:[3]"_ct,"2:[2]"_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int result[3] = {2,3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int shape[1]   = {9};
        inline int slice0[2]  = {0,3};
        inline auto shape_ct  = nmtools_tuple{9_ct};
        inline auto slice0_ct = nmtools_tuple{0_ct,3_ct};
        inline auto shape_cl  = to_clipped(shape_ct);
        inline auto slice0_cl = to_clipped(slice0_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(slice0);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int shape[1]   = {9};
        inline int slice0[2]  = {3,6};
        inline auto shape_ct  = nmtools_tuple{9_ct};
        inline auto slice0_ct = nmtools_tuple{3_ct,6_ct};
        inline auto shape_cl  = to_clipped(shape_ct);
        inline auto slice0_cl = to_clipped(slice0_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(slice0);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int result[1] = {3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, shape_dynamic_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using slice_t  = nmtools_array<int,3>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{0,2,1},{0,1,1},{0,2,1}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){0,2,1},(slice_t){0,1,1},(slice_t){0,2,1}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = nmtools_array{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using slice_t  = nmtools_array<int,2>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{0,2},{0,1},{0,2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){0,2},(slice_t){0,1},(slice_t){0,2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = nmtools_array{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{None,2},{None,1},{None,2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){None,2},(slice_t){None,1},(slice_t){None,2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_array{2,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{None,None},{None,None},{None,None}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){None,None},(slice_t){None,None},(slice_t){None,None}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = nmtools_array{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{None,2},{None,2},{None,-1}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){None,2},(slice_t){None,2},(slice_t){None,-1}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = nmtools_array{2,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{None,None,1},{None,None,-1},{None,None,1}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){None,None,1},(slice_t){None,None,-1},(slice_t){None,None,1}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = nmtools_array{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{None,None,2},{None,None,1}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){None,None,2},(slice_t){None,None,1}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = nmtools_array{2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{0,None,-2},{1,None,-2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){0,None,-2},(slice_t){1,None,-2}};
        inline auto slices = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = nmtools_array{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{3,None,-2},{1,None,-2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){3,None,-2},(slice_t){1,None,-2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{3,None,2},{1,None,-2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){3,None,2},(slice_t){1,None,-2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = nmtools_list{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[2] = {4,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{{2,None,-2},{1,None,-2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t){2,None,-2},(slice_t){1,None,-2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using slice_t  = nmtools_either<int,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,None},0,0};
        #else
        inline auto a_slices = a_slices_t{(slice_t)nmtools_tuple{None,None},(slice_t)0,(slice_t)0};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto result = nmtools_array{2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using slice_t  = nmtools_either<int,nmtools_tuple<none_t,int>>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,3>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,2},0,nmtools_tuple{None,-1}};
        #else
        inline auto a_slices = a_slices_t{(slice_t)nmtools_tuple{None,2},(slice_t)0,(slice_t)nmtools_tuple{None,-1}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices  = slices_t{Ellipsis,nmtools_tuple{None,None}};
        #else
        inline auto a_slices = a_slices_t{(slice_t)Ellipsis,(slice_t)nmtools_tuple{None,None}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto result = nmtools_list{2,3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using slice_t  = nmtools_either<int,ellipsis_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,2>;
        inline int shape[3] = {2,3,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{0,Ellipsis};
        #else
        inline auto a_slices = a_slices_t{(slice_t)0,(slice_t)Ellipsis};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto result = nmtools_list{3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{0,0,tuple_t{None,2},tuple_t{None,2}};
        #else
        inline auto a_slices = a_slices_t{(slice_t)0,(slice_t)0,(slice_t)(pack_slice_t)tuple_t{None,2},(slice_t)(pack_slice_t)tuple_t{None,2}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto result = nmtools_array{2,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        #if 0
        inline auto slices = slices_t{0,0,tuple_t{None,2},array_t{0,3}};
        #else
        inline auto a_slices = a_slices_t{(slice_t)0,(slice_t)0,(slice_t)(pack_slice_t)tuple_t{None,2},(slice_t)(pack_slice_t)array_t{0,3}};
        inline auto slices   = to_list(a_slices);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline auto result = nmtools_array{2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto a_slices = a_slices_t{
            (slice_t)0,
            (slice_t)0,
            (slice_t)(pack_slice_t)array_t{0,3},
            (slice_t)(pack_slice_t)tuple_t{None,2}
        };
        inline auto slices = to_list(a_slices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline auto result = nmtools_array{3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<pack_slice_t,index_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto a_slices = a_slices_t{
            (slice_t)0,
            (slice_t)0,
            (slice_t)(pack_slice_t)array_t{0,3},
            (slice_t)(pack_slice_t)tuple_t{None,2}
        };
        inline auto slices = to_list(a_slices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline auto result = nmtools_array{3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using tuple_slice_t = nmtools_either<tuple_t,ellipsis_t>;
        using pack_slice_t  = nmtools_either<array_t,tuple_slice_t>;
        using slice_t  = nmtools_either<pack_slice_t,index_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto a_slices = a_slices_t{
            (slice_t)0,
            (slice_t)0,
            (slice_t)(pack_slice_t)array_t{0,3},
            (slice_t)(pack_slice_t)(tuple_slice_t)tuple_t{None,2}
        };
        inline auto slices = to_list(a_slices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline auto result = nmtools_array{3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using tuple_slice_t = nmtools_either<tuple_t,ellipsis_t>;
        using pack_slice_t  = nmtools_either<array_t,tuple_slice_t>;
        using slice_t  = nmtools_either<pack_slice_t,index_t>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,5>;
        inline int shape[4] = {1,3,5,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto a_slices = a_slices_t{
            (slice_t)(pack_slice_t)(tuple_slice_t)Ellipsis,
            (slice_t)0,
            (slice_t)0,
            (slice_t)(pack_slice_t)array_t{0,3},
            (slice_t)(pack_slice_t)(tuple_slice_t)tuple_t{None,2}
        };
        inline auto slices = to_list(a_slices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline auto result = nmtools_array{3,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        using index_t = int;
        using slice_t = nmtools_array<index_t,2>;
        using slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,1>;
        inline int shape[1] = {9};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        inline auto a_slices = a_slices_t{
            slice_t{0,3}
        };
        inline auto slices = to_list(a_slices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline auto result = nmtools_array{3};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[3] = {0,0,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[3] = {1,2,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {0,0,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{1,2};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int indices[3] = {0,0,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{1,3};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int indices[3] = {1,1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{0,2};
        inline auto slice2 = tuple{None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int indices[1] = {1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int indices[2] = {1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = 0;
        inline auto slice2 = tuple{None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int indices[3] = {0,0,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int indices[3] = {1,2,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int indices[3] = {0,0,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None,-1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3] = {0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int indices[3] = {1,2,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None,-1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int indices[3] = {1,1,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None};
        inline auto slice1 = tuple{None,None,-1};
        inline auto slice2 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[3] = {1,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int indices[3] = {0,0,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{None,None};
        inline auto slice2 = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int indices[3] = {0,0,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{0,1};
        inline auto slice2 = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int indices[3] = {0,0,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{1,None,-1};
        inline auto slice2 = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int indices[3] = {0,1,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0 = tuple{None,None,-1};
        inline auto slice1 = tuple{1,None,-1};
        inline auto slice2 = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int indices[2] = {1,1};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,2};
        inline auto slice1 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int result[2] = {2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int indices[2] = {1,1};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int indices[2] = {0,0};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int result[2] = {3,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int indices[2] = {0,0};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{1,None,2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int indices[2] = {0,0};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{None,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int indices[2] = {0,0};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{3,None,-2};
        inline auto slice1 = tuple{1,None,-2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int indices[2] = {0,0};
        inline int shape[2] = {4,2};
        inline auto slice0 = tuple{3,None,2};
        inline auto slice1 = tuple{1,None,-2};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int result[2] = {3,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int indices[3] = {0,1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{None,None};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int indices[3] = {0,1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{None,Last};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int indices[3] = {0,1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = tuple{0,Last};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int indices[3] = {0,1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = tuple{0ul,Last};
        inline auto slice1  = Ellipsis;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int indices[2] = {1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int result[3] = {0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline int indices[2] = {1,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int result[3] = {0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case30)
    {
        inline int indices[2] = {1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case30)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case31)
    {
        inline int indices[2] = {1,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case31)
    {
        inline int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case32)
    {
        inline int indices[1] = {2};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case32)
    {
        inline int result[3] = {0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case33)
    {
        inline int indices[3] = {0,0,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case33)
    {
        inline int result[4] = {0,0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case34)
    {
        inline int indices[2] = {0,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = 1;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case34)
    {
        inline int result[4] = {0,0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case35)
    {
        inline int indices[2] = {0,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case35)
    {
        inline int result[4] = {1,0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case36)
    {
        inline int indices[2] = {0,2};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case36)
    {
        inline int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case37)
    {
        inline int indices[2] = {1,0};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = -1;
        inline auto slice2  = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case37)
    {
        inline int result[3] = {1,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case38)
    {
        inline int indices[2] = {1,1};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = -2;
        inline auto slice2  = tuple{None,None,-1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case38)
    {
        inline int result[3] = {1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case39)
    {
        inline int indices[1] = {2};
        inline int shape[3] = {2,3,2};
        inline auto slice0  = 0;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case39)
    {
        inline int result[3] = {0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case40)
    {
        inline int indices[3] = {0,0,-1};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = -1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case40)
    {
        inline int result[4] = {0,0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case41)
    {
        inline int indices[2] = {1,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = Ellipsis;
        inline auto slice1  = -1;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case41)
    {
        inline int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case42)
    {
        inline int indices[2] = {0,-1};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = -1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case42)
    {
        inline int result[4] = {1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case43)
    {
        inline int indices[2] = {0,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = tuple{None,None,-1};
        inline auto slice3  = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case43)
    {
        inline int result[4] = {1,0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case44)
    {
        inline int indices[2] = {0,2};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = tuple{None,None,1};
        inline auto slice3  = 1;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        using r_slice_t  = nmtools_either<decltype(slice1),decltype(slice2)>;
        using slice_t    = nmtools_either<int,r_slice_t>;
        using d_slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline auto d_slices = d_slices_t{
            (slice_t)slice0,
            (slice_t)(r_slice_t)slice1,
            (slice_t)(r_slice_t)slice2,
            (slice_t)slice3,
        };
        inline auto a_slices = a_slices_t{
            (slice_t)slice0,
            (slice_t)(r_slice_t)slice1,
            (slice_t)(r_slice_t)slice2,
            (slice_t)slice3,
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case44)
    {
        inline int result[4] = {1,0,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case45)
    {
        inline int indices[2] = {0,0};
        inline int shape[4] = {2,1,3,2};
        inline auto slice0  = 1;
        inline auto slice1  = Ellipsis;
        inline auto slice2  = tuple{None,None,-1};
        inline auto slice3  = 0;
        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(indices);
        using r_slice_t  = nmtools_either<decltype(slice1),decltype(slice2)>;
        using slice_t    = nmtools_either<int,r_slice_t>;
        using d_slices_t = nmtools_list<slice_t>;
        using a_slices_t = nmtools_array<slice_t,4>;
        inline auto d_slices = d_slices_t{
            (slice_t)slice0,
            (slice_t)(r_slice_t)slice1,
            (slice_t)(r_slice_t)slice2,
            (slice_t)slice3,
        };
        inline auto a_slices = a_slices_t{
            (slice_t)slice0,
            (slice_t)(r_slice_t)slice1,
            (slice_t)(r_slice_t)slice2,
            (slice_t)slice3,
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case45)
    {
        inline int result[4] = {1,0,2,0};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(index, dynamic_slice)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        using slice_t  = nmtools_array<int,2>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{0,2},{0,1},{0,2}};
        #else
        inline auto slices  = slices_t{(slice_t){0,2},(slice_t){0,1},(slice_t){0,2}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline auto result = nmtools_list{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using slice_t  = nmtools_tuple<none_t,none_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,2,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{None,None},{None,None},{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t){None,None},(slice_t){None,None},(slice_t){None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline auto result = nmtools_list{1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using slice_t  = nmtools_tuple<none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{None,2},{None,2},{None,-1}};
        #else
        inline auto slices  = slices_t{(slice_t){None,2},(slice_t){None,2},(slice_t){None,-1}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto result = nmtools_list{1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{None,None,-1},{None,None,1},{None,None,1}};
        #else
        inline auto slices  = slices_t{(slice_t){None,None,-1},(slice_t){None,None,1},(slice_t){None,None,1}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        using slice_t  = nmtools_tuple<none_t,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{None,None,1},{None,None,-1},{None,None,1}};
        #else
        inline auto slices  = slices_t{(slice_t){None,None,1},(slice_t){None,None,-1},(slice_t){None,None,1}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        using slice_t  = nmtools_tuple<int,none_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{{0,None,1},{2,None,-1},{0,None,1}};
        #else
        inline auto slices  = slices_t{(slice_t){0,None,1},(slice_t){2,None,-1},(slice_t){0,None,1}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,None},nmtools_tuple{0,1},nmtools_tuple{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{None,None},(slice_t)nmtools_tuple{0,1},(slice_t)nmtools_tuple{None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto result = nmtools_list{0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{1,2},nmtools_tuple{0,1},nmtools_tuple{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{1,2},(slice_t)nmtools_tuple{0,1},(slice_t)nmtools_tuple{None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline auto result = nmtools_list{1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t>,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_array{1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,None},0,0};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{None,None},(slice_t)0,(slice_t)0};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{
            nmtools_tuple{None,None,-1},
            nmtools_tuple{0,1},
            nmtools_tuple{None,None,-1}
        };
        #else
        inline auto slices  = slices_t{
            (slice_t)nmtools_tuple{None,None,-1},
            (slice_t)nmtools_tuple{0,1},
            (slice_t)nmtools_tuple{None,None,-1}
        };
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{4,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,None,2},nmtools_tuple{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{None,None,2},(slice_t)nmtools_tuple{None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline auto result = nmtools_list{2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        using slice_t  = nmtools_either<nmtools_tuple<none_t,none_t,int>,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{4,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{None,None,-2},nmtools_tuple{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{None,None,-2},(slice_t)nmtools_tuple{None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline auto result = nmtools_list{1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{Ellipsis,nmtools_tuple{None,None}};
        #else
        inline auto slices  = slices_t{(slice_t)Ellipsis,(slice_t)nmtools_tuple{None,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<none_t,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{Ellipsis,nmtools_tuple{None,-1}};
        #else
        inline auto slices  = slices_t{(slice_t)Ellipsis,(slice_t)nmtools_tuple{None,-1}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<int,none_t>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{Ellipsis,nmtools_tuple{0,None}};
        #else
        inline auto slices  = slices_t{(slice_t)Ellipsis,(slice_t)nmtools_tuple{0,None}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        using slice_t  = nmtools_either<ellipsis_t,nmtools_tuple<int,int>>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{nmtools_tuple{0,-1},Ellipsis};
        #else
        inline auto slices  = slices_t{(slice_t)nmtools_tuple{0,-1},(slice_t)Ellipsis};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{0,Ellipsis};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)Ellipsis};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline auto result = nmtools_list{0,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,1};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{0,Ellipsis};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)Ellipsis};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline auto result = nmtools_list{0,1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,0};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{Ellipsis,0};
        #else
        inline auto slices  = slices_t{(slice_t)Ellipsis,(slice_t)0};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline auto result = nmtools_list{1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_array{2};
        inline auto shape   = nmtools_list{2,3,2};
        #if 0
        inline auto slices  = slices_t{0,Ellipsis,0};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)Ellipsis,(slice_t)0};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline auto result = nmtools_list{0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,1,3,2};
        #if 0
        inline auto slices  = slices_t{Ellipsis,1};
        #else
        inline auto slices  = slices_t{(slice_t)Ellipsis,(slice_t)1};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline auto result = nmtools_list{0,0,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        using slice_t  = nmtools_either<ellipsis_t,int>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0,0};
        inline auto shape   = nmtools_list{2,1,3,2};
        #if 0
        inline auto slices  = slices_t{1,Ellipsis};
        #else
        inline auto slices  = slices_t{(slice_t)1,(slice_t)Ellipsis};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline auto result = nmtools_list{1,0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0};
        inline auto shape   = nmtools_list{1,3,5,5};
        #if 0
        inline auto slices  = slices_t{0,1,tuple_t{None,2},tuple_t{None,2}};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)1,(slice_t)(pack_slice_t)tuple_t{None,2},(slice_t)(pack_slice_t)tuple_t{None,2}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline auto result = nmtools_list{0,1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,0};
        inline auto shape   = nmtools_list{1,3,5,5};
        #if 0
        inline auto slices  = slices_t{0,1,tuple_t{None,2},array_t{0,3}};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)1,(slice_t)(pack_slice_t)tuple_t{None,2},(slice_t)(pack_slice_t)array_t{0,3}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline auto result = nmtools_list{0,1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using pack_slice_t = nmtools_either<array_t,tuple_t>;
        using slice_t  = nmtools_either<index_t,pack_slice_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{1,0};
        inline auto shape   = nmtools_list{1,3,5,5};
        #if 0
        inline auto slices  = slices_t{0,1,array_t{0,3},tuple_t{None,2}};
        #else
        inline auto slices  = slices_t{(slice_t)0,(slice_t)1,(slice_t)(pack_slice_t)array_t{0,3},(slice_t)(pack_slice_t)tuple_t{None,2}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline auto result = nmtools_list{0,1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        using index_t  = int;
        using array_t  = nmtools_array<int,2>;
        using tuple_t  = nmtools_tuple<none_t,int>;
        using tuple_slice_t = nmtools_either<tuple_t,ellipsis_t>;
        using pack_slice_t  = nmtools_either<array_t,tuple_slice_t>;
        using slice_t  = nmtools_either<pack_slice_t,index_t>;
        using slices_t = nmtools_list<slice_t>;
        inline auto indices = nmtools_list{0,1};
        inline auto shape   = nmtools_list{1,3,5,5};
        // negative index not supported yet
        // TODO: support negative index slice
        #if 0
        inline auto slices  = slices_t{Ellipsis,0,2,array_t{0,3},tuple_t{None,2}};
        #else
        inline auto slices  = slices_t{
            (slice_t)(pack_slice_t)(tuple_slice_t)Ellipsis,
            (slice_t)0,
            (slice_t)2,
            (slice_t)(pack_slice_t)array_t{0,3},
            (slice_t)(pack_slice_t)(tuple_slice_t)tuple_t{None,2}};
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline auto result = nmtools_list{0,2,0,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_SLICE_HPP