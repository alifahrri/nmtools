#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline bool a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline bool result[3][3] = {
            { !true, !false,  !true},
            {!false,  !true, !false},
            { !true, !false,  !true},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOGICAL_NOT_HPP