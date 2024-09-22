#ifndef NMTOOLS_TESTING_DATA_ARRAY_SWAPAXES_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SWAPAXES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,swapaxes)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[1][3] = {
            {1,2,3}
        };
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3][1] = {
            {1},
            {2},
            {3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3][2] = {
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
        inline int axis1 = 0;
        inline int axis2 = 1;

        inline auto axis1_ct = 0_ct;
        inline auto axis2_ct = 1_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][2][2] = {
            {
                {0,1},
                {6,7},
            },
            {
                {2,3},
                {8,9},
            },
            {
                { 4, 5},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
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
        inline int axis1 = 2;
        inline int axis2 = 1;

        inline int axis1_ct = 2_ct;
        inline int axis2_ct = 1_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2][3] = {
            {
                {0,2,4},
                {1,3,5},
            },
            {
                {6,8,10},
                {7,9,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3][1][2] = {
            {
                {
                    {0,1},
                },
                {
                    {2,3},
                },
                {
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                },
                {
                    { 8, 9},
                },
                {
                    {10,11},
                }
            }
        };
        inline int axis1 = -2;
        inline int axis2 = -1;

        inline int axis1_ct = "-2"_ct;
        inline int axis2_ct = "-1"_ct;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][3][2][1] = {
            {
                {
                    {0},
                    {1},
                },
                {
                    {2},
                    {3},
                },
                {
                    {4},
                    {5},
                },
            },
            {
                {
                    {6},
                    {7},
                },
                {
                    {8},
                    {9},
                },
                {
                    {10},
                    {11},
                },
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SWAPAXES_HPP