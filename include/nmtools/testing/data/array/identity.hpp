#ifndef NMTOOLS_TESTING_DATA_ARRAY_IDENTITY_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_IDENTITY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,identity)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int n = 3;
        // inline auto dtype = float32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3][3] = {
            {1,0,0},
            {0,1,0},
            {0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int n = 4;
        // inline auto dtype = float32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int n = 4;
        inline auto dtype = int8;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_IDENTITY_HPP