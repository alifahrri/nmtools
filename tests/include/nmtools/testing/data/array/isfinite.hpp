#ifndef NMTOOLS_TESTING_DATA_ARRAY_ISFINITE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ISFINITE_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, isfinite)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double a[3][3] = {
            { 0.1, INFINITY, 0.3 },
            { NAN,    NAN,   NAN },
            { 0.1, INFINITY, 0.3 },
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline bool result[3][3] = {
            { std::isfinite(0.1), std::isfinite(INFINITY), std::isfinite(0.3) },
            { std::isfinite(NAN), std::isfinite(   NAN  ), std::isfinite(NAN) },
            { std::isfinite(0.1), std::isfinite(INFINITY), std::isfinite(0.3) },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ISFINITE_HPP