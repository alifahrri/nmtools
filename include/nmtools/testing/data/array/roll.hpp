#ifndef NMTOOLS_TESTING_DATA_ARRAY_ROLL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ROLL_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(roll)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int array[6] = {1,2,3,4,5,6};
        inline int shift = 1;
        inline auto shift_ct = 1_ct;
        inline auto shift_cl = to_clipped(shift_ct);
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[6] = {6,1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int array[6] = {1,2,3,4,5,6};
        inline int shift = 2;
        inline auto shift_ct = 2_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[6] = {5,6,1,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int array[6] = {1,2,3,4,5,6};
        inline int shift = -2;
        inline auto shift_ct = "-2"_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[6] = {3,4,5,6,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline auto shift = 1;
        inline auto shift_ct = 1_ct;
        inline auto shift_cl = to_clipped(shift_ct);
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2][4] = {
            {7,0,1,2},
            {3,4,5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline auto shift = -2;
        inline auto shift_ct = "-2"_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2][4] = {
            {2,3,4,5},
            {6,7,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline auto shift = 1;
        inline auto axis  = 0;
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;
        inline auto shift_cl = to_clipped(shift_ct);
        inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2][4] = {
            {4,5,6,7},
            {0,1,2,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline auto shift = 1;
        inline int axis[2] = {1,0};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        inline auto shift_cl = to_clipped(shift_ct);
        inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2][4] = {
            {7,4,5,6},
            {3,0,1,2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline int shift[2] = {1,2};
        inline int axis[2]  = {0,1};
        inline auto shift_ct = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct  = nmtools_tuple{0_ct,1_ct};
        inline auto shift_cl = to_clipped(shift_ct);
        inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(shift)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[2][4] = {
            {6,7,4,5},
            {2,3,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
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
        inline int shift = 1;
        inline auto shift_ct = 1_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[2][3][2] = {
            {
                {11,0},
                { 1,2},
                { 3,4},
            },
            {
                {5, 6},
                {7, 8},
                {9,10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
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
        inline int shift = 1;
        inline int axis  = 0;
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2][3][2] = {
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
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
        inline int shift = 1;
        inline int axis  = 1;
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 1_ct;
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][3][2] = {
            {
                {4,5},
                {0,1},
                {2,3},
            },
            {
                {10,11},
                { 6, 7},
                { 8, 9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
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
        inline int shift = 1;
        inline int axis  = 2;
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 2_ct;
        NMTOOLS_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[2][3][2] = {
            {
                {1,0},
                {3,2},
                {5,4},
            },
            {
                { 7, 6},
                { 9, 8},
                {11,10},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
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
        inline int shift   = 1;
        inline int axis[2] = {1,0};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result[2][3][2] = {
            {
                {10,11},
                { 6, 7},
                { 8, 9},
            },
            {
                {4,5},
                {0,1},
                {2,3},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3f)
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
        inline int shift[2] = {2,1};
        inline int axis[2]  = {1,0};
        inline auto shift_ct = nmtools_tuple{2_ct,1_ct};
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(shift)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        inline int result[2][3][2] = {
            {
                { 8, 9},
                {10,11},
                { 6, 7},
            },
            {
                {2,3},
                {4,5},
                {0,1},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3g)
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
        inline int shift[2] = {2,1};
        inline int axis[2]  = {0,1};
        inline auto shift_ct = nmtools_tuple{2_ct,1_ct};
        inline auto axis_ct  = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3g)
    {
        inline int result[2][3][2] = {
            {
                {4,5},
                {0,1},
                {2,3},
            },
            {
                {10,11},
                { 6, 7},
                { 8, 9},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3h)
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
        inline int shift[2] = {1,1};
        inline int axis[2]  = {1,2};
        inline auto shift_ct = nmtools_tuple{1_ct,1_ct};
        inline auto axis_ct  = nmtools_tuple{1_ct,2_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3h)
    {
        inline int result[2][3][2] = {
            {
                {5,4},
                {1,0},
                {3,2},
            },
            {
                {11,10},
                { 7, 6},
                { 9, 8},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ROLL_HPP