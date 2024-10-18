#ifndef NMTOOLS_TESTING_DATA_ARRAY_INNER_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_INNER_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,inner)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[6] = {6,7,8,9,10,11};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 145;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[2][6] = {
            { 6, 7, 8, 9,10,11},
            {12,13,14,15,16,17},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[2] = {145,235};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[2][1][6] = {
            {
                {6,7,8,9,10,11},
            },
            {
                {12,13,14,15,16,17},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[2][1] = {
            {145},
            {235},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][3] = {
            { 86,110,134},
            {302,390,478},
            {518,670,822},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int b[2][2][3] = {
            {
                {12,13,14},
                {15,16,17},
            },
            {
                {18,19,20},
                {21,22,23},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[4][2][2] = {
            {
                {41,50},
                {59,68},
            },
            {
                {158,194},
                {230,266},
            },
            {
                {275,338},
                {401,464},
            },
            {
                {392,482},
                {572,662},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int b[3] = {12,13,14};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[4] = {41,158,275,392};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int b[2][1][2][3] = {
            {
                {
                    {12,13,14},
                    {15,16,17},
                }
            },
            {
                {
                    {18,19,20},
                    {21,22,23},
                }
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[4][2][1][2] = {
            {
                {
                    {41,50},
                },
                {
                    {59,68},
                },
            },
            {
                {
                    {158,194},
                },
                {
                    {230,266},
                }
            },
            {
                {
                    {275,338},
                },
                {
                    {401,464},
                }
            },
            {
                {
                    {392,482},
                },
                {
                    {572,662},
                }
            },
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
            },
        };
        inline int b[3][2][2] = {
            {
                {12,13},
                {14,15},
            },
            {
                {16,17},
                {18,19},
            },
            {
                {20,21},
                {22,23},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][3][2] = {
            {
                {
                    {13,15},
                    {17,19},
                    {21,23},
                },
                {
                    { 63, 73},
                    { 83, 93},
                    {103,113},
                },
                {
                    {113,131},
                    {149,167},
                    {185,203},
                },
            },
            {
                {
                    {163,189},
                    {215,241},
                    {267,293},
                },
                {
                    {213,247},
                    {281,315},
                    {349,383},
                },
                {
                    {263,305},
                    {347,389},
                    {431,473},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
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
            },
        };
        inline int b[6][2] = {
            {12,13},
            {14,15},
            {16,17},
            {18,19},
            {20,21},
            {22,23},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2][3][6] = {
            {
                { 13, 15, 17, 19, 21 ,23},
                { 63, 73, 83, 93,103,113},
                {113,131,149,167,185,203},
            },
            {
                {163,189,215,241,267,293},
                {213,247,281,315,349,383},
                {263,305,347,389,431,473},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
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
            },
        };
        inline int b[2] = {12,13};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][3] = {
            { 13, 63,113},
            {163,213,263},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
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
            },
        };
        inline int b[1][3][2][2] = {
            {
                {
                    {12,13},
                    {14,15},
                },
                {
                    {16,17},
                    {18,19},
                },
                {
                    {20,21},
                    {22,23},
                },
            }
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[2][3][1][3][2] = {
            {
                {
                    {
                        {13,15},
                        {17,19},
                        {21,23},
                    }
                },
                {
                    {
                        { 63, 73},
                        { 83, 93},
                        {103,113},
                    }
                },
                {
                    {
                        {113,131},
                        {149,167},
                        {185,203},
                    }
                },
            },
            {
                {
                    {
                        {163,189},
                        {215,241},
                        {267,293},
                    }
                },
                {
                    {
                        {213,247},
                        {281,315},
                        {349,383},
                    }
                },
                {
                    {
                        {263,305},
                        {347,389},
                        {431,473},
                    }
                },
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_INNER_HPP