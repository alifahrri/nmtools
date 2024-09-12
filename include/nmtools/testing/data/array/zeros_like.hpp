#ifndef NMTOOLS_TESTING_DATA_ARRAY_ZEROS_LIKE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ZEROS_LIKE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,zeros_like)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][3] = {
            {0,0,0},
            {0,0,0},
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

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][2] = {
            {
                {0.,0.},
                {0.,0.},
                {0.,0.},
            },
            {
                {0.,0.},
                {0.,0.},
                {0.,0.},
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
        inline auto dtype = int8;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][2] = {
            {
                {0,0},
                {0,0},
                {0,0},
            },
            {
                {0,0},
                {0,0},
                {0,0},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ZEROS_LIKE_HPP