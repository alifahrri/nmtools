#ifndef NMTOOLS_TESTING_DATA_ARRAY_VECDOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_VECDOT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,vecdot)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[6] = {6,7,8,9,10,11};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 145;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[6] = {6,7,8,9,10,11};

        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[1] = {145};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[2][6] = {
            { 6, 7, 8, 9,10,11},
            {12,13,14,15,16,17},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[2] = {145,235};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[2][6] = {
            { 6, 7, 8, 9,10,11},
            {12,13,14,15,16,17},
        };

        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result[2][1] = {
            {145},
            {235},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int a[3] = {0,1,2};
        inline int b[2][2][3] = {
            {
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result[2][2] = {
            {23,32},
            {41,50},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int a[3] = {0,1,2};
        inline int b[2][2][3] = {
            {
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
            },
        };
        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline int result[2][2][1] = {
            {
                {23},
                {32},
            },
            {
                {41},
                {50},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][3] = {
            {6, 7, 8},
            {9,10,11},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2] = {23,122};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][3] = {
            {6, 7, 8},
            {9,10,11},
        };

        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2][1] = {
            { 23},
            {122},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = {6,7,8};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2] = {23,86};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = {6,7,8};

        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2][1] = {
            {23},
            {86},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
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

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[2][3] = {
            {1,13,41},
            {7,43,95},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
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

        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[2][3][1] = {
            {
                { 1},
                {13},
                {41},
            },
            {
                { 7},
                {43},
                {95},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
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
        inline int b[2][3][2] = {
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

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[2][3] = {
            { 1, 13, 41},
            {85,145,221},
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
        inline int b[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
        inline auto keepdims = True;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2][3][1] = {
            {
                { 1},
                {13},
                {41},
            },
            {
                { 7},
                {43},
                {95},
            }
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
        inline int b[3][2][1][2] = {
            {
                {
                    {0,1},
                },
                {
                    {2,3},
                },
            },
            {
                {
                    {4,5},
                },
                {
                    {6,7},
                }
            },
            {
                {
                    {8,9},
                },
                {
                    {10,11},
                }
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[3][2][3] = {
            {
                { 1, 3, 5},
                {33,43,53},
            },
            {
                { 5, 23, 41},
                {85,111,137},
            },
            {
                {  9, 43, 77},
                {137,179,221},
            }
        };
    }

}

#endif // NMTOOLS_TESTING_DATA_ARRAY_VECDOT_HPP