#ifndef NMTOOLS_TESTING_DATA_ARRAY_LINEAR_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LINEAR_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,linear)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int input[4] = {0,1,2,3};
        inline int weight[4] = {0,1,2,3};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 14;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int input[4] = {0,1,2,3};
        inline int weight[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[3] = {14,38,62};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int input[4] = {0,1,2,3};
        inline int weight[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int bias[3] = {0,1,2};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[3] = {14,39,64};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int input[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int weight[4] = {0,1,2,3};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[3] = {14,38,62};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int input[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int weight[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[3][3] = {
            {14, 38, 62},
            {38,126,214},
            {62,214,366},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int input[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int weight[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int bias = 3;

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[3][3] = {
            {17, 41 ,65},
            {41,129,217},
            {65,217,369},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int input[3][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7},
            },
            {
                {8,9,10,11},
            },
        };
        inline int weight[4] = {0,1,2,3};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[3][1] = {
            {14},
            {38},
            {62},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int input[3][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7},
            },
            {
                {8,9,10,11},
            },
        };
        inline int weight[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[3][1][2] = {
            {
                {14,38},
            },
            {
                {38,126},
            },
            {
                {62,214},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int input[2][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            },
            {
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
        };
        inline int weight[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline int bias[2] = {0,1};

        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][3][2] = {
            {
                {14, 39},
                {38,127},
                {62,215},
            },
            {
                { 86,303},
                {110,391},
                {134,479},
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LINEAR_HPP