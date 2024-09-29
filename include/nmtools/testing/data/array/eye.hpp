#ifndef NMTOOLS_TESTING_DATA_ARRAY_EYE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_EYE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,eye)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int N = 3;
        // inline auto M = None;
        // inline int k = 0;
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
        inline int N = 4;
        inline int M = 3;
        // inline int k = 0;
        // inline auto dtype = float32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[4][3] = {
            {1,0,0},
            {0,1,0},
            {0,0,1},
            {0,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int N = 3;
        inline int M = 4;
        // inline int k = 0;
        // inline auto dtype = float32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[3][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int N = 3;
        inline int M = 4;
        inline int k = 1;
        // inline auto dtype = float32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3][4] = {
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int N = 4;
        inline int M = 3;
        inline int k = -1;
        inline auto dtype = int32;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4][3] = {
            {0,0,0},
            {1,0,0},
            {0,1,0},
            {0,0,1},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_EYE_HPP