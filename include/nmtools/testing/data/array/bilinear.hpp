#ifndef NMTOOLS_TESTING_DATA_ARRAY_BILINEAR_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BILINEAR_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array,bilinear)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int a[3] = {0,1,2};
        inline int b[3] = {0,1,2};
        inline int weight[2][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            },
            {
                { 9,10,11},
                {12,13,14},
                {15,16,17},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[2] = {60,141};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int a[6] = {0,1,2,3,4,5};
        inline int b[3] = {0,1,2};
        inline int weight[2][6][3] =
        {{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8},
          { 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}},
 
         {{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26},
          {27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}}};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        inline int result[2] = {570,1380};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2a)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int weight[2][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            },
            {
                { 9,10,11},
                {12,13,14},
                {15,16,17},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2a)
    {
        inline int result[2][2] = {
            { 60, 141},
            {672,1968},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline int weight[1][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            }
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        inline int result[2][1] = {
            { 162},
            {1688},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[2][4] = {
            {0,1,2,3},
            {4,5,6,7},
        };
        inline int weight[3][3][4] =
        {{{ 0,  1,  2,  3},
          { 4,  5,  6,  7},
          { 8,  9, 10, 11}},
 
         {{12, 13, 14, 15},
          {16, 17, 18, 19},
          {20, 21, 22, 23}},
 
         {{24, 25, 26, 27},
          {28, 29, 30, 31},
          {32, 33, 34, 35}}};
        inline int bias[3] = {0,1,2};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c)
    {
        inline int result[2][3] = {
            { 162, 379, 596},
            {1688,4857,8026},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
    {
        inline int a[1][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            }
        };
        inline int b[1][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            }
        };
        inline int weight[2][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            },
            {
                { 9,10,11},
                {12,13,14},
                {15,16,17},
            },
        };

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        inline int result[1][3][2] = {
            {
                {  60, 141},
                { 672,1968},
                {1932,5901},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        inline int a[1][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            }
        };
        inline int b[1][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            }
        };
        inline int weight[2][4][3] =
        {{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8},
          { 9, 10, 11}},
 
         {{12, 13, 14},
          {15, 16, 17},
          {18, 19, 20},
          {21, 22, 23}}};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        inline int result[1][3][2] = {
            {
                { 156,  372},
                {1676, 4844},
                {4780,14356},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        inline int a[1][3][3] = {
            {
                {0,1,2},
                {3,4,5},
                {6,7,8},
            }
        };
        inline int b[1][3][4] = {
            {
                {0,1, 2, 3},
                {4,5, 6, 7},
                {8,9,10,11},
            }
        };
        inline int weight[2][3][4] =
        {{{ 0,  1,  2,  3},
          { 4,  5,  6,  7},
          { 8,  9, 10, 11}},
 
         {{12, 13, 14, 15},
          {16, 17, 18, 19},
          {20, 21, 22, 23}}};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
    {
        inline int result[1][3][2] = {
            {
                { 162,  378},
                {1688, 4856},
                {4798,14374},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3d)
    {
        inline int a[3][2][3] = {
            {
                {0,1,2},
                {3,4,5},
            },
            {
                {6, 7, 8},
                {9,10,11},
            },
            {
                {12,13,14},
                {15,16,17},
            },
        };
        inline int b[3][2][4] =
        {{{ 0,  1,  2,  3},
          { 4,  5,  6,  7}},
 
         {{ 8,  9, 10, 11},
          {12, 13, 14, 15}},
 
         {{16, 17, 18, 19},
          {20, 21, 22, 23}}};
        inline int weight[2][3][4] =
        {{{ 0,  1,  2,  3},
          { 4,  5,  6,  7},
          { 8,  9, 10, 11}},
 
         {{12, 13, 14, 15},
          {16, 17, 18, 19},
          {20, 21, 22, 23}}};
        inline int bias[2] = {0,1};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3d)
    {
        inline int result[3][2][2] = {
            {
                { 162, 379},
                {1688,4857},
            },
            {
                {4798,14375},
                {9492,28933},
            },
            {
                {15770,48531},
                {23632,73169},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4a)
    {
        inline int a[3][1][2][3] =
        {{{{ 0,  1,  2},
           { 3,  4,  5}}},
 
 
         {{{ 6,  7,  8},
           { 9, 10, 11}}},
 
 
         {{{12, 13, 14},
           {15, 16, 17}}}};
        inline int b[3][1][2][4] =
        {{{{ 0,  1,  2,  3},
           { 4,  5,  6,  7}}},
 
 
         {{{ 8,  9, 10, 11},
           {12, 13, 14, 15}}},
 
 
         {{{16, 17, 18, 19},
           {20, 21, 22, 23}}}};
        inline int weight[2][3][4] =
        {{{ 0,  1,  2,  3},
          { 4,  5,  6,  7},
          { 8,  9, 10, 11}},
 
         {{12, 13, 14, 15},
          {16, 17, 18, 19},
          {20, 21, 22, 23}}};
        inline int bias[2] = {0,1};

        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4a)
    {
        inline int result[3][1][2][2] =
        {{{{  162,   379},
           { 1688,  4857}}},
 
 
         {{{ 4798, 14375},
           { 9492, 28933}}},
 
 
         {{{15770, 48531},
           {23632, 73169}}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BILINEAR_HPP