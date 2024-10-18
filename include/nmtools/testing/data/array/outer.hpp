#ifndef NMTOOLS_TESTING_DATA_ARRAY_OUTER_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_OUTER_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,outer)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[4] = {0,1,2,3};
        inline int b[4] = {4,5,6,7};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4][4] = {
            { 0, 0, 0, 0},
            { 4, 5, 6, 7},
            { 8,10,12,14},
            {12,15,18,21},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[4] = {0,1,2,3};
        inline int b[2][4] = {
            {4,5, 6, 7},
            {8,9,10,11},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[4][8] = {
            { 0, 0, 0, 0, 0, 0, 0, 0},
            { 4, 5, 6, 7, 8, 9,10,11},
            { 8,10,12,14,16,18,20,22},
            {12,15,18,21,24,27,30,33},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[2] = {0,1};
        inline int b[2][1][3] = {
            {
                {2,3,4},
            },
            {
                {5,6,7},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[2][6] = {
            {0,0,0,0,0,0},
            {2,3,4,5,6,7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][2] = {
            {6,7},
            {8,9},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[6][4] = {
            { 0, 0, 0, 0},
            { 6, 7, 8, 9},
            {12,14,16,18},
            {18,21,24,27},
            {24,28,32,36},
            {30,35,40,45},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[4] = {6,7,8,9};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[6][4] = {
            { 0, 0, 0, 0},
            { 6, 7, 8, 9},
            {12,14,16,18},
            {18,21,24,27},
            {24,28,32,36},
            {30,35,40,45},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][1][2] = {
            {
                {6,7}
            },
            {
                {8,9}
            }
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[6][4] = {
            { 0, 0, 0, 0},
            { 6, 7, 8, 9},
            {12,14,16,18},
            {18,21,24,27},
            {24,28,32,36},
            {30,35,40,45},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_OUTER_HPP