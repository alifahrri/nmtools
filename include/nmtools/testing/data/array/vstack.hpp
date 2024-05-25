#ifndef NMTOOLS_TESTING_DATA_ARRAY_VSTACK_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_VSTACK_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(vstack)
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
            {4,5,6}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4][3] = {
            { 1, 2, 3},
            { 4, 5, 6},
            { 7, 8, 9},
            {10,11,12},
        };
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
            {
                {1,2},
                {3,4},
                {5,6},
            },
            {
                { 7, 8},
                { 9,10},
                {11,12},
            }
        };
        inline int b[2][3][2] = {
            {
                {13,14},
                {15,16},
                {17,18},
            },
            {
                {19,20},
                {21,22},
                {23,24},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4][3][2] = {
            {
                { 1, 2},
                { 3, 4},
                { 5, 6},
            },
            {
                { 7, 8},
                { 9,10},
                {11,12},
            },
            {
                {13,14},
                {15,16},
                {17,18},
            },
            {
                {19,20},
                {21,22},
                {23,24},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_VSTACK_HPP