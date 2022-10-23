#ifndef NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4][4] = {
            { 20,  23,  26,  29},
            { 56,  68,  80,  92},
            { 92, 113, 134, 155},
            {128, 158, 188, 218},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[3][4] = {
            {0, 1,  2,  3},
            {4, 5,  6,  7},
            {8, 9, 10, 11},
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][3] = {
            { 42,  48,  54},
            {114, 136, 158},
            {186, 224, 262},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[1][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            }
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][4][4] = {
            {
                { 20,  23,  26,  29},
                { 56,  68,  80,  92},
                { 92, 113, 134, 155},
                {128, 158, 188, 218},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[1][3][4] = {
            {
                {0, 1,  2,  3},
                {4, 5,  6,  7},
                {8, 9, 10, 11},
            }
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][3][3] = {
            {
                { 42,  48,  54},
                {114, 136, 158},
                {186, 224, 262},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lhs[2][3][2] = {
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
        inline int rhs[1][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            }
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][2][3][3] = {
            {
                {
                    { 3, 4, 5},
                    { 9,14,19},
                    {15,24,33},
                },
                {
                    {21,34,47},
                    {27,44,61},
                    {33,54,75},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lhs[3][2][1][2] = {
            {
                {{0,1}},
                {{2,3}},
            },
            {
                {{4,5}},
                {{6,7}},
            },
            {
                {{ 8, 9}},
                {{10,11}},
            },
        };
        inline int rhs[3][2][2][1] = {
            {
                {
                    {0},
                    {1},
                },
                {
                    {2},
                    {3},
                },
            },
            {
                {
                    {4},
                    {5},
                },
                {
                    {6},
                    {7},
                },
            },
            {
                {
                    {8},
                    {9},
                },
                {
                    {10},
                    {11},
                },
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][2][1][1] = {
            {
                {{1}},
                {{13}},
            },
            {
                {{41}},
                {{85}},
            },
            {
                {{145}},
                {{221}},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP