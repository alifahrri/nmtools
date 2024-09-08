#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONV1D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONV1D_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, conv1d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[1][5][3] = {
            {
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
            }
        };
        inline int bias[1] = {0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][1][2] = {{{135,150}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline float weight[1][5][3] = {
            {
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
            }
        };
        inline int bias[1] = {0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[1][1][2] = {{{45., 50.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[1][5][2] = {
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            }
        };
        inline int bias[1] = {0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline float result[1][1][3] = {{{85.,95.,105.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[2][5][2] = {
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            },
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            },
        };
        inline int bias[2] = {0,0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[1][2][3] = {
            {
                {85,95,105},
                {85,95,105},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int input[1][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            }
        };
        inline float weight[2][3][2] = {
            {
                {-5.000000, -4.090909},
                {-3.181818, -2.272727},
                {-1.363636, -0.454545},
            },
            {
                { 0.454545,  1.363636},
                { 2.272727,  3.181818},
                { 4.090909,  5.000000}
            }
        };
        inline int bias[2] = {0,0};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline float result[1][2][3] = {
            {
                {-43.181812, -59.545452, -75.909088},
                {104.090912, 120.454544, 136.818176},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int input[1][6][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            }
        };
        inline float weight[2][3][3] = {
            {
                {1.f, 1.f, 1.f},
                {1.f, 1.f, 1.f},
                {1.f, 1.f, 1.f},
            },
            {
                {1.f, 1.f, 1.f},
                {1.f, 1.f, 1.f},
                {1.f, 1.f, 1.f},
            }
        };
        inline float bias[2] = {0.5f,0.5f};
        inline auto stride   = None;
        inline auto padding  = None;
        inline auto dilation = None;
        inline int groups    = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline float result[1][2][2] = {
            {
                { 45.5f,  54.5f},
                {153.5f, 162.5f},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int input[1][6][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
                {20,21,22,23},
            }
        };
        inline float weight[2][3][3] = {
            {
                {1.000000, 1.470588, 1.941176},
                {2.411765, 2.882353, 3.352941},
                {3.823529, 4.294117, 4.764706},
            },
            {
                {5.235294, 5.705883, 6.176471},
                {6.647059, 7.117647, 7.588235},
                {8.058824, 8.529411, 9.000000},
            }
        };
        inline int bias[2]   = {0,0};
        inline auto stride   = None;
        inline auto padding  = None;
        inline auto dilation = None;
        inline int groups    = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline float result[1][2][2] = {
            {
                { 166.411758,  192.352936},
                {1125.705811, 1189.764648},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[1][5][3] = {
            {
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
            }
        };
        inline int bias[1]   = {0};
        inline auto stride   = 2;
        inline auto padding  = None;
        inline auto dilation = None;
        inline auto groups   = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int result[1][1][1] = {{{135}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline float weight[1][5][3] = {
            {
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
                {0.25,0.50,0.25},
            }
        };
        inline int bias[1]   = {0};
        inline auto stride   = 2;
        inline auto padding  = None;
        inline auto dilation = None;
        inline auto groups   = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline float result[1][1][1] = {{{45.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[1][5][2] = {
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            }
        };
        inline int bias[1]   = {0};
        inline auto stride   = 2;
        inline auto padding  = None;
        inline auto dilation = None;
        inline auto groups   = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline float result[1][1][2] = {{{85.,105.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[1][5][2] = {
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            }
        };
        inline int bias[1]   = {0};
        inline auto stride   = 3;
        inline auto padding  = None;
        inline auto dilation = None;
        inline auto groups   = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline float result[1][1][1] = {{{85.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int input[1][5][4] = {
            {
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15},
                {16,17,18,19},
            }
        };
        inline int weight[2][5][2] = {
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            },
            {
                {1,1},
                {1,1},
                {1,1},
                {1,1},
                {1,1},
            },
        };
        inline int bias[2]   = {0,0};
        inline auto stride   = 3;
        inline auto padding  = None;
        inline auto dilation = None;
        inline auto groups   = 1;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int result[1][2][1] = {
            {
                {85},
                {85},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int input[1][5][5] = {
            {
                { 0, 1, 2, 3, 4},
                { 5, 6, 7, 8, 9},
                {10,11,12,13,14},
                {15,16,17,18,19},
                {20,21,22,23,24},
            }
        };
        inline int weight[1][5][3] = {
            {
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
                {1,1,1},
            }
        };
        inline auto bias     = None;
        inline auto stride   = None;
        inline auto padding  = None;
        inline auto dilation = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int result[1][1][1] = {{{180}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int input[1][5][5] = {
            {
                { 0, 1, 2, 3, 4},
                { 5, 6, 7, 8, 9},
                {10,11,12,13,14},
                {15,16,17,18,19},
                {20,21,22,23,24},
            }
        };
        inline float weight[1][5][3] = {
            {
                {  1, 0.25,  1},
                {0.5,0.125,0.5},
                {  1, 0.25,  1},
                {  1, 0.25,  1},
                {  1, 0.25,  1},
            }
        };
        inline auto bias     = None;
        inline auto stride   = None;
        inline auto padding  = None;
        inline auto dilation = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline float result[1][1][1] = {{{127.125}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int input[1][5][6] = {
            {
                { 0, 1, 2, 3, 4, 5},
                { 6, 7, 8, 9,10,11},
                {12,13,14,15,16,17},
                {18,19,20,21,22,23},
                {24,25,26,27,28,29},
            }
        };
        inline float weight[1][5][3] = {
            {
                {  1, 0.25,  1},
                {0.5,0.125,0.5},
                {  1, 0.25,  1},
                {  1, 0.25,  1},
                {  1, 0.25,  1},
            }
        };
        inline auto bias     = None;
        inline auto stride   = None;
        inline auto padding  = None;
        inline auto dilation = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline float result[1][1][2] = {{{148.5,158.625}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int input[1][6][6] = {
            {
                { 0, 1, 2, 3, 4, 5},
                { 6, 7, 8, 9,10,11},
                {12,13,14,15,16,17},
                {18,19,20,21,22,23},
                {24,25,26,27,28,29},
                {30,31,32,33,34,35},
            }
        };
        inline float weight[2][3][3] = {
            {
                {1,0.5,1},
                {1,0.5,1},
                {1,0.5,1},
            },
            {
                {0.5,   1, 0.5},
                {  1, 0.5,   1},
                {0.5,   1, 0.5},
            }
        };
        inline int bias[2]  = {1,1};
        inline auto stride  = None;
        inline auto padding = None;
        inline int dilation = 2;
        inline int groups   = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline float result[1][2][2] = {
            {
                { 61.0, 68.5},
                {170.0,176.5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int input[1][6][6] = {
            {
                { 0, 1, 2, 3, 4, 5},
                { 6, 7, 8, 9,10,11},
                {12,13,14,15,16,17},
                {18,19,20,21,22,23},
                {24,25,26,27,28,29},
                {30,31,32,33,34,35},
            }
        };
        inline float weight[1][6][3] = {
            {
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
            }
        };
        inline int bias[1]  = {1};
        inline int stride   = 2;
        inline auto padding = None;
        inline int dilation = 2;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline float result[1][1][1] = {{{235.}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int input[1][6][6] = {
            {
                { 0, 1, 2, 3, 4, 5},
                { 6, 7, 8, 9,10,11},
                {12,13,14,15,16,17},
                {18,19,20,21,22,23},
                {24,25,26,27,28,29},
                {30,31,32,33,34,35},
            }
        };
        inline float weight[1][6][3] = {
            {
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
                {0.5,1.0,0.5},
                {1.0,0.5,1.0},
            }
        };
        inline int bias[1]   = {1};
        inline auto stride   = None;
        inline auto padding  = 1;
        inline auto dilation = None;
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline float result[1][1][6] = {
            {
                {140.5,221.5,235.0,248.5,262.0,176.5}
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CONV1D_HPP