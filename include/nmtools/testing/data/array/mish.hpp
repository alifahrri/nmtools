#ifndef NMTOOLS_TESTING_DATA_ARRAY_MISH_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MISH_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, mish)
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
        inline float result[2][3][2] = {{{-1.110620e-03, -4.666250e-03},
         {-1.861732e-02, -6.784444e-02},
         {-2.018253e-01, -2.864034e-01}},

        {{ 6.779527e-01,  2.424016e+00},
         { 4.088696e+00,  5.727152e+00},
         { 7.363631e+00,  8.999999e+00}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MISH_HPP