#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONV2D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONV2D_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, conv2d)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][1][4][4] = {
            {
                {
                    { 0, 1, 2, 3},
                    { 4, 5, 6, 7},
                    { 8, 9,10,11},
                    {12,13,14,15},
                }
            }
        };
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,0,1},
                    {1,0,1},
                    {1,0,1},
                }
            }
        };
        // inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][1][2][2] = {
            {
                {
                    {30,36},
                    {54,60},   
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[1][1][7][7] = {{{{ 0,  1,  2,  3,  4,  5,  6},
          { 7,  8,  9, 10, 11, 12, 13},
          {14, 15, 16, 17, 18, 19, 20},
          {21, 22, 23, 24, 25, 26, 27},
          {28, 29, 30, 31, 32, 33, 34},
          {35, 36, 37, 38, 39, 40, 41},
          {42, 43, 44, 45, 46, 47, 48}}}};
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1][1][5][5] = {{{{ 72,  81,  90,  99, 108},
          {135, 144, 153, 162, 171},
          {198, 207, 216, 225, 234},
          {261, 270, 279, 288, 297},
          {324, 333, 342, 351, 360}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int input[1][1][5][5] = {{{{ 0,  1,  2,  3,  4},
          { 5,  6,  7,  8,  9},
          {10, 11, 12, 13, 14},
          {15, 16, 17, 18, 19},
          {20, 21, 22, 23, 24}}}};
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][1][3][3] = {{{{ 54,  63,  72},
          { 99, 108, 117},
          {144, 153, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int input[1][1][5][5] = {{{{ 0,  1,  2,  3,  4},
          { 5,  6,  7,  8,  9},
          {10, 11, 12, 13, 14},
          {15, 16, 17, 18, 19},
          {20, 21, 22, 23, 24}}}};
        inline int weight[1][1][3][3] = {
            {
                {
                    {1,1,1},
                    {1,1,1},
                    {1,1,1},
                }
            }
        };
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][1][2][2] = {{{{ 54,  72},
          {144, 162}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[1][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}}};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[1][1][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        inline int stride[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[1][3][3][3] = {{{{15219, 15570, 15921},
          {16974, 17325, 17676},
          {18729, 19080, 19431}},

         {{37818, 38898, 39978},
          {43218, 44298, 45378},
          {48618, 49698, 50778}},

         {{60417, 62226, 64035},
          {69462, 71271, 73080},
          {78507, 80316, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        inline int stride[2] = {2,2};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[1][3][2][2] = {{{{15219, 15921},
          {18729, 19431}},

         {{37818, 39978},
          {48618, 50778}},

         {{60417, 64035},
          {78507, 82125}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        inline int stride[2]  = {2,2};
        inline int padding[2] = {1,1};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[1][3][3][3] = {{{{ 6888, 10479,  7056},
          {11511, 17325, 11547},
          { 8040, 11991,  7920}},

         {{15960, 24816, 17100},
          {28764, 44298, 30258},
          {21972, 33618, 22824}},

         {{25032, 39153, 27144},
          {46017, 71271, 48969},
          {35904, 55245, 37728}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline int weight[3][3][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},

         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}}},


        {{{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}},

         {{36, 37, 38},
          {39, 40, 41},
          {42, 43, 44}},

         {{45, 46, 47},
          {48, 49, 50},
          {51, 52, 53}}},


        {{{54, 55, 56},
          {57, 58, 59},
          {60, 61, 62}},

         {{63, 64, 65},
          {66, 67, 68},
          {69, 70, 71}},

         {{72, 73, 74},
          {75, 76, 77},
          {78, 79, 80}}}};
        inline int stride[2]  = {2,2};
        inline int padding[2] = {2,3};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_INDEX_ARRAYS(stride)
        NMTOOLS_CAST_INDEX_ARRAYS(padding)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int result[1][3][4][5] = {{{{    0,  3426,  5244,  3552,     0},
          {    0, 10296, 15570, 10422,     0},
          {    0, 12726, 19080, 12672,     0},
          {    0,  3768,  5586,  3666,     0}},

         {{    0,  7557, 11805,  8169,     0},
          {    0, 25119, 38898, 26703,     0},
          {    0, 32409, 49698, 33813,     0},
          {    0, 11139, 17007, 11523,     0}},

         {{    0, 11688, 18366, 12786,     0},
          {    0, 39942, 62226, 42984,     0},
          {    0, 52092, 80316, 54954,     0},
          {    0, 18510, 28428, 19380,     0}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int input[1][1][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
            }
        };
        inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline float result[1][3][3][3] = {
            {
                {
                    { 54.,  63.,  72.},
                    { 99., 108., 117.},
                    {144., 153., 162.}
                },
                {
                    { 54.,  63.,  72.},
                    { 99., 108., 117.},
                    {144., 153., 162.}
                },
                {
                    { 54.,  63.,  72.},
                    { 99., 108., 117.},
                    {144., 153., 162.}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int input[1][1][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
            }
        };
        inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {2., 2., 2.},
                    {2., 2., 2.},
                    {2., 2., 2.}
                }
            },
            {
                {
                    {3.5, 3.5, 3.5},
                    {3.5, 3.5, 3.5},
                    {3.5, 3.5, 3.5}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 1;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline float result[1][3][5][5] = {
            {
                {
                    { 12.,  21.,  27.,  33.,  24.},
                    { 33.,  54.,  63.,  72.,  51.},
                    { 63.,  99., 108., 117.,  81.},
                    { 93., 144., 153., 162., 111.},
                    { 72., 111., 117., 123.,  84.}
                },
                {
                    { 24.,  42.,  54.,  66.,  48.},
                    { 66., 108., 126., 144., 102.},
                    {126., 198., 216., 234., 162.},
                    {186., 288., 306., 324., 222.},
                    {144., 222., 234., 246., 168.}
                },
                {
                    { 42.0,  73.5,  94.5, 115.5,  84.0},
                    {115.5, 189.0, 220.5, 252.0, 178.5},
                    {220.5, 346.5, 378.0, 409.5, 283.5},
                    {325.5, 504.0, 535.5, 567.0, 388.5},
                    {252.0, 388.5, 409.5, 430.5, 294.0}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline float weight[2][3][3][3] =
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                },
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                },
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}
                },
                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}
                },
                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline float result[1][2][3][3] = {
            {
                {
                    { 837.0000,  864.0000,  891.0000},
                    { 972.0000,  999.0000, 1026.0000},
                    {1107.0000, 1134.0000, 1161.0000}
                },
                {
                    { 418.5000,  432.0000,  445.5000},
                    { 486.0000,  499.5000,  513.0000},
                    { 553.5000,  567.0000,  580.5000}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline float weight[2][3][3][3] = {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}},

                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}},

                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}},

                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}
                },
                {
                    {.5, .5, .5},
                    {.5, .5, .5},
                    {.5, .5, .5}
                }
            }
        };
        inline float bias[2] = {0.25,0.25};
        inline auto stride   = 1;
        inline auto padding  = 0;
        inline auto dilation = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline float result[1][2][3][3] = {
            {
                {
                    { 837.2500,  864.2500,  891.2500},
                    { 972.2500,  999.2500, 1026.2500},
                    {1107.2500, 1134.2500, 1161.2500}
                },
                {
                    { 418.7500,  432.2500,  445.7500},
                    { 486.2500,  499.7500,  513.2500},
                    { 553.7500,  567.2500,  580.7500}
                }
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int input[1][3][5][5] = {
            {
                {
                    { 0,  1,  2,  3,  4},
                    { 5,  6,  7,  8,  9},
                    {10, 11, 12, 13, 14},
                    {15, 16, 17, 18, 19},
                    {20, 21, 22, 23, 24}
                },
                {
                    {25, 26, 27, 28, 29},
                    {30, 31, 32, 33, 34},
                    {35, 36, 37, 38, 39},
                    {40, 41, 42, 43, 44},
                    {45, 46, 47, 48, 49}
                },
                {
                    {50, 51, 52, 53, 54},
                    {55, 56, 57, 58, 59},
                    {60, 61, 62, 63, 64},
                    {65, 66, 67, 68, 69},
                    {70, 71, 72, 73, 74}
                }
            }
        };
        inline float weight[3][1][3][3] = 
        {
            {
                {
                    {1., 1., 1.},
                    {1., 1., 1.},
                    {1., 1., 1.}
                }
            },
            {
                {
                    {2., 2., 2.},
                    {2., 2., 2.},
                    {2., 2., 2.}
                }
            },
            {
                {
                    {3.5, 3.5, 3.5},
                    {3.5, 3.5, 3.5},
                    {3.5, 3.5, 3.5}
                }
            }
        };
        inline auto stride   = 1;
        inline auto padding  = 1;
        inline auto dilation = 1;
        inline auto groups   = 3;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline float result[1][3][5][5] = {
            {
                {
                    {  12.0,   21.0,   27.00,   33.0,   24.0},
                    {  33.0,   54.0,   63.00,   72.0,   51.0},
                    {  63.0,   99.0,  108.00,  117.0,   81.0},
                    {  93.0,  144.0,  153.00,  162.0,  111.0},
                    {  72.0,  111.0,  117.00,  123.0,   84.0}
                },
                {
                    { 224.0,  342.0,  354.0,  366.0,  248.0},
                    { 366.0,  558.0,  576.0,  594.0,  402.0},
                    { 426.0,  648.0,  666.0,  684.0,  462.0},
                    { 486.0,  738.0,  756.0,  774.0,  522.0},
                    { 344.0,  522.0,  534.0,  546.0,  368.0}
                },
                {
                    { 742.0, 1123.5, 1144.5, 1165.5,  784.0},
                    {1165.5, 1764.0, 1795.5, 1827.0, 1228.5},
                    {1270.5, 1921.5, 1953.0, 1984.5, 1333.5},
                    {1375.5, 2079.0, 2110.5, 2142.0, 1438.5},
                    { 952.0, 1438.5, 1459.5, 1480.5,  994.0}
                },
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int input[1][3][4][4] =
        {{{{ 0,  1,  2,  3},
           { 4,  5,  6,  7},
           { 8,  9, 10, 11},
           {12, 13, 14, 15}},
 
          {{16, 17, 18, 19},
           {20, 21, 22, 23},
           {24, 25, 26, 27},
           {28, 29, 30, 31}},
 
          {{32, 33, 34, 35},
           {36, 37, 38, 39},
           {40, 41, 42, 43},
           {44, 45, 46, 47}}}};
        inline int weight[3][1][2][2] =
        {{{{ 0,  1},
           { 2,  3}}},
 
 
         {{{ 4,  5},
           { 6,  7}}},
 
 
         {{{ 8,  9},
           {10, 11}}}};
        inline int bias[3] = {0,1,2};
        inline int groups = 3;
        inline int groups_ct = 3_ct;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int result[1][3][3][3] =
        {{{{  24,   30,   36},
           {  48,   54,   60},
           {  72,   78,   84}},
 
          {{ 417,  439,  461},
           { 505,  527,  549},
           { 593,  615,  637}},
 
          {{1322, 1360, 1398},
           {1474, 1512, 1550},
           {1626, 1664, 1702}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int input[1][3][4][4] =
        {{{{ 0,  1,  2,  3},
           { 4,  5,  6,  7},
           { 8,  9, 10, 11},
           {12, 13, 14, 15}},
 
          {{16, 17, 18, 19},
           {20, 21, 22, 23},
           {24, 25, 26, 27},
           {28, 29, 30, 31}},
 
          {{32, 33, 34, 35},
           {36, 37, 38, 39},
           {40, 41, 42, 43},
           {44, 45, 46, 47}}}};
        inline int weight[6][1][2][2] =
        {{{{ 0,  1},
           { 2,  3}}},
 
 
         {{{ 4,  5},
           { 6,  7}}},
 
 
         {{{ 8,  9},
           {10, 11}}},
 
 
         {{{12, 13},
           {14, 15}}},
 
 
         {{{16, 17},
           {18, 19}}},
 
 
         {{{20, 21},
           {22, 23}}}};
        inline int bias[6] = {0,1,2,3,4,5};
        inline int groups = 3;
        inline int groups_ct = 3_ct;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int result[1][6][3][3] =
        {{{{  24,   30,   36},
           {  48,   54,   60},
           {  72,   78,   84}},
 
          {{  65,   87,  109},
           { 153,  175,  197},
           { 241,  263,  285}},
 
          {{ 714,  752,  790},
           { 866,  904,  942},
           {1018, 1056, 1094}},
 
          {{1011, 1065, 1119},
           {1227, 1281, 1335},
           {1443, 1497, 1551}},
 
          {{2428, 2498, 2568},
           {2708, 2778, 2848},
           {2988, 3058, 3128}},
 
          {{2981, 3067, 3153},
           {3325, 3411, 3497},
           {3669, 3755, 3841}}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CONV2D_HPP