#ifndef NMTOOLS_TESTING_DATA_ARRAY_LEAKY_RELU_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LEAKY_RELU_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, leaky_relu)
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
        inline float result[2][3][2] = {{{-9.000000e-02, -7.363636e-02},
         {-5.727273e-02, -4.090909e-02},
         {-2.454546e-02, -8.181819e-03}},

        {{ 8.181819e-01,  2.454545e+00},
         { 4.090909e+00,  5.727273e+00},
         { 7.363636e+00,  9.000000e+00}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LEAKY_RELU_HPP