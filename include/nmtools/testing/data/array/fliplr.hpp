#ifndef NMTOOLS_TESTING_DATA_ARRAY_FLIPLR_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FLIPLR_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(fliplr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][3] = {
            {2,1,0},
            {5,4,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
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
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][3][2] = {
            {
                {4,5},
                {2,3},
                {0,1},
            },
            {
                {10,11},
                { 8, 9},
                { 6, 7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                    { 8, 9},
                    {10,11},
                }
            }
        };
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                    { 8, 9},
                    {10,11},
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FLIPLR_HPP