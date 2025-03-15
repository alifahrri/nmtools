#ifndef NMTOOLS_TESTING_DATA_ARRAY_TILING_WINDOW_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TILING_WINDOW_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,tiling_window)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int x[6] = {0,1,2,3,4,5};
        inline int tile_shape = 3;

        inline auto tile_shape_ct = 3_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[2][3] = {
            {0,1,2},
            {3,4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int x[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int tile_shape[2] = {1,2};

        inline auto tile_shape_ct = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[3][2][1][2] = {
            {
                {
                    {0,1}
                },
                {
                    {2,3}
                },
            },
            {
                {
                    {4,5}
                },
                {
                    {6,7}
                }
            },
            {
                {
                    {8,9}
                },
                {
                    {10,11}
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int x[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline int tile_shape[2] = {2,2};

        inline auto tile_shape_ct = nmtools_tuple{2_ct,2_ct};

        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int expected[2][2][2][2] = {
            {
                {
                    {0,1},
                    {4,5},
                },
                {
                    {2,3},
                    {6,7},
                },
            },
            {
                {
                    { 8, 9},
                    {12,13},
                },
                {
                    {10,11},
                    {14,15},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int x[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int tile_shape = 3;
        inline int axis = 0;

        inline auto tile_shape_ct = 3_ct;
        inline auto axis_ct = 0_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int expected[1][4][3] = {
            {
                {0,4, 8},
                {1,5, 9},
                {2,6,10},
                {3,7,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int x[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int tile_shape = 2;
        inline int axis = 1;

        inline auto tile_shape_ct = 2_ct;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int expected[3][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            },
            {
                { 8, 9},
                {10,11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int x[4][4] = {
            { 0, 1, 2, 3},
            { 4, 5, 6, 7},
            { 8, 9,10,11},
            {12,13,14,15},
        };
        inline int tile_shape = 2;

        inline auto tile_shape_ct = 2_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int expected[2][2][2][2] = {
            {
                {
                    {0,1},
                    {4,5},
                },
                {
                    {2,3},
                    {6,7},
                },
            },
            {
                {
                    { 8, 9},
                    {12,13},
                },
                {
                    {10,11},
                    {14,15},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int x[2][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
                {18,19,20},
                {21,22,23},
            }
        };
        inline int tile_shape[3] = {2,2,3};

        inline auto tile_shape_ct = nmtools_tuple{2_ct,2_ct,3_ct};

        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int expected[1][2][1][2][2][3] = {
            {
                {
                    {
                        {
                            {0,1,2},
                            {3,4,5},
                        },
                        {
                            {12,13,14},
                            {15,16,17},
                        },
                    }
                },
                {
                    {
                        {
                            {6, 7, 8},
                            {9,10,11},
                        },
                        {
                            {18,19,20},
                            {21,22,23},
                        }
                    }
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int x[2][4][4] = {
            {
                {0,  1, 2, 3},
                {4,  5, 6, 7},
                {8,  9,10,11},
                {12,13,14,15},
            },
            {
                {16,17,18,19},
                {20,21,22,23},
                {24,25,26,27},
                {28,29,30,31},
            }
        };
        inline int tile_shape = 2;

        inline auto tile_shape_ct = 2_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int expected[1][2][2][2][2][2] = {
            {
                {
                    {
                        {
                            {0,1},
                            {4,5},
                        },
                        {
                            {16,17},
                            {20,21},
                        },
                    },
                    {
                        {
                            {2,3},
                            {6,7},
                        },
                        {
                            {18,19},
                            {22,23},
                        }
                    },
                },
                {
                    {
                        {
                            { 8, 9},
                            {12,13},
                        },
                        {
                            {24,25},
                            {28,29},
                        }
                    },
                    {
                        {
                            {10,11},
                            {14,15},
                        },
                        {
                            {26,27},
                            {30,31},
                        },
                    },
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int x[2][4][4] = {
            {
                {0,  1, 2, 3},
                {4,  5, 6, 7},
                {8,  9,10,11},
                {12,13,14,15},
            },
            {
                {16,17,18,19},
                {20,21,22,23},
                {24,25,26,27},
                {28,29,30,31},
            }
        };
        inline int tile_shape = 2;
        inline int axis = 1;

        inline auto tile_shape_ct = 2_ct;
        inline auto axis_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int expected[2][2][4][2] = {
            {
                {
                    {0,4},
                    {1,5},
                    {2,6},
                    {3,7},
                },
                {
                    { 8,12},
                    { 9,13},
                    {10,14},
                    {11,15},
                },
            },
            {
                {
                    {16,20},
                    {17,21},
                    {18,22},
                    {19,23},
                },
                {
                    {24,28},
                    {25,29},
                    {26,30},
                    {27,31},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int x[2][6][4] = {
            {
                {0,  1, 2, 3},
                {4,  5, 6, 7},
                {8,  9,10,11},
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
            {
                {24,25,26,27},
                {28,29,30,31},
                {32,33,34,35},
                {36,37,38,39},
                {40,41,42,43},
                {44,45,46,47},
            }
        };
        inline int tile_shape[2] = {3,2};
        inline int axis[2] = {1,2};

        inline auto tile_shape_ct = nmtools_tuple{3_ct,2_ct};
        inline auto axis_ct = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_ARRAYS(x)
        NMTOOLS_CAST_INDEX_ARRAYS(tile_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int expected[2][2][2][3][2] = {
            {
                {
                    {
                        {0,1},
                        {4,5},
                        {8,9},
                    },
                    {
                        { 2, 3},
                        { 6, 7},
                        {10,11},
                    },
                },
                {
                    {
                        {12,13},
                        {16,17},
                        {20,21},
                    },
                    {
                        {14,15},
                        {18,19},
                        {22,23},
                    }
                },
            },
            {
                {
                    {
                        {24,25},
                        {28,29},
                        {32,33},
                    },
                    {
                        {26,27},
                        {30,31},
                        {34,35},
                    },
                },
                {
                    {
                        {36,37},
                        {40,41},
                        {44,45},
                    },
                    {
                        {38,39},
                        {42,43},
                        {46,47},
                    },
                },
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TILING_WINDOW_HPP