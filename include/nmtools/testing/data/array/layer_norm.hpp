#ifndef NMTOOLS_TESTING_DATA_ARRAY_LAYER_NORM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LAYER_NORM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, layer_norm)
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
        inline float weight[5][2][2] = {
            {
                {1.,1.},
                {1.,1.},
            },
            {
                {1.,1.},
                {1.,1.},
            },
            {
                {1.,1.},
                {1.,1.},
            },
            {
                {1.,1.},
                {1.,1.},
            },
            {
                {1.,1.},
                {1.,1.},
            },
        };
        inline float bias[5][2][2] = {
            {
                {0.,0.},
                {0.,0.},
            },
            {
                {0.,0.},
                {0.,0.},
            },
            {
                {0.,0.},
                {0.,0.},
            },
            {
                {0.,0.},
                {0.,0.},
            },
            {
                {0.,0.},
                {0.,0.},
            },
        };
        inline int axis[3] = {-3,-2,-1};
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
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[2][3][4] = {
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
        inline int weight[4] = {1,1,1,1};
        inline int bias[4]   = {0,0,0,0};
        inline int axis[1]   = {-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][4] = {
            {
                {-1.341635, -0.447212,  0.447212,  1.341635},
                {-1.341635, -0.447212,  0.447212,  1.341635},
                {-1.341635, -0.447212,  0.447212,  1.341635},
            },
            {
                {-1.341635, -0.447212,  0.447212,  1.341635},
                {-1.341635, -0.447212,  0.447212,  1.341635},
                {-1.341635, -0.447212,  0.447212,  1.341635},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
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
        inline int weight[2][2] = {
            {1,1},
            {1,1},
        };
        inline int bias[2][2] = {
            {0,0},
            {0,0},
        };
        inline int axis[2] = {-2,-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
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
            },
        };
    }
}

// subtract mean part of layer norm
NMTOOLS_TESTING_DECLARE_CASE(array, layer_norm_subtract_mean)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[2][3][4] = {
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
        inline int axis[1] = {-1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][4] = {
            {
                {-1.5, -0.5, 0.5, 1.5},
                {-1.5, -0.5, 0.5, 1.5},
                {-1.5, -0.5, 0.5, 1.5},
            },
            {
                {-1.5, -0.5, 0.5, 1.5},
                {-1.5, -0.5, 0.5, 1.5},
                {-1.5, -0.5, 0.5, 1.5},
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LAYER_NORM_HPP