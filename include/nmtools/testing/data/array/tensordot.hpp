#ifndef NMTOOLS_TESTING_DATA_ARRAY_TENSORDOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TENSORDOT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,tensordot)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[6] = {0,1,2,3,4,5};

        inline int axes = 1;
        inline auto axes_ct = 1_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result = 55;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result = 55;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[3][2][1] = {
            {
                {0},
                {1},
            },
            {
                {2},
                {3},
            },
            {
                {4},
                {5},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[1] = {55};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[3][2][2] = {
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

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2] = {110,125};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[3][2][1][2] = {
            {
                {
                    {0,1},
                },
                {
                    {2,3},
                },
            },
            {
                {
                    {4,5},
                },
                {
                    {6,7},
                }
            },
            {
                {
                    {8,9},
                },
                {
                    {10,11},
                }
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[1][2] = {
            {110,125}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{0,1},
            nmtools_array{1,2},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct,1_ct},
            nmtools_tuple{1_ct,2_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e)
    {
        inline int result[1] = {55};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2f)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{0,1},
            nmtools_array{1,2},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct,1_ct},
            nmtools_tuple{1_ct,2_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2f)
    {
        inline int result[2] = {55,145};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2g)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{0,1},
            nmtools_array{1,0},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct,1_ct},
            nmtools_tuple{1_ct,0_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2g)
    {
        inline int result[2] = {100,115};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2h)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{1,0},
            nmtools_array{0,1},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{1_ct,0_ct},
            nmtools_tuple{0_ct,1_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2h)
    {
        inline int result[2] = {100,115};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2i)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {6,7},
                {8,9},
                {10,11},
            },
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{1,0},
            nmtools_array{2,1},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{1_ct,0_ct},
            nmtools_tuple{2_ct,1_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2i)
    {
        inline int result[2] = {55,145};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2j)
    {
        inline int a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int b[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline auto axes = nmtools_tuple{
            nmtools_array{0},
            nmtools_array{1},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2j)
    {
        inline int result[2][2] = {
            {10,28},
            {13,40},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
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
            },
        };
        inline int b[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[2] = {55,145};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
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
            },
        };
        inline int b[2][3] = {
            {0,1,2},
            {3,4,5},
        };

        inline auto axes = nmtools_tuple{
            nmtools_array{0,1},
            nmtools_array{0,1},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct,1_ct},
            nmtools_tuple{0_ct,1_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2] = {110,125};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
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
            },
        };
        inline int b[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
        inline auto axes = nmtools_tuple{
            nmtools_array{0,1},
            nmtools_array{-1,-2},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct,1_ct},
            nmtools_tuple{"-1"_ct,"-2"_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][1] = {
            {100},
            {115},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
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
            },
        };
        inline int b[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
        inline auto axes = nmtools_tuple{
            nmtools_array{0},
            nmtools_array{-1},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{"-1"_ct},
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3][2][1][3] =
        {{{{ 6, 18, 30}},
 
          {{ 7, 23, 39}}},
 
 
         {{{ 8, 28, 48}},
  
          {{ 9, 33, 57}}},
 
 
         {{{10, 38, 66}},
  
          {{11, 43, 75}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3e)
    {
        inline int a[2][3][1] = {
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
        };
        inline int b[2][3][1] = {
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
        };
        inline int axes = 3;
        inline auto axes_ct = 3_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3e)
    {
        inline int result = 55;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int a[2][3][4][5] =
        {{{{  0,   1,   2,   3,   4},
           {  5,   6,   7,   8,   9},
           { 10,  11,  12,  13,  14},
           { 15,  16,  17,  18,  19}},
 
          {{ 20,  21,  22,  23,  24},
           { 25,  26,  27,  28,  29},
           { 30,  31,  32,  33,  34},
           { 35,  36,  37,  38,  39}},
 
          {{ 40,  41,  42,  43,  44},
           { 45,  46,  47,  48,  49},
           { 50,  51,  52,  53,  54},
           { 55,  56,  57,  58,  59}}},
 
 
         {{{ 60,  61,  62,  63,  64},
           { 65,  66,  67,  68,  69},
           { 70,  71,  72,  73,  74},
           { 75,  76,  77,  78,  79}},
 
          {{ 80,  81,  82,  83,  84},
           { 85,  86,  87,  88,  89},
           { 90,  91,  92,  93,  94},
           { 95,  96,  97,  98,  99}},
 
          {{100, 101, 102, 103, 104},
           {105, 106, 107, 108, 109},
           {110, 111, 112, 113, 114},
           {115, 116, 117, 118, 119}}}};

        inline int b[3][4][5][2] =
        {{{{  0,   1},
           {  2,   3},
           {  4,   5},
           {  6,   7},
           {  8,   9}},
 
          {{ 10,  11},
           { 12,  13},
           { 14,  15},
           { 16,  17},
           { 18,  19}},
 
          {{ 20,  21},
           { 22,  23},
           { 24,  25},
           { 26,  27},
           { 28,  29}},
 
          {{ 30,  31},
           { 32,  33},
           { 34,  35},
           { 36,  37},
           { 38,  39}}},
 
 
         {{{ 40,  41},
           { 42,  43},
           { 44,  45},
           { 46,  47},
           { 48,  49}},
 
          {{ 50,  51},
           { 52,  53},
           { 54,  55},
           { 56,  57},
           { 58,  59}},
 
          {{ 60,  61},
           { 62,  63},
           { 64,  65},
           { 66,  67},
           { 68,  69}},
 
          {{ 70,  71},
           { 72,  73},
           { 74,  75},
           { 76,  77},
           { 78,  79}}},
 
 
         {{{ 80,  81},
           { 82,  83},
           { 84,  85},
           { 86,  87},
           { 88,  89}},
 
          {{ 90,  91},
           { 92,  93},
           { 94,  95},
           { 96,  97},
           { 98,  99}},
 
          {{100, 101},
           {102, 103},
           {104, 105},
           {106, 107},
           {108, 109}},
 
          {{110, 111},
           {112, 113},
           {114, 115},
           {116, 117},
           {118, 119}}}};
        
        inline auto axes = 3;
        inline auto axes_ct = 3_ct;

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[2][2] = {
            {140420, 142190},
            {352820, 358190},
        };     
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4b)
    {
        inline int a[2][3][4][5] =
        {{{{  0,   1,   2,   3,   4},
           {  5,   6,   7,   8,   9},
           { 10,  11,  12,  13,  14},
           { 15,  16,  17,  18,  19}},
 
          {{ 20,  21,  22,  23,  24},
           { 25,  26,  27,  28,  29},
           { 30,  31,  32,  33,  34},
           { 35,  36,  37,  38,  39}},
 
          {{ 40,  41,  42,  43,  44},
           { 45,  46,  47,  48,  49},
           { 50,  51,  52,  53,  54},
           { 55,  56,  57,  58,  59}}},
 
 
         {{{ 60,  61,  62,  63,  64},
           { 65,  66,  67,  68,  69},
           { 70,  71,  72,  73,  74},
           { 75,  76,  77,  78,  79}},
 
          {{ 80,  81,  82,  83,  84},
           { 85,  86,  87,  88,  89},
           { 90,  91,  92,  93,  94},
           { 95,  96,  97,  98,  99}},
 
          {{100, 101, 102, 103, 104},
           {105, 106, 107, 108, 109},
           {110, 111, 112, 113, 114},
           {115, 116, 117, 118, 119}}}};
        
        inline int b[3][5][4][2] =
        {{{{  0,   1},
           {  2,   3},
           {  4,   5},
           {  6,   7}},
 
          {{  8,   9},
           { 10,  11},
           { 12,  13},
           { 14,  15}},
 
          {{ 16,  17},
           { 18,  19},
           { 20,  21},
           { 22,  23}},
 
          {{ 24,  25},
           { 26,  27},
           { 28,  29},
           { 30,  31}},
 
          {{ 32,  33},
           { 34,  35},
           { 36,  37},
           { 38,  39}}},
 
 
         {{{ 40,  41},
           { 42,  43},
           { 44,  45},
           { 46,  47}},
 
          {{ 48,  49},
           { 50,  51},
           { 52,  53},
           { 54,  55}},
 
          {{ 56,  57},
           { 58,  59},
           { 60,  61},
           { 62,  63}},
 
          {{ 64,  65},
           { 66,  67},
           { 68,  69},
           { 70,  71}},
 
          {{ 72,  73},
           { 74,  75},
           { 76,  77},
           { 78,  79}}},
 
 
         {{{ 80,  81},
           { 82,  83},
           { 84,  85},
           { 86,  87}},
 
          {{ 88,  89},
           { 90,  91},
           { 92,  93},
           { 94,  95}},
 
          {{ 96,  97},
           { 98,  99},
           {100, 101},
           {102, 103}},
 
          {{104, 105},
           {106, 107},
           {108, 109},
           {110, 111}},
 
          {{112, 113},
           {114, 115},
           {116, 117},
           {118, 119}}}};

        inline auto axes = nmtools_tuple{
            nmtools_array{2,3},
            nmtools_array{-2,-3},
        };
        inline auto axes_ct = nmtools_tuple{
            nmtools_tuple{2_ct,3_ct},
            nmtools_tuple{"-2"_ct,"-3"_ct},
        };
        
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4b)
    {
        inline int result[2][3][3][2] =
        {{{{  4180,   4370},
           { 11780,  11970},
           { 19380,  19570}},
 
          {{ 11780,  12370},
           { 35380,  35970},
           { 58980,  59570}},
 
          {{ 19380,  20370},
           { 58980,  59970},
           { 98580,  99570}}},
 
 
         {{{ 26980,  28370},
           { 82580,  83970},
           {138180, 139570}},
 
          {{ 34580,  36370},
           {106180, 107970},
           {177780, 179570}},
 
          {{ 42180,  44370},
           {129780, 131970},
           {217380, 219570}}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TENSORDOT_HPP