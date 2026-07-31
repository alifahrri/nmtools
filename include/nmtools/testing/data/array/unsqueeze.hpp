#ifndef NMTOOLS_TESTING_DATA_ARRAY_UNSQUEEZE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_UNSQUEEZE_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(unsqueeze)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[6] = {1,2,3,4,5,6};
        inline int axis = 0;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][6] = {
            {1,2,3,4,5,6}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[6] = {1,2,3,4,5,6};
        inline int axis = 1;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[3][4] = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
        };
        inline int axis = 0;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][3][4] = {
            {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[3][4] = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
        };
        inline int axis = 1;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[3][1][4] = {
            {{1,2,3,4}},
            {{5,6,7,8}},
            {{9,10,11,12}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[3][4] = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
        };
        inline int axis = 2;
        inline auto axis_ct = 2_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3][4][1] = {
            {{1},{2},{3},{4}},
            {{5},{6},{7},{8}},
            {{9},{10},{11},{12}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[2][3][4] = {
            {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
            },
            {
                {13,14,15,16},
                {17,18,19,20},
                {21,22,23,24},
            }
        };
        inline int axis = 0;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[1][2][3][4] = {
            {
                {
                    {1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12},
                },
                {
                    {13,14,15,16},
                    {17,18,19,20},
                    {21,22,23,24},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int array[2][3][4] = {
            {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
            },
            {
                {13,14,15,16},
                {17,18,19,20},
                {21,22,23,24},
            }
        };
        inline int axis = 1;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[2][1][3][4] = {
            {
                {
                    {1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12},
                }
            },
            {
                {
                    {13,14,15,16},
                    {17,18,19,20},
                    {21,22,23,24},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int array[2][3][4] = {
            {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
            },
            {
                {13,14,15,16},
                {17,18,19,20},
                {21,22,23,24},
            }
        };
        inline int axis = 2;
        inline auto axis_ct = 2_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][3][1][4] = {
            {
                {{1,2,3,4}},
                {{5,6,7,8}},
                {{9,10,11,12}},
            },
            {
                {{13,14,15,16}},
                {{17,18,19,20}},
                {{21,22,23,24}},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int array[2][3][4] = {
            {
                {1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
            },
            {
                {13,14,15,16},
                {17,18,19,20},
                {21,22,23,24},
            }
        };
        inline int axis = 3;
        inline auto axis_ct = 3_ct;

        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][3][4][1] = {
            {
                {{1},{2},{3},{4}},
                {{5},{6},{7},{8}},
                {{9},{10},{11},{12}},
            },
            {
                {{13},{14},{15},{16}},
                {{17},{18},{19},{20}},
                {{21},{22},{23},{24}},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_UNSQUEEZE_HPP