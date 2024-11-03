#ifndef NMTOOLS_TESTING_DATA_ARRAY_PAIRWISE_DISTANCE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_PAIRWISE_DISTANCE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,pairwise_distance)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
        inline int b[12] = {12,13,14,15,16,17,18,19,20,21,22,23};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline float result = 41.569218;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[4] = {0,1,2,3};
        inline int b[2][4] = {
            {4,5, 6, 7},
            {8,9,10,11},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline float result[2] = {7.999998, 15.999998};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
        inline int b[12] = {12,13,14,15,16,17,18,19,20,21,22,23};

        inline bool keepdims = true;
        inline auto keepdims_ct = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline float result[1] = {41.569218};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int a[4] = {0,1,2,3};
        inline int b[2][4] = {
            {4,5, 6, 7},
            {8,9,10,11},
        };

        inline bool keepdims = true;
        inline auto keepdims_ct = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline float result[2][1] = {
            {7.999998}, {15.999998}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[3][4] = {
            {12,13,14,15},
            {16,17,18,19},
            {20,21,22,23},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline float result[3] = {23.999998, 23.999998, 23.999998};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[4] = {12,13,14,15};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline float result[3] = {23.999998, 15.999998, 7.999998};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[1][4] = {
            {12,13,14,15},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline float result[3] = {23.999998, 15.999998, 7.999998};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[2][1][4] = {
            {
                {12,13,14,15},
            },
            {
                {16,17,18,19},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline float result[2][3] = {
            {23.999998, 15.999998,  7.999998},
            {31.999998, 23.999998, 15.999998},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[4] = {12,13,14,15};

        inline auto keepdims = true;
        inline auto keepdims_ct = True;

        inline auto ord = 1;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline float result[3][1] = {
            {47.999996},
            {31.999996},
            {15.999996},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int a[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int b[2][1][4] = {
            {
                {12,13,14,15},
            },
            {
                {16,17,18,19},
            },
        };

        inline auto ord = 1;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline float result[2][3] = {
            {47.999996, 31.999996, 15.999996},
            {63.999996, 47.999996, 31.999996},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_PAIRWISE_DISTANCE_HPP