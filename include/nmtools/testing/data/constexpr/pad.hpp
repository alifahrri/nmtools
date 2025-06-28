#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_PAD_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_PAD_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        constexpr inline int pads[4] = {0,2,0,0};
        constexpr inline auto pads_ct = nmtools_tuple{0_ct,2_ct,0_ct,0_ct};
        constexpr inline auto pads_cl = to_clipped(pads_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[3][4] = {
            {0,0,0,1},
            {0,0,2,3},
            {0,0,4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        constexpr inline int pads[4] = {0,2,0,2};
        constexpr inline auto pads_ct = nmtools_tuple{0_ct,2_ct,0_ct,2_ct};
        constexpr inline auto pads_cl = to_clipped(pads_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int result[3][6] = {
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        constexpr inline int pads[4] = {1,2,0,2};
        constexpr inline auto pads_ct = nmtools_tuple{1_ct,2_ct,0_ct,2_ct};
        constexpr inline auto pads_cl = to_clipped(pads_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int result[4][6] = {
            {0,0,0,0,0,0},
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        constexpr inline int pads[4] = {1,2,3,2};
        constexpr inline auto pads_ct = nmtools_tuple{1_ct,2_ct,3_ct,2_ct};
        constexpr inline auto pads_cl = to_clipped(pads_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int result[7][6] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int pads[6] = {0,1,1,2,0,1};
        constexpr inline auto pads_ct = nmtools_tuple{0_ct,1_ct,1_ct,2_ct,0_ct,1_ct};
        constexpr inline auto pads_cl = to_clipped(pads_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int result[4][4][4] = {{{ 0,  0,  0,  0},
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

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_PAD_HPP