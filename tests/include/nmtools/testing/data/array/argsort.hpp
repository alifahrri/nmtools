#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARGSORT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARGSORT_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, argsort)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][3][2] = {
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
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][3][2] = {
            {
                {0,0},
                {0,0},
                {0,0},
            },
            {
                {1,1},
                {1,1},
                {1,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        using case1::args::array;
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][3][2] = {
            {
                {0,0},
                {1,1},
                {2,2},
            },
            {
                {0,0},
                {1,1},
                {2,2},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        using case2::args::array;
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {0,1},
                {0,1},
            },
            {
                {0,1},
                {0,1},
                {0,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float array[12] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.};
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float array[12] = {11., 10., 9., 8., 7., 6., 5., 4., 3., 2., 1., 0.};
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[12] = {11,10,9,8,7,6,5,4,3,2,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[2][3][2] = {
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
        inline int axis = -3;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2][3][2] = {
            {
                {0,0},
                {0,0},
                {0,0},
            },
            {
                {1,1},
                {1,1},
                {1,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        using case1::args::array;
        inline int axis = -2;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2][3][2] = {
            {
                {0,0},
                {1,1},
                {2,2},
            },
            {
                {0,0},
                {1,1},
                {2,2},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        using case2::args::array;
        inline int axis = -1;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][3][2] = {
            {
                {0,1},
                {0,1},
                {0,1},
            },
            {
                {0,1},
                {0,1},
                {0,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline float array[12] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.};
        inline int axis = -1;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline float array[12] = {66., 55., 45., 36., 28., 21., 15., 10., 6., 3., 1., 0.};
        inline int axis = -1;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[12] = {11,10,9,8,7,6,5,4,3,2,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARGSORT_HPP