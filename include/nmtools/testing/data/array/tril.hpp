#ifndef NMTOOLS_TESTING_DATA_ARRAY_TRIL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TRIL_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,tril)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9,10,11,12},
        };
        // inline int k = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[3][4] = {
            {1, 0, 0, 0},
            {5, 6, 0, 0},
            {9,10,11, 0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9,10,11,12},
        };
        inline int k = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[3][4] = {
            {1, 2, 0, 0},
            {5, 6, 7, 0},
            {9,10,11,12},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9,10,11,12},
        };
        inline int k = -1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[3][4] = {
            {0, 0,0,0},
            {5, 0,0,0},
            {9,10,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[2][3][3] = {
            {
                {1,2,3},
                {4,5,6},
                {7,8,9},
            },
            {
                {10,11,12},
                {13,14,15},
                {16,17,18},
            }
        };
        // inline int k = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2][3][3] = {
            {
                {1,0,0},
                {4,5,0},
                {7,8,9},
            },
            {
                {10, 0, 0},
                {13,14, 0},
                {16,17,18},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3][3] = {
            {
                {1,2,3},
                {4,5,6},
                {7,8,9},
            },
            {
                {10,11,12},
                {13,14,15},
                {16,17,18},
            }
        };
        inline int k = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2][3][3] = {
            {
                {1,2,0},
                {4,5,6},
                {7,8,9},
            },
            {
                {10,11, 0},
                {13,14,15},
                {16,17,18},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3][3] = {
            {
                {1,2,3},
                {4,5,6},
                {7,8,9},
            },
            {
                {10,11,12},
                {13,14,15},
                {16,17,18},
            }
        };
        inline int k = -1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2][3][3] = {
            {
                {0,0,0},
                {4,0,0},
                {7,8,0},
            },
            {
                { 0, 0,0},
                {13, 0,0},
                {16,17,0},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int a[3] = {1,2,3};
        // inline int k = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3][3] = {
            {1,0,0},
            {1,2,0},
            {1,2,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int a[6] = {1,2,3,4,5,6};
        // inline int k = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[6][6] = {
            {1,0,0,0,0,0},
            {1,2,0,0,0,0},
            {1,2,3,0,0,0},
            {1,2,3,4,0,0},
            {1,2,3,4,5,0},
            {1,2,3,4,5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int a[6] = {1,2,3,4,5,6};
        inline int k = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[6][6] = {
            {1,2,3,0,0,0},
            {1,2,3,4,0,0},
            {1,2,3,4,5,0},
            {1,2,3,4,5,6},
            {1,2,3,4,5,6},
            {1,2,3,4,5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int a[6] = {1,2,3,4,5,6};
        inline int k = -2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[6][6] = {
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {1,0,0,0,0,0},
            {1,2,0,0,0,0},
            {1,2,3,0,0,0},
            {1,2,3,4,0,0},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TRIL_HPP