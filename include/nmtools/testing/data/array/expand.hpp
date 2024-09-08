#ifndef NMTOOLS_TESTING_DATA_ARRAY_EXPAND_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_EXPAND_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

// https://en.wikipedia.org/wiki/Expansion_of_the_universe
NMTOOLS_TESTING_DECLARE_CASE(array,expand)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[5][3] = {
            { 0, 1, 2},
            { 3, 4, 5},
            { 6, 7, 8},
            { 9,10,11},
            {12,13,14},
        };
        // defaults:
        // inline auto axis = None;   // same as axis=[0,1]
        inline int axis[2] = {0,1};
        inline int spacing = 1;   // will be spacing=[1,1]
        inline int fill_value = 0; // should be same as input element_type

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[9][5] = {
            { 0, 0, 1, 0, 2},
            { 0, 0, 0, 0, 0},
            { 3, 0, 4, 0, 5},
            { 0, 0, 0, 0, 0},
            { 6, 0, 7, 0, 8},
            { 0, 0, 0, 0, 0},
            { 9, 0,10, 0,11},
            { 0, 0, 0, 0, 0},
            {12, 0,13, 0,14},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[5][3] = {
            {1,1,1},
            {1,1,1},
            {1,1,1},
            {1,1,1},
            {1,1,1},
        };
        inline int axis[2] = {0,1};
        inline int spacing[2] = {1,2};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(spacing)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[9][7] = {
            {1,0,0,1,0,0,1},
            {0,0,0,0,0,0,0},
            {1,0,0,1,0,0,1},
            {0,0,0,0,0,0,0},
            {1,0,0,1,0,0,1},
            {0,0,0,0,0,0,0},
            {1,0,0,1,0,0,1},
            {0,0,0,0,0,0,0},
            {1,0,0,1,0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int input[5][3] = {
            {1,1,1},
            {1,1,1},
            {1,1,1},
            {1,1,1},
            {1,1,1},
        };
        inline auto axis = 0;

        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[9][3] = {
            {1,1,1},
            {0,0,0},
            {1,1,1},
            {0,0,0},
            {1,1,1},
            {0,0,0},
            {1,1,1},
            {0,0,0},
            {1,1,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int input[5][3] = {
            { 1, 2, 3},
            { 4, 5, 6},
            { 7, 8, 9},
            {10,11,12},
            {13,14,15},
        };
        // defaults:
        inline int axis[1] = {-1};
        inline int spacing = 1;
        inline int fill_value = -1;

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[5][5] = {
            { 1,-1, 2,-1, 3},
            { 4,-1, 5,-1, 6},
            { 7,-1, 8,-1, 9},
            {10,-1,11,-1,12},
            {13,-1,14,-1,15},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[6] = {0,1,2,3,4,5};
        inline int axis = 0;

        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[11] = {0,0,1,0,2,0,3,0,4,0,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int input[11] = {1,2,3,4,5,6,7,8,9,10,11};
        inline int axis     = -1;
        inline int spacing = 2;

        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[31] = {1,0,0,2,0,0,3,0,0,4,0,0,5,0,0,6,0,0,7,0,0,8,0,0,9,0,0,10,0,0,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int input[3][2][3] = {
            {
                { 0, 1, 2},
                { 3, 4, 5},
            },
            {
                { 6, 7, 8},
                { 9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
            },
        };
        inline int axis[3] = {0,1,2};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[5][3][5] = {
            {
                { 0, 0, 1, 0, 2},
                { 0, 0, 0, 0, 0},
                { 3, 0, 4, 0, 5},
            },
            {
                { 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0},
            },
            {
                { 6, 0, 7, 0, 8},
                { 0, 0, 0, 0, 0},
                { 9, 0,10, 0,11},
            },
            {
                { 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0},
                { 0, 0, 0, 0, 0},
            },
            {
                {12, 0,13, 0,14},
                { 0, 0, 0, 0, 0},
                {15, 0,16, 0,17},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int input[3][2][3] = {
            {
                { 0, 1, 2},
                { 3, 4, 5},
            },
            {
                { 6, 7, 8},
                { 9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
            },
        };
        inline int axis[2] = {-1,-2};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3][3][5] = {
            {
                { 0, 0, 1, 0, 2},
                { 0, 0, 0, 0, 0},
                { 3, 0, 4, 0, 5},
            },
            {
                { 6, 0, 7, 0, 8},
                { 0, 0, 0, 0, 0},
                { 9, 0,10, 0,11},
            },
            {
                {12, 0,13, 0,14},
                { 0, 0, 0, 0, 0},
                {15, 0,16, 0,17},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_EXPAND_HPP