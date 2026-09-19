#ifndef NMTOOLS_TESTING_DATA_ARRAY_STRIDE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_STRIDE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,stride)
{
    using namespace nmtools::literals;

    using nmtools_tuple;

    // broadcast_to
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int x[3] = {1,2,3};
        inline int shape[2] = {3,3};
        inline int striding[2] = {0,1};

        inline auto shape_ct    = tuple{3_ct,3_ct};
        inline auto striding_ct = tuple{0_ct,1_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    // reshape
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[2] = {12,1};
        inline int striding[2] = {1,0};

        inline auto shape_ct = tuple{12_ct,1_ct};
        inline auto striding_ct = tuple{1_ct,0_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t expected[12][1] = {
            {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}
        };
    }

    // reshape
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[2] = {3,4};
        inline int striding[2] = {4,1};

        inline auto shape_ct    = tuple{3_ct,4_ct};
        inline auto striding_ct = tuple{4_ct,1_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t expected[3][4] = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12}
        };
    }

    // reshape
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[4] = {1,2,3,2};
        inline int striding[4] = {12,6,2,1};

        inline auto shape_ct    = tuple{1_ct,2_ct,3_ct,2_ct};
        inline auto striding_ct = tuple{12_ct,6_ct,2_ct,1_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t expected[1][2][3][2] = {
            {
                {
                    {1, 2},
                    {3, 4},
                    {5, 6}
                },
                {
                    {7,  8},
                    {9, 10},
                    {11,12}
                }
            }
        };
    }

    // broadcast_to(4,3) -> reshape(2,3,2)
    // broadcast_to: shape={4,3},stride={0,1}
    // reshape: shape={2,3,2}, stride={}
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int x[3] = {1,2,3};
        inline int shape[3] = {2,3,2};
        inline int striding[3]  = {0,2,1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int expected[2][3][2] = {
            {
                {1,2},
                {3,1},
                {2,3},
            },
            {
                {1,2},
                {3,1},
                {2,3},
            },
        };
    }

    // slice
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // x[::2]
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[1] = {6};
        inline int striding[1] = {2};

        inline auto shape_ct    = tuple{6_ct};
        inline auto striding_ct = tuple{2_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int expected[6] = {1,3,5,7,9,11};
    }

    // slice
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // x[:6:2]
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[1] = {3};
        inline int striding[1] = {2};

        inline auto shape_ct    = tuple{3_ct};
        inline auto striding_ct = tuple{2_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int expected[3] = {1,3,5};
    }

    // reshape -> slice
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // x.reshape(3,4)[::2,::2]
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[2] = {2,2};
        inline int striding[2] = {8,2};

        inline auto shape_ct    = tuple{2_ct,2_ct};
        inline auto striding_ct = tuple{8_ct,2_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int expected[2][2] = {
            {1,3},
            {9,11},
        };
    }

    // reshape -> slice
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // x.reshape(3,4)[::2,::3]
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[2] = {2,2};
        inline int striding[2] = {8,3};

        inline auto shape_ct    = tuple{2_ct,2_ct};
        inline auto striding_ct = tuple{8_ct,3_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int expected[2][2] = {
            {1,4},
            {9,12},
        };
    }

    // slice (negative)
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        // x[::-1]
        inline int x[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int shape[1] = {12};
        inline int striding[1] = {-1};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int expected[12] = {12,11,10,9,8,7,6,5,4,3,2,1};
    }

    using nmtools_tuple, nmtools_array;

    // from cute layout example (col-major interleave)
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int x[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

        inline auto inner_shape_0 = 4;
        inline int inner_shape[2] = {2,4};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_shape);

        inline int inner_strides[2] = {16,1};
        NMTOOLS_CAST_INDEX_ARRAYS(inner_strides);

        inline auto nested_shape_a = tuple{inner_shape_0,inner_shape_a};
        inline auto nested_shape_v = tuple{inner_shape_0,inner_shape_v};
        inline auto nested_shape_h = tuple{inner_shape_0,inner_shape_h};
        inline auto nested_shape_f = tuple{inner_shape_0,inner_shape_f};

        inline auto nested_striding_a = tuple{inner_shape_0,inner_strides_a};
        inline auto nested_striding_v = tuple{inner_shape_0,inner_strides_v};
        inline auto nested_striding_h = tuple{inner_shape_0,inner_strides_h};
        inline auto nested_striding_f = tuple{inner_shape_0,inner_strides_f};

        inline auto nested_shape_ct   = tuple{4_ct,tuple{2_ct,4_ct}};
        inline auto nested_strides_ct = tuple{4_ct,tuple{16_ct,1_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int expected[4][8] = {
            { 0, 1, 2, 3,16,17,18,19},
            { 4, 5, 6, 7,20,21,22,23},
            { 8, 9,10,11,24,25,26,27},
            {12,13,14,15,28,29,30,31},
        };
    }

    // col-major
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int x[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

        inline int shape[2]    = {4,8};
        inline int striding[2] = {1,4};

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);

        inline auto shape_ct    = tuple{4_ct,8_ct};
        inline auto striding_ct = tuple{1_ct,4_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int expected[4][8] = {
            {0,4, 8,12,16,20,24,28},
            {1,5, 9,13,17,21,25,29},
            {2,6,10,14,18,22,26,30},
            {3,7,11,15,19,23,27,31},
        };
    }

    // col-major padded
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int x[40] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
        inline int shape[2]    = {4,8};
        inline int striding[2] = {1,5};

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);

        inline auto shape_ct    = tuple{4_ct,8_ct};
        inline auto striding_ct = tuple{1_ct,5_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int expected[4][8] = {
            {0,5,10,15,20,25,30,35},
            {1,6,11,16,21,26,31,36},
            {2,7,12,17,22,27,32,37},
            {3,8,13,18,23,28,33,38},
        };
    }

    // mixed
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int x[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

        inline auto nested_shape_ct    = tuple{tuple{2_ct,2_ct},tuple{2_ct,4_ct}};
        inline auto nested_striding_ct = tuple{tuple{8_ct,1_ct},tuple{16_ct,2_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int expected[4][8] = {
            {0, 2, 4, 6,16,18,20,22},
            {1, 3, 5, 7,17,19,21,23},
            {8,10,12,14,24,26,28,30},
            {9,11,13,15,25,27,29,31},
        };
    }

    // transpose
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int x[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        inline int shape[2]    = {8,3};
        inline int striding[2] = {1,8};

        inline auto shape_ct    = tuple{8_ct,3_ct};
        inline auto striding_ct = tuple{1_ct,8_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int expected[8][3] = {
            { 0,  8, 16},
            { 1,  9, 17},
            { 2, 10, 18},
            { 3, 11, 19},
            { 4, 12, 20},
            { 5, 13, 21},
            { 6, 14, 22},
            { 7, 15, 23}
        };
    }

    // (2,4,3) transpose -> (3,4,2)
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int x[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        inline int shape[3]    = {3,4,2};
        inline int striding[3] = {1,3,12};

        inline auto shape_ct    = tuple{3_ct,4_ct,2_ct};
        inline auto striding_ct = tuple{1_ct,3_ct,12_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int expected[3][4][2] = {
            {
                { 0, 12},
                { 3, 15},
                { 6, 18},
                { 9, 21}
            },
            {
                { 1, 13},
                { 4, 16},
                { 7, 19},
                {10, 22}
            },
            {
                { 2, 14},
                { 5, 17},
                { 8, 20},
                {11, 23}
            }
        };
    }

    // np.arange(24).reshape(2,4,3).transpose(2,0,1)
    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int x[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        inline int shape[3]    = {3,2,4};
        inline int striding[3] = {1,12,3};

        inline auto shape_ct    = tuple{3_ct,2_ct,4_ct};
        inline auto striding_ct = tuple{1_ct,12_ct,3_ct};

        inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int expected[3][2][4] = {
            {
                { 0,  3,  6,  9},
                {12, 15, 18, 21}
            },
            {
                { 1,  4,  7, 10},
                {13, 16, 19, 22}
            },
            {
                { 2,  5,  8, 11},
                {14, 17, 20, 23}
            }
        };
    }

    // blocked column major
    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int x[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
            34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
            51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
        
        inline int shape1[2] = {2,4};
        inline int shape2[2] = {4,2};

        inline int striding1[2] = {32,1};
        inline int striding2[2] = {8,4};

        NMTOOLS_CAST_INDEX_ARRAYS(shape1);
        NMTOOLS_CAST_INDEX_ARRAYS(shape2);
        NMTOOLS_CAST_INDEX_ARRAYS(striding1);
        NMTOOLS_CAST_INDEX_ARRAYS(striding2);

        inline auto nested_shape_a    = tuple{shape1_a,shape2_a};
        inline auto nested_striding_a = tuple{striding1_a,striding2_a};

        inline auto nested_shape_f    = tuple{shape1_f,shape2_f};
        inline auto nested_striding_f = tuple{striding1_f,striding2_f};

        inline auto nested_shape_h    = tuple{shape1_h,shape2_h};
        inline auto nested_striding_h = tuple{striding1_h,striding2_h};

        inline auto nested_shape_v    = tuple{shape1_v,shape2_v};
        inline auto nested_striding_v = tuple{striding1_v,striding2_v};

        inline auto nested_shape_ct    = tuple{tuple{2_ct,4_ct},tuple{4_ct,2_ct}};
        inline auto nested_striding_ct = tuple{tuple{32_ct,1_ct},tuple{8_ct,4_ct}};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        int expected[8][8] = {
            {0, 4, 8, 12, 16, 20, 24, 28},
            {1, 5, 9, 13, 17, 21, 25, 29},
            {2, 6, 10, 14, 18, 22, 26, 30},
            {3, 7, 11, 15, 19, 23, 27, 31},
            {32, 36, 40, 44, 48, 52, 56, 60},
            {33, 37, 41, 45, 49, 53, 57, 61},
            {34, 38, 42, 46, 50, 54, 58, 62},
            {35, 39, 43, 47, 51, 55, 59, 63}
        };
    }

    /*********************************************************************** */

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int x[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
            34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
            51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

        inline int shape[2] = {8,8};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(1),f2(9)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);

        inline auto shape_ct    = tuple{8_ct,8_ct};
        inline auto striding_ct = tuple{f2(1_ct),f2(9_ct)};

        constexpr inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        constexpr inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        constexpr inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        constexpr inline auto striding_mx2 = to_mixed(striding_ct,1_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        int expected[8][8] = {
            {0, 9, 18, 27, 36, 45, 54, 63},
            {1, 8, 19, 26, 37, 44, 55, 62},
            {2, 11, 16, 25, 38, 47, 52, 61},
            {3, 10, 17, 24, 39, 46, 53, 60},
            {4, 13, 22, 31, 32, 41, 50, 59},
            {5, 12, 23, 30, 33, 40, 51, 58},
            {6, 15, 20, 29, 34, 43, 48, 57},
            {7, 14, 21, 28, 35, 42, 49, 56}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int x[64] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
            34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
            51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

        inline int shape[2] = {8,8};
        NMTOOLS_CAST_INDEX_ARRAYS(shape);

        inline f2<int> striding[2] = {f2(9),f2(1)};
        NMTOOLS_CAST_INDEX_ARRAYS(striding);

        inline auto shape_ct    = tuple{8_ct,8_ct};
        inline auto striding_ct = tuple{f2(9_ct),f2(1_ct)};

        constexpr inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        constexpr inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        constexpr inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        constexpr inline auto striding_mx2 = to_mixed(striding_ct,1_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        int expected[8][8] = {
            {0, 1, 2, 3, 4, 5, 6, 7},
            {9, 8, 11, 10, 13, 12, 15, 14},
            {18, 19, 16, 17, 22, 23, 20, 21},
            {27, 26, 25, 24, 31, 30, 29, 28},
            {36, 37, 38, 39, 32, 33, 34, 35},
            {45, 44, 47, 46, 41, 40, 43, 42},
            {54, 55, 52, 53, 50, 51, 48, 49},
            {63, 62, 61, 60, 59, 58, 57, 56}
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array,constexpr_stride)
{
    using namespace nmtools::literals;

    using nmtools_tuple;

    // broadcast_to
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int x[3] = {1,2,3};
        constexpr inline int shape[2] = {3,3};
        constexpr inline int striding[2] = {0,1};

        constexpr inline auto shape_ct    = tuple{3_ct,3_ct};
        constexpr inline auto striding_ct = tuple{0_ct,1_ct};

        constexpr inline auto shape_mx1 = to_mixed(shape_ct,0_ct);
        constexpr inline auto shape_mx2 = to_mixed(shape_ct,1_ct);
        constexpr inline auto striding_mx1 = to_mixed(striding_ct,0_ct);
        constexpr inline auto striding_mx2 = to_mixed(striding_ct,1_ct);

        NMTOOLS_CONSTEXPR_CAST_ARRAYS(x);
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(shape);
        NMTOOLS_CONSTEXPR_CAST_INDEX_ARRAYS(striding);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_STRIDE_HPP