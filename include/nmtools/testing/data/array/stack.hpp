#ifndef NMTOOLS_TESTING_DATA_ARRAY_STACK_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_STACK_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(stack)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3] = {1,2,3};
        inline int b[3] = {4,5,6};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][3] = {
            {1,2,3},
            {4,5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3] = {1,2,3};
        inline int b[3] = {4,5,6};
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][2] = {
            {1,4},
            {2,5},
            {3,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        inline int b[2][3] = {
            { 7, 8, 9},
            {10,11,12},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2][3] = {
            {
                {1,2,3},
                {4,5,6},
            },
            {
                { 7, 8, 9},
                {10,11,12},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        inline int b[2][3] = {
            { 7, 8, 9},
            {10,11,12},
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][2][3] = {
            {
                {1,2,3},
                {7,8,9},
            },
            {
                { 4, 5, 6},
                {10,11,12},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        inline int b[2][3] = {
            { 7, 8, 9},
            {10,11,12},
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2][3][2] = {
            {
                {1,7},
                {2,8},
                {3,9},
            },
            {
                {4,10},
                {5,11},
                {6,12},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_STACK_HPP