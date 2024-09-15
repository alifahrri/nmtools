#ifndef NMTOOLS_TESTING_DATA_ARRAY_DIAGFLAT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DIAGFLAT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,diagflat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int v[2][2] = {
            {0,1},
            {2,3},
        };
        // inline int k = 0;
        NMTOOLS_CAST_ARRAYS(v)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4][4] = {
            {0,0,0,0},
            {0,1,0,0},
            {0,0,2,0},
            {0,0,0,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int v[3] = {1,2,3};
        inline int k = 1;
        NMTOOLS_CAST_ARRAYS(v)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4][4] = {
            {0,1,0,0},
            {0,0,2,0},
            {0,0,0,3},
            {0,0,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int v[3] = {1,2,3};
        inline int k = -1;
        NMTOOLS_CAST_ARRAYS(v)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4][4] = {
            {0,0,0,0},
            {1,0,0,0},
            {0,2,0,0},
            {0,0,3,0},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DIAGFLAT_HPP