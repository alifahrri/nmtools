#ifndef NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP

#include "nmtools/testing/array_cast.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, matmul)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[4][4] = {
            { 20,  23,  26,  29},
            { 56,  68,  80,  92},
            { 92, 113, 134, 155},
            {128, 158, 188, 218},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[3][4] = {
            {0, 1,  2,  3},
            {4, 5,  6,  7},
            {8, 9, 10, 11},
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][3] = {
            { 42,  48,  54},
            {114, 136, 158},
            {186, 224, 262},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[1][4][3] = {
            {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
                {9,10,11},
            }
        };
        inline int rhs[3][4] = {
            {0, 1, 2, 3},
            {4, 5, 6, 7},
            {8, 9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][4][4] = {
            {
                { 20,  23,  26,  29},
                { 56,  68,  80,  92},
                { 92, 113, 134, 155},
                {128, 158, 188, 218},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[1][3][4] = {
            {
                {0, 1,  2,  3},
                {4, 5,  6,  7},
                {8, 9, 10, 11},
            }
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][3][3] = {
            {
                { 42,  48,  54},
                {114, 136, 158},
                {186, 224, 262},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int lhs[2][3][2] = {
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
        inline int rhs[1][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            }
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][2][3][3] = {
            {
                {
                    { 3, 4, 5},
                    { 9,14,19},
                    {15,24,33},
                },
                {
                    {21,34,47},
                    {27,44,61},
                    {33,54,75},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int lhs[3][2][1][2] = {
            {
                {{0,1}},
                {{2,3}},
            },
            {
                {{4,5}},
                {{6,7}},
            },
            {
                {{ 8, 9}},
                {{10,11}},
            },
        };
        inline int rhs[3][2][2][1] = {
            {
                {
                    {0},
                    {1},
                },
                {
                    {2},
                    {3},
                },
            },
            {
                {
                    {4},
                    {5},
                },
                {
                    {6},
                    {7},
                },
            },
            {
                {
                    {8},
                    {9},
                },
                {
                    {10},
                    {11},
                },
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][2][1][1] = {
            {
                {{1}},
                {{13}},
            },
            {
                {{41}},
                {{85}},
            },
            {
                {{145}},
                {{221}},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int lhs[6] = {0,1,2,3,4,5};
        inline int rhs[6] = {0,1,2,3,4,5};
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 55;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int lhs[6] = {0,1,2,3,4,5};
        inline int rhs[6][2] = {
            { 0, 1},
            { 2, 3},
            { 4, 5},
            { 6, 7},
            { 8, 9},
            {10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[2] = {110,125};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int lhs[6] = {0,1,2,3,4,5};
        inline int rhs[1][6][2] = {
            {
                { 0, 1},
                { 2, 3},
                { 4, 5},
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[1][2] = {
            {110,125},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int lhs[3] = {0,1,2};
        inline int rhs[2][1][3][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                }
            },
            {
                {
                    { 6, 7},
                    { 8, 9},
                    {10,11},
                }
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline int result[2][1][2] = {
            {
                {10,13},
            },
            {
                {28,31},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int lhs[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int rhs[4] = {0,1,2,3};
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[3] = {14,38,62};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int lhs[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int rhs[4][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[3][3] = {
            { 42, 48, 54},
            {114,136,158},
            {186,224,262},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int lhs[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int rhs[2][4][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
                {6,7},
            },
            {
                { 8, 9},
                {10,11},
                {12,13},
                {14,15},
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2][3][2] = {
            {
                { 28, 34},
                { 76, 98},
                {124,162},
            },
            {
                { 76, 82},
                {252,274},
                {428,466},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int lhs[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        inline int rhs[2][1][4][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                    {6,7},
                }
            },
            {
                {
                    { 8, 9},
                    {10,11},
                    {12,13},
                    {14,15},
                }
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2][1][3][2] = {
            {
                {
                    { 28, 34},
                    { 76, 98},
                    {124,162},
                }
            },
            {
                {
                    { 76, 82},
                    {252,274},
                    {428,466},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int lhs[2][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            },
            {
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
        };
        inline int rhs[2][4][3] = {
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
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[2][3][3] = {
            {
                { 42, 48, 54},
                {114,136,158},
                {186,224,262},
            },
            {
                { 906, 960,1014},
                {1170,1240,1310},
                {1434,1520,1606},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int lhs[2][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            },
            {
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
        };
        inline int rhs[4] = {0,1,2,3};
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2][3] = {
            {14, 38, 62},
            {86,110,134},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int lhs[2][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            },
            {
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
        };
        inline int rhs[4][2] = {
            {0,1},
            {2,3},
            {4,5},
            {6,7},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][3][2] = {
            {
                { 28, 34},
                { 76, 98},
                {124,162},
            },
            {
                {172,226},
                {220,290},
                {268,354},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int lhs[2][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            },
            {
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            },
        };
        inline int rhs[2][1][4][2] = {
            {
                {
                    {0,1},
                    {2,3},
                    {4,5},
                    {6,7},
                }
            },
            {
                {
                    { 8, 9},
                    {10,11},
                    {12,13},
                    {14,15},
                }
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[2][2][3][2] = {
            {
                {
                    { 28, 34},
                    { 76, 98},
                    {124,162},
                },
                {
                    {172,226},
                    {220,290},
                    {268,354},
                },
            },
            {
                {
                    { 76, 82},
                    {252,274},
                    {428,466},
                },
                {
                    {604, 658},
                    {780, 850},
                    {956,1042},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int lhs[2][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
            {
                {
                    { 6, 7, 8},
                    { 9,10,11},
                }
            },
        };
        inline int rhs[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[2][1][2] = {
            {
                {5,14},
            },
            {
                {23,32},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int lhs[2][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
            {
                {
                    { 6, 7, 8},
                    { 9,10,11},
                }
            },
        };
        inline int rhs[3][4] = {
            {0,1, 2, 3},
            {4,5, 6, 7},
            {8,9,10,11},
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result[2][1][2][4] = {
            {
                {
                    {20,23,26,29},
                    {56,68,80,92},
                }
            },
            {
                {
                    { 92,113,134,155},
                    {128,158,188,218},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4c)
    {
        inline int lhs[2][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
            {
                {
                    { 6, 7, 8},
                    { 9,10,11},
                }
            },
        };
        inline int rhs[2][3][2] = {
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
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4c)
    {
        inline int result[2][2][2][2] = {
            {
                {
                    {10,13},
                    {28,30},
                },
                {
                    { 28, 31},
                    {100,112},
                },
            },
            {
                {
                    {46,67},
                    {64,94},
                },
                {
                    {172,193},
                    {244,274},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4d)
    {
        inline int lhs[2][1][2][3] = {
            {
                {
                    {0,1,2},
                    {3,4,5},
                }
            },
            {
                {
                    { 6, 7, 8},
                    { 9,10,11},
                }
            },
        };
        inline int rhs[2][2][3][1] = {
            {
                {
                    {0},
                    {1},
                    {2},
                },
                {
                    {3},
                    {4},
                    {5},
                },
            },
            {
                {
                    {6},
                    {7},
                    {8},
                },
                {
                    { 9},
                    {10},
                    {11},
                }
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4d)
    {
        inline int result[2][2][2][1] = {
            {
                {
                    { 5},
                    {14},
                },
                {
                    {14},
                    {50},
                },
            },
            {
                {
                    {149},
                    {212},
                },
                {
                    {212},
                    {302},
                },
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MATMUL_HPP