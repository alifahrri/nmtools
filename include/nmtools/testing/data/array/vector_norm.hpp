#ifndef NMTOOLS_TESTING_DATA_ARRAY_VECTOR_NORM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_VECTOR_NORM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,vector_norm)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int x[3] = {0,1,2};

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result = 2.23606797749979;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int x[2][3][2] = {
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

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline float result = 22.494443758403985;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int x[2][3][2] = {
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
        inline int axis = 1;

        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline float result[2][2] = {
            {4.47213595,  5.91607978},
            {14.14213562, 15.84297952}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int x[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline int keepdims = True;

        inline auto axis_ct = nmtools_tuple{0_ct,2_ct};

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline float result[1][3][1] = {
            {
                { 9.2736185 },
                {12.56980509},
                {16.18641406},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int x[2][3][2] = {
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
        inline int axis[2] = {-2,-1};
        inline int keepdims = true;
        inline int ord = 1;

        inline auto axis_ct = nmtools_tuple{"-2"_ct, "-1"_ct};

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline float result[2][1][1] = {
            {
                {15}
            },
            {
                {51}
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_VECTOR_NORM_HPP