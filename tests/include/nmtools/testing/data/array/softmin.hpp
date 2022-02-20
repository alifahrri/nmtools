#ifndef NMTOOLS_TESTING_DATA_ARRAY_SOFTMIN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SOFTMIN_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, softmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[5] = {1,1,1,1,1};
        inline int dim = 0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[5] = {0.2,0.2,0.2,0.2,0.2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int dim = 0;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][5] = {
            {0.9933072, 0.9933072, 0.9933072, 0.9933072, 0.9933072},
            {0.0066929, 0.0066929, 0.0066929, 0.0066929, 0.0066929},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int input[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int dim = 1;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[2][5] = {
            {0.6364086, 0.2341217, 0.0861285, 0.0316849, 0.0116562},
            {0.6364086, 0.2341217, 0.0861285, 0.0316849, 0.0116562}
        };
    }

    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int input[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int dim = 0_ct;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[2][5] = {
            {0.9933072, 0.9933072, 0.9933072, 0.9933072, 0.9933072},
            {0.0066929, 0.0066929, 0.0066929, 0.0066929, 0.0066929},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int dim = 1_ct;
        NMTOOLS_CAST_ARRAYS(input)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[2][5] = {
            {0.6364086, 0.2341217, 0.0861285, 0.0316849, 0.0116562},
            {0.6364086, 0.2341217, 0.0861285, 0.0316849, 0.0116562}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SOFTMIN_HPP