#ifndef NMTOOLS_TESTING_DATA_ARRAY_DOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_DOT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,dot)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[6] = {6,7,8,9,10,11};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result = 145;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3][2] = {
            { 6, 7},
            { 8, 9},
            {10,11},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][2] = {
            { 28, 31},
            {100,112},
        };
    }
    
    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = {6,7,8};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2] = {23,86};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3][4] = {
            { 6, 7, 8, 9},
            {10,11,12,13},
            {14,15,16,17},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2][4] = {
            { 38, 41, 44, 47},
            {128,140,152,164},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][3][2] = {
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
            {
                {12,13},
                {14,15},
                {16,17},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d)
    {
        inline int result[2][2][2] = {
            {
                {28,31},
                {46,49},
            },
            {
                {100,112},
                {172,184},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
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
            }
        };
        inline int b[3][2][2] = {
            {
                {12,13},
                {14,15},
            },
            {
                {16,17},
                {18,19},
            },
            {
                {20,21},
                {22,23},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][3][3][2] = {
            {
                {
                    {14,15},
                    {18,19},
                    {22,23},
                },
                {
                    { 66, 71},
                    { 86, 91},
                    {106,111},
                },
                {
                    {118,127},
                    {154,163},
                    {190,199},
                },
            },
            {
                {
                    {170,183},
                    {222,235},
                    {274,287},
                },
                {
                    {222,239},
                    {290,307},
                    {358,375},
                },
                {
                    {274,295},
                    {358,379},
                    {442,463},
                },
            },
        };
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
            }
        };
        inline int b[2][3] = {
            {12,13,14},
            {15,16,17},
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[2][3][3] = {
            {
                { 15, 16, 17},
                { 69, 74, 79},
                {123,132,141},
            },
            {
                {177,190,203},
                {231,248,265},
                {285,306,327},
            },
        };
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
        inline int b[2] = {12,13};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[2][3] = {
            { 13, 63,113},
            {163,213,263},
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
        inline int b[2][4][2][2] = {
            {
                {
                    {12, 13},
                    {14, 15}
                },
                {
                    {16, 17},
                    {18, 19}
                },
                {
                    {20, 21},
                    {22, 23}
                },
                {
                    {24, 25},
                    {26, 27}
                }
            },
            {
                {
                    {28, 29},
                    {30, 31}
                },
                {
                    {32, 33},
                    {34, 35}
                },
                {
                    {36, 37},
                    {38, 39}
                },
                {
                    {40, 41},
                    {42, 43}
                }
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[2][3][2][4][2] = {{{{{ 14,  15},
           { 18,  19},
           { 22,  23},
           { 26,  27}},
 
          {{ 30,  31},
           { 34,  35},
           { 38,  39},
           { 42,  43}}},
 
 
         {{{ 66,  71},
           { 86,  91},
           {106, 111},
           {126, 131}},
 
          {{146, 151},
           {166, 171},
           {186, 191},
           {206, 211}}},
 
 
         {{{118, 127},
           {154, 163},
           {190, 199},
           {226, 235}},
 
          {{262, 271},
           {298, 307},
           {334, 343},
           {370, 379}}}},
 
 
 
        {{{{170, 183},
           {222, 235},
           {274, 287},
           {326, 339}},
 
          {{378, 391},
           {430, 443},
           {482, 495},
           {534, 547}}},
 
 
         {{{222, 239},
           {290, 307},
           {358, 375},
           {426, 443}},
 
          {{494, 511},
           {562, 579},
           {630, 647},
           {698, 715}}},
 
 
         {{{274, 295},
           {358, 379},
           {442, 463},
           {526, 547}},
 
          {{610, 631},
           {694, 715},
           {778, 799},
           {862, 883}}}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_DOT_HPP