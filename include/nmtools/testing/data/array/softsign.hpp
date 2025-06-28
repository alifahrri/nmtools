#ifndef NMTOOLS_TESTING_DATA_ARRAY_SOFTSIGN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SOFTSIGN_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, softsign)
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
        inline float result[2][3][2] = {{{-0.900000, -0.880435},
         {-0.851351, -0.803571},
         {-0.710526, -0.450000}},

        {{ 0.450000,  0.710526},
         { 0.803571,  0.851351},
         { 0.880435,  0.900000}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_SOFTSIGN_HPP