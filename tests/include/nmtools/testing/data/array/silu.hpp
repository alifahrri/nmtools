#ifndef NMTOOLS_TESTING_DATA_ARAY_SILU_HPP
#define NMTOOLS_TESTING_DATA_ARAY_SILU_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(activations, silu)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {{{-9.000000, -7.363636},
         {-5.727273, -4.090909},
         {-2.454545, -0.818182}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
        CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {{{-1.110551e-03, -4.664772e-03},
         {-1.858716e-02, -6.729109e-02},
         {-1.941712e-01, -2.504862e-01}},

        {{ 5.676957e-01,  2.260374e+00},
         { 4.023618e+00,  5.708686e+00},
         { 7.358972e+00,  8.998890e+00}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARAY_SILU_HPP