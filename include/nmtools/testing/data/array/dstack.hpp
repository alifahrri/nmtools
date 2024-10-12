#ifndef NMTOOLS_TESTING_DATA_ARRAY_DSTACK_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DSTACK_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,dstack)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3] = {1,2,3};
        inline int b[3] = {2,3,4};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][3][2] = {
            {
                {1,2},
                {2,3},
                {3,4},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][1] = {
            {1},
            {2},
            {3},
        };
        inline int b[3][1] = {
            {2},
            {3},
            {4},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][1][2] = {
            {
                {1,2},
            },
            {
                {2,3},
            },
            {
                {3,4},
            }
        };
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
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2][3][2] = {
            {
                {0,6},
                {1,7},
                {2,8},
            },
            {
                {3, 9},
                {4,10},
                {5,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
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
                },
            },
            {
                {
                    {6,7},
                },
                {
                    {8,9},
                },
                {
                    {10,11},
                }
            }
        };
        inline int b[2][3][1][2] = {
            {
                {
                    {12,13},
                },
                {
                    {14,15},
                },
                {
                    {16,17},
                }
            },
            {
                {
                    {18,19},
                },
                {
                    {20,21},
                },
                {
                    {22,23},
                },
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][2][2] = {
            {
                {
                    { 0, 1},
                    {12,13},
                },
                {
                    { 2, 3},
                    {14,15},
                },
                {
                    { 4, 5},
                    {16,17},
                },
            },
            {
                {
                    { 6, 7},
                    {18,19},
                },
                {
                    { 8, 9},
                    {20,21},
                },
                {
                    {10,11},
                    {22,23},
                },
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][1][3][1][2] = {
            {
                {
                    {
                        {0,1},
                    },
                    {
                        {2,3},
                    },
                    {
                        {4,5},
                    },
                }
            },
            {
                {
                    {
                        {6,7},
                    },
                    {
                        {8,9},
                    },
                    {
                        {10,11},
                    }
                }
            }
        };
        inline int b[2][1][3][1][2] = {
            {
                {
                    {
                        {12,13},
                    },
                    {
                        {14,15},
                    },
                    {
                        {16,17},
                    }
                }
            },
            {
                {
                    {
                        {18,19},
                    },
                    {
                        {20,21},
                    },
                    {
                        {22,23},
                    },
                }
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][1][6][1][2] = {
            {
                {
                    {
                        {0,1},
                    },
                    {
                        {2,3},
                    },
                    {
                        {4,5},
                    },
                    {
                        {12,13},
                    },
                    {
                        {14,15},
                    },
                    {
                        {16,17},
                    },
                }
            },
            {
                {
                    {
                        {6,7},
                    },
                    {
                        {8,9},
                    },
                    {
                        {10,11},
                    },
                    {
                        {18,19},
                    },
                    {
                        {20,21},
                    },
                    {
                        {22,23},
                    },
                }
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DSTACK_HPP