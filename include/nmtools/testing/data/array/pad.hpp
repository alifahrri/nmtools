#ifndef NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

using namespace nm::literals;

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