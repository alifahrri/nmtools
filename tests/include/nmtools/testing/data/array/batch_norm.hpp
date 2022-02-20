#ifndef NMTOOLS_TESTING_DATA_ARRAY_BATCH_NORM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BATCH_NORM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, batch_norm)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int input[1][2][5][5] = {{{{ 0,  1,  2,  3,  4},
          { 5,  6,  7,  8,  9},
          {10, 11, 12, 13, 14},
          {15, 16, 17, 18, 19},
          {20, 21, 22, 23, 24}},

         {{25, 26, 27, 28, 29},
          {30, 31, 32, 33, 34},
          {35, 36, 37, 38, 39},
          {40, 41, 42, 43, 44},
          {45, 46, 47, 48, 49}}}};
        inline float mean[2] = {0.3,0.3};
        inline float var[2]  = {0.1,0.1};
        inline float weight[2] = {1.,1.};
        inline float bias[2]   = {0.25,0.25};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(mean)
        NMTOOLS_CAST_ARRAYS(var)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[1][2][5][5] = {{{{ -0.6986,   2.4635,   5.6256,   8.7877,  11.9498},
          { 15.1120,  18.2741,  21.4362,  24.5983,  27.7604},
          { 30.9226,  34.0847,  37.2468,  40.4089,  43.5710},
          { 46.7332,  49.8953,  53.0574,  56.2195,  59.3816},
          { 62.5438,  65.7059,  68.8680,  72.0301,  75.1922}},

         {{ 78.3543,  81.5165,  84.6786,  87.8407,  91.0028},
          { 94.1649,  97.3271, 100.4892, 103.6513, 106.8134},
          {109.9755, 113.1377, 116.2998, 119.4619, 122.6240},
          {125.7861, 128.9483, 132.1104, 135.2725, 138.4346},
          {141.5967, 144.7589, 147.9210, 151.0831, 154.2452}}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int input[2][2][3][3] = {{{{ 0,  1,  2},
          { 3,  4,  5},
          { 6,  7,  8}},

         {{ 9, 10, 11},
          {12, 13, 14},
          {15, 16, 17}}},


        {{{18, 19, 20},
          {21, 22, 23},
          {24, 25, 26}},

         {{27, 28, 29},
          {30, 31, 32},
          {33, 34, 35}}}};
        inline float mean[2] = {0.3,0.3};
        inline float var[2]  = {0.1,0.1};
        inline float weight[2] = {1.,1.};
        inline float bias[2]   = {0.25,0.25};
        NMTOOLS_CAST_ARRAYS(input)
        NMTOOLS_CAST_ARRAYS(mean)
        NMTOOLS_CAST_ARRAYS(var)
        NMTOOLS_CAST_ARRAYS(weight)
        NMTOOLS_CAST_ARRAYS(bias)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][2][3][3] = {{{{ -0.6986,   2.4635,   5.6256},
          {  8.7877,  11.9498,  15.1120},
          { 18.2741,  21.4362,  24.5983}},

         {{ 27.7604,  30.9226,  34.0847},
          { 37.2468,  40.4089,  43.5710},
          { 46.7332,  49.8953,  53.0574}}},


        {{{ 56.2195,  59.3816,  62.5438},
          { 65.7059,  68.8680,  72.0301},
          { 75.1922,  78.3543,  81.5165}},

         {{ 84.6786,  87.8407,  91.0028},
          { 94.1649,  97.3271, 100.4892},
          {103.6513, 106.8134, 109.9755}}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BATCH_NORM_HPP