#ifndef NMTOOLS_TESTING_DATA_ARRAY_RELU6_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RELU6_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

NMTOOLS_TESTING_DECLARE_CASE(activations, relu6)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {{{-9.000000, -7.363636},
         {-5.727273, -4.090909},
         {-2.454545, -0.818182}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {{{0.000000, 0.000000},
         {0.000000, 0.000000},
         {0.000000, 0.000000}},

        {{0.818182, 2.454545},
         {4.090909, 5.727273},
         {6.000000, 6.000000}}};
    }
}

#else // NMTOOLS_BUILD_CONSTEXPR_TESTS

NMTOOLS_TESTING_DECLARE_CASE(activations, constexpr_relu6)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline float a[2][3][2] = {{{-9.000000, -7.363636},
         {-5.727273, -4.090909},
         {-2.454545, -0.818182}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline float result[2][3][2] = {{{0.000000, 0.000000},
         {0.000000, 0.000000},
         {0.000000, 0.000000}},

        {{0.818182, 2.454545},
         {4.090909, 5.727273},
         {6.000000, 6.000000}}};
    }
}

#endif

#endif // NMTOOLS_TESTING_DATA_ARRAY_RELU6_HPP