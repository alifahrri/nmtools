#ifndef NMTOOLS_TESTING_DATA_ARRAY_COLUMN_STACK_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_COLUMN_STACK_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,column_stack)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3] = {1,2,3};
        inline int b[3] = {2,3,4};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3][2] = {
            {1,2},
            {2,3},
            {3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[3][2] = {
            { 7, 8},
            { 9,10},
            {11,12},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][4] = {
            {0,1, 7, 8},
            {2,3, 9,10},
            {4,5,11,12},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[3][1][2] = {
            {
                {0,1},
            },
            {
                {2,3},
            },
            {
                {4,5},
            }
        };
        inline int b[3][1][2] = {
            {
                {7,8},
            },
            {
                {9,10},
            },
            {
                {11,12},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3][2][2] = {
            {
                {0,1},
                {7,8},
            },
            {
                {2, 3},
                {9,10},
            },
            {
                { 4, 5},
                {11,12},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_COLUMN_STACK_HPP