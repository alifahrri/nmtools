#ifndef NMTOOLS_TESTING_DATA_ARRAY_HARDTANH_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_HARDTANH_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, hardtanh)
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
        inline float result[2][3][2] = {{{-1.000000, -1.000000},
         {-1.000000, -1.000000},
         {-1.000000, -0.818182}},

        {{ 0.818182,  1.000000},
         { 1.000000,  1.000000},
         { 1.000000,  1.000000}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_HARDTANH_HPP