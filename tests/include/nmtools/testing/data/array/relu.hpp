#ifndef NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(activations, relu)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {{{-9.0000, -7.3636},
         {-5.7273, -4.0909},
         {-2.4545, -0.8182}},

        {{ 0.8182,  2.4545},
         { 4.0909,  5.7273},
         { 7.3636,  9.0000}}};
        CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {{{0.0000, 0.0000},
         {0.0000, 0.0000},
         {0.0000, 0.0000}},

        {{0.8182, 2.4545},
         {4.0909, 5.7273},
         {7.3636, 9.0000}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP