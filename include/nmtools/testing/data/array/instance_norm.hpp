#ifndef NMTOOLS_TESTING_DATA_ARRAY_INSTANCE_NORM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_INSTANCE_NORM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, instance_norm)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][5][2][2] = {
            {
                {
                    {0,1},
                    {2,3},
                },
                {
                    {4,5},
                    {6,7},
                },
                {
                    {8,9},
                    {10,11},
                },
                {
                    {12,13},
                    {14,15},
                },
                {
                    {16,17},
                    {18,19},
                },
            }
        };
        inline int weight[5] = {1,1,1,1,1};
        inline int bias[5]   = {0,0,0,0,0};
        inline int axis[2]   = {-2,-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][5][2][2] = {
            {
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[1][5][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
                {6,7},
                {8,9},
            }
        };
        inline int weight[5] = {1,1,1,1,1};
        inline int bias[5]   = {0,0,0,0,0};
        inline int axis[1]   = {-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][5][2] = {
            {
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_INSTANCE_NORM_HPP