#ifndef NMTOOLS_TESTING_DATA_ARRAY_MOVEAXIS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MOVEAXIS_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, moveaxis)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = 0;
        inline int destination = 1;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][1][3] = {
            {
                {0,1,2}
            },
            {
                {3,4,5}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = 1;
        inline int destination = 0;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][1][3] = {
            {
                {0,1,2}
            },
            {
                {3,4,5}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = 0;
        inline int destination = -2;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][1][3] = {
            {
                {0,1,2}
            },
            {
                {3,4,5}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = 0;
        inline int destination = 2;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {1},
                {2},
            },
            {
                {3},
                {4},
                {5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = 0;
        inline int destination = -1;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2][3][1] = {
            {
                {0},
                {1},
                {2},
            },
            {
                {3},
                {4},
                {5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source = -1;
        inline int destination = 0;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[3][1][2] = {
            {{0,3}},
            {{1,4}},
            {{2,5}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int a[1][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            }
        };
        inline int source[1] = {-1};
        inline int destination[1] = {0};
        NMTOOLS_CAST_ARRAYS(a);
        NMTOOLS_CAST_ARRAYS(source);
        NMTOOLS_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3][1][2] = {
            {{0,3}},
            {{1,4}},
            {{2,5}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
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
        inline int source[2] = {0,1};
        inline int destination[2] = {-1,2};
        NMTOOLS_CAST_ARRAYS(a);
        NMTOOLS_CAST_ARRAYS(source);
        NMTOOLS_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[3][4][2][1] = {
            {
                {
                    {0},
                    {12},
                },
                {
                    {1},
                    {13},
                },
                {
                    {2},
                    {14},
                },
                {
                    {3},
                    {15},
                }
            },
            {
                {
                    {4},
                    {16},
                },
                {
                    {5},
                    {17},
                },
                {
                    {6},
                    {18},
                },
                {
                    {7},
                    {19}
                }
            },
            {
                {
                    {8},
                    {20},
                },
                {
                    {9},
                    {21},
                },
                {
                    {10},
                    {22},
                },
                {
                    {11},
                    {23},
                }
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        inline int source[3] = {0,1,2};
        inline int destination[3] = {-1,-2,-3};
        NMTOOLS_CAST_ARRAYS(a);
        NMTOOLS_CAST_ARRAYS(source);
        NMTOOLS_CAST_ARRAYS(destination);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[4][3][2][1] = {
            {
                {
                    { 0},
                    {12},
                },
                {
                    { 4},
                    {16},
                },
                {
                    { 8},
                    {20},
                },
            },
            {
                {
                    { 1},
                    {13},
                },
                {
                    { 5},
                    {17},
                },
                {
                    { 9},
                    {21},
                }
            },
            {
                {
                    { 2},
                    {14},
                },
                {
                    { 6},
                    {18},
                },
                {
                    {10},
                    {22},
                }
            },
            {
                {
                    { 3},
                    {15},
                },
                {
                    { 7},
                    {19},
                },
                {
                    {11},
                    {23},
                }
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MOVEAXIS_HPP