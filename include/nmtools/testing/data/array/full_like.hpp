#ifndef NMTOOLS_TESTING_DATA_ARRAY_FULL_LIKE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FULL_LIKE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,full_like)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int fill_value = 3;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][3] = {
            {3,3,3},
            {3,3,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0.,1.},
                {2.,3.},
                {4.,5.},
            },
            {
                { 6., 7.},
                { 8., 9.},
                {10.,11.},
            }
        };
        inline int fill_value = 9;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][2] = {
            {
                {9.,9.},
                {9.,9.},
                {9.,9.},
            },
            {
                {9.,9.},
                {9.,9.},
                {9.,9.},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {0.,1.},
                {2.,3.},
                {4.,5.},
            },
            {
                { 6., 7.},
                { 8., 9.},
                {10.,11.},
            }
        };
        inline float fill_value = 7.;
        inline auto dtype = int8;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][2] = {
            {
                {7,7},
                {7,7},
                {7,7},
            },
            {
                {7,7},
                {7,7},
                {7,7},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FULL_LIKE_HPP