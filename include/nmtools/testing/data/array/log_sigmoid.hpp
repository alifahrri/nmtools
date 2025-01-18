#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOG_SIGMOID_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOG_SIGMOID_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, log_sigmoid)
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
        inline float result[2][3][2] = {{{-9.000123e+00, -7.364270e+00},
         {-5.730524e+00, -4.107495e+00},
         {-2.536957e+00, -1.183681e+00}},

        {{-3.654991e-01, -8.241118e-02},
         {-1.658569e-02, -3.250674e-03},
         {-6.336350e-04, -1.233740e-04}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOG_SIGMOID_HPP