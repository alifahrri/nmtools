#ifndef NMTOOLS_TESTING_DATA_ARRAY_GROUP_NORM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_GROUP_NORM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, group_norm)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][5][2][2] = {
            {
                {
                    {0,1},
                    {2,3},
                },
                {
                    {4,5},
                    {6,7},
                },
                {
                    {8,9},
                    {10,11},
                },
                {
                    {12,13},
                    {14,15},
                },
                {
                    {16,17},
                    {18,19}
                },
            }
        };
        inline int num_groups = 5;
        inline int weight[5] = {1,1,1,1,1};
        inline int bias[5]   = {0,0,0,0,0};
        inline int axis[3]   = {-3,-2,-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][5][2][2] = {
            {
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
                {
                    {-1.341635, -0.447212},
                    { 0.447212,  1.341635},
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[1][5][2][2] = {
            {
                {
                    {0,1},
                    {2,3},
                },
                {
                    {4,5},
                    {6,7},
                },
                {
                    {8,9},
                    {10,11},
                },
                {
                    {12,13},
                    {14,15},
                },
                {
                    {16,17},
                    {18,19}
                },
            }
        };
        inline int num_groups = 1;
        inline int weight[5] = {1,1,1,1,1};
        inline int bias[5]   = {0,0,0,0,0};
        inline int axis[3]   = {-3,-2,-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][5][2][2] = {
            {
                {
                    {-1.647509, -1.474087},
                    {-1.300665, -1.127243},
                },
                {
                    {-0.953821, -0.780399},
                    {-0.606977, -0.433555},
                },
                {
                    {-0.260133, -0.086711},
                    { 0.086711,  0.260133},
                },
                {
                    { 0.433555,  0.606977},
                    { 0.780399,  0.953821},
                },
                {
                    { 1.127243,  1.300665},
                    { 1.474087,  1.647509},
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int input[1][5][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
                {6,7},
                {8,9},
            }
        };
        inline int num_groups = 5;
        inline int weight[5]  = {1,1,1,1,1};
        inline int bias[5]    = {0,0,0,0,0};
        inline int axis[2]    = {-2,-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[1][5][2] = {
            {
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
                {-0.999980, 0.999980},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int input[1][5][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
                {6,7},
                {8,9},
            }
        };
        inline int num_groups = 1;
        inline int weight[5]  = {1,1,1,1,1};
        inline int bias[5]    = {0,0,0,0,0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline float result[1][5][2] = {
            {
                {-1.566698, -1.218543},
                {-0.870387, -0.522232},
                {-0.174077,  0.174078},
                { 0.522233,  0.870388},
                { 1.218543,  1.566698},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[1][6][2][2] = {
            {
                {
                    {0,1},
                    {2,3},
                },
                {
                    {4,5},
                    {6,7},
                },
                {
                    {8,9},
                    {10,11},
                },
                {
                    {12,13},
                    {14,15},
                },
                {
                    {16,17},
                    {18,19}
                },
                {
                    {20,21},
                    {22,23},
                }
            }
        };
        inline int num_groups = 3;
        inline int weight[6] = {1,1,1,1,1,1};
        inline int bias[6]   = {0,0,0,0,0,0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][6][2][2] = {
            {
                {
                    {-1.527524, -1.091088},
                    {-0.654653, -0.218218},
                },
                {
                    { 0.218218,  0.654653},
                    { 1.091089,  1.527524},
                },
                {
                    {-1.527524, -1.091088},
                    {-0.654653, -0.218218},
                },
                {
                    { 0.218218,  0.654653},
                    { 1.091089,  1.527524},
                },
                {
                    {-1.527524, -1.091088},
                    {-0.654653, -0.218218},
                },
                {
                    { 0.218218,  0.654653},
                    { 1.091089,  1.527524},
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int input[1][6][2] = {
            {
                { 0, 1},
                { 2, 3},
                { 4, 5},
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int num_groups = 2;
        inline int weight[6]  = {1,1,1,1,1,1};
        inline int bias[6]    = {0,0,0,0,0,0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[1][6][2] = {
            {
                {-1.463848, -0.878309},
                {-0.292770,  0.292770},
                { 0.878309,  1.463848},
                {-1.463848, -0.878309},
                {-0.292770,  0.292770},
                { 0.878309,  1.463848},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_GROUP_NORM_HPP