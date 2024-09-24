#ifndef NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,diagonal)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][2] = {
            {0,1},
            {2,3},
        };
        // inline int offset = 0;
        // inline int axis1 = 0;
        // inline int axis2 = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][2] = {
            {0,1},
            {2,3},
        };
        inline int offset = 1;
        // inline int axis1 = 0;
        // inline int axis2 = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
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
        inline int offset = 0;
        inline int axis1  = 0;
        inline int axis2  = 1;
        
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2] = {
            {0,9},
            {1,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3][2] = {
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
        inline int offset = 0;
        inline int axis1  = 1;
        inline int axis2  = 2;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][2] = {
            {0,3},
            {6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][3][2] = {
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
        inline int offset = 0;
        inline int axis1  = 2;
        inline int axis2  = 0;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3][2] = {
            {0, 7},
            {2, 9},
            {4,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[2][3][2] = {
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
        inline int offset = 0;
        inline int axis1  = -1;
        inline int axis2  = -3;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][2] = {
            {0, 7},
            {2, 9},
            {4,11},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP