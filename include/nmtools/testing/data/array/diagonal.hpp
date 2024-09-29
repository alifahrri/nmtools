#ifndef NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,diagonal)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][2] = {
            {0,1},
            {2,3},
        };
        // inline int offset = 0;
        // inline int axis1 = 0;
        // inline int axis2 = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2] = {0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][2] = {
            {0,1},
            {2,3},
        };
        inline int offset = 1;
        // inline int axis1 = 0;
        // inline int axis2 = 1;

        inline auto offset_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {1};
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
        inline int offset = 0;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;
        
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2] = {
            {0,8},
            {1,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
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
        inline int offset = 0;
        inline int axis1  = 1;
        inline int axis2  = 2;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = 1_ct;
        inline auto axis2_ct  = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][2] = {
            {0,3},
            {6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
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
        inline int offset = 0;
        inline int axis1  = 2;
        inline int axis2  = 0;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = 2_ct;
        inline auto axis2_ct  = 0_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3][2] = {
            {0, 7},
            {2, 9},
            {4,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
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
        inline int offset = 0;
        inline int axis1  = -1;
        inline int axis2  = -3;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = "-1"_ct;
        inline auto axis2_ct  = "-3"_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][2] = {
            {0, 7},
            {2, 9},
            {4,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
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
        inline int offset = 1;
        inline int axis1  = 0;
        inline int axis2  = 2;

        inline auto offset_ct = 1_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3][1] = {
            {1},
            {3},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
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
        inline int offset = 1;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto offset_ct = 1_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[2][2] = {
            {2,10},
            {3,11}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        inline int offset = 2;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto offset_ct = 2_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[2][1] = {
            {4},
            {5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int a[1][2][3][4] = {
            {
                {
                    {0,1, 2, 3},
                    {4,5, 6, 7},
                    {8,9,10,11},
                },
                {
                    {12,13,14,15},
                    {16,17,18,19},
                    {20,21,22,23},
                }
            }
        };
        inline int offset = 0;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int result[3][4][1] = {
            {
                {0},
                {1},
                {2},
                {3},
            },
            {
                {4},
                {5},
                {6},
                {7},
            },
            {
                { 8},
                { 9},
                {10},
                {11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int a[1][2][3][4] = {
            {
                {
                    {0,1, 2, 3},
                    {4,5, 6, 7},
                    {8,9,10,11},
                },
                {
                    {12,13,14,15},
                    {16,17,18,19},
                    {20,21,22,23},
                }
            }
        };
        inline int offset = 1;
        inline int axis1  = 0;
        inline int axis2  = 1;

        inline auto offset_ct = 1_ct;
        inline auto axis1_ct  = 0_ct;
        inline auto axis2_ct  = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int result[3][4][1] = {
            {
                {12},
                {13},
                {14},
                {15},
            },
            {
                {16},
                {17},
                {18},
                {19},
            },
            {
                {20},
                {21},
                {22},
                {23},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int a[1][2][3][4] = {
            {
                {
                    {0,1, 2, 3},
                    {4,5, 6, 7},
                    {8,9,10,11},
                },
                {
                    {12,13,14,15},
                    {16,17,18,19},
                    {20,21,22,23},
                }
            }
        };
        inline int offset = 0;
        inline int axis1  = 1;
        inline int axis2  = 2;

        inline auto offset_ct = 0_ct;
        inline auto axis1_ct  = 1_ct;
        inline auto axis2_ct  = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[1][4][2] = {
            {
                {0,16},
                {1,17},
                {2,18},
                {3,19},
            }  
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int a[1][2][3][4] = {
            {
                {
                    {0,1, 2, 3},
                    {4,5, 6, 7},
                    {8,9,10,11},
                },
                {
                    {12,13,14,15},
                    {16,17,18,19},
                    {20,21,22,23},
                }
            }
        };
        inline int offset = 1;
        inline int axis1  = 1;
        inline int axis2  = 2;

        inline auto offset_ct = 1_ct;
        inline auto axis1_ct  = 1_ct;
        inline auto axis2_ct  = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[1][4][2] = {
            {
                {4,20},
                {5,21},
                {6,22},
                {7,23},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int a[1][2][3][4] = {
            {
                {
                    {0,1, 2, 3},
                    {4,5, 6, 7},
                    {8,9,10,11},
                },
                {
                    {12,13,14,15},
                    {16,17,18,19},
                    {20,21,22,23},
                }
            }
        };
        inline int offset = 2;
        inline int axis1  = 1;
        inline int axis2  = 2;

        inline auto offset_ct = 2_ct;
        inline auto axis1_ct  = 1_ct;
        inline auto axis2_ct  = 2_ct;

        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int result[1][4][1] = {
            {
                { 8},
                { 9},
                {10},
                {11},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DIAGONAL_HPP