#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_ROLL_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_ROLL_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(constexpr_roll)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        constexpr inline int array[6] = {1,2,3,4,5,6};
        constexpr inline int shift = 1;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto shift_cl = to_clipped(shift_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        constexpr inline int result[6] = {6,1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        constexpr inline int array[6] = {1,2,3,4,5,6};
        constexpr inline int shift = 2;
        constexpr inline auto shift_ct = 2_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        constexpr inline int result[6] = {5,6,1,2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        constexpr inline int array[6] = {1,2,3,4,5,6};
        constexpr inline int shift = -2;
        constexpr inline auto shift_ct = "-2"_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        constexpr inline int result[6] = {3,4,5,6,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        constexpr inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        constexpr inline auto shift = 1;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto shift_cl = to_clipped(shift_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        constexpr inline int result[2][4] = {
            {7,0,1,2},
            {3,4,5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        constexpr inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        constexpr inline auto shift = -2;
        constexpr inline auto shift_ct = "-2"_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        constexpr inline int result[2][4] = {
            {2,3,4,5},
            {6,7,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        constexpr inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        constexpr inline auto shift = 1;
        constexpr inline auto axis  = 0;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = 0_ct;
        constexpr inline auto shift_cl = to_clipped(shift_ct);
        constexpr inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        constexpr inline int result[2][4] = {
            {4,5,6,7},
            {0,1,2,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        constexpr inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        constexpr inline auto shift = 1;
        constexpr inline int axis[2] = {1,0};
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        constexpr inline auto shift_cl = to_clipped(shift_ct);
        constexpr inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        constexpr inline int result[2][4] = {
            {7,4,5,6},
            {3,0,1,2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        constexpr inline int array[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        constexpr inline int shift[2] = {1,2};
        constexpr inline int axis[2]  = {0,1};
        constexpr inline auto shift_ct = nmtools_tuple{1_ct,2_ct};
        constexpr inline auto axis_ct  = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto shift_cl = to_clipped(shift_ct);
        constexpr inline auto axis_cl  = to_clipped(axis_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(shift)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        constexpr inline int result[2][4] = {
            {6,7,4,5},
            {2,3,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift = 1;
        constexpr inline auto shift_ct = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift = 1;
        constexpr inline int axis  = 0;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = 0_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift = 1;
        constexpr inline int axis  = 1;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = 1_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift = 1;
        constexpr inline int axis  = 2;
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = 2_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift   = 1;
        constexpr inline int axis[2] = {1,0};
        constexpr inline auto shift_ct = 1_ct;
        constexpr inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift[2] = {2,1};
        constexpr inline int axis[2]  = {1,0};
        constexpr inline auto shift_ct = nmtools_tuple{2_ct,1_ct};
        constexpr inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(shift)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3f)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift[2] = {2,1};
        constexpr inline int axis[2]  = {0,1};
        constexpr inline auto shift_ct = nmtools_tuple{2_ct,1_ct};
        constexpr inline auto axis_ct  = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3g)
    {
        constexpr inline int result[2][3][2] = {
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
        constexpr inline int array[2][3][2] = {
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
        constexpr inline int shift[2] = {1,1};
        constexpr inline int axis[2]  = {1,2};
        constexpr inline auto shift_ct = nmtools_tuple{1_ct,1_ct};
        constexpr inline auto axis_ct  = nmtools_tuple{1_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3h)
    {
        constexpr inline int result[2][3][2] = {
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

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_ROLL_HPP