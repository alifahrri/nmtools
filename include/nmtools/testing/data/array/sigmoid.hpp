#ifndef NMTOOLS_TESTING_DATA_ARRAY_SIGMOID_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SIGMOID_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, sigmoid)
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
        inline float result[2][3][2] = {{{1.233946e-04, 6.334875e-04},
         {3.245377e-03, 1.644893e-02},
         {7.910678e-02, 3.061497e-01}},

        {{6.938503e-01, 9.208933e-01},
         {9.835511e-01, 9.967546e-01},
         {9.993666e-01, 9.998766e-01}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SIGMOID_HPP