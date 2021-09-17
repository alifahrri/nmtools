#ifndef NMTOOLS_TESTING_DATA_ARAY_SOFTPLUS_HPP
#define NMTOOLS_TESTING_DATA_ARAY_SOFTPLUS_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(activations, softplus)
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
        inline float result[2][3][2] = {{{1.234022e-04, 6.336883e-04},
         {3.250655e-03, 1.658572e-02},
         {8.241119e-02, 3.654991e-01}},

        {{1.183681e+00, 2.536957e+00},
         {4.107495e+00, 5.730524e+00},
         {7.364270e+00, 9.000123e+00}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARAY_SOFTPLUS_HPP