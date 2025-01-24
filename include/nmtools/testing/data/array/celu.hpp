#ifndef NMTOOLS_TESTING_DATA_ARRAY_CELU_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CELU_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, celu)
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
        inline float result[2][3][2] = {{{-0.999877, -0.999366},
         {-0.996744, -0.983276},
         {-0.914098, -0.558767}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {{{-9.000000, -7.363636},
         {-5.727273, -4.090909},
         {-2.454545, -0.818182}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
        NMTOOLS_CAST_ARRAYS(a);
        inline float alpha = 0.5;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline float result[2][3][2] = {{{-0.500000, -0.500000},
         {-0.499995, -0.499860},
         {-0.496310, -0.402657}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CELU_HPP