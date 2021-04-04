#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCTAN2_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCTAN2_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, arctan2)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0.0,0.1,0.2},
            {0.3,0.4,0.5},
            {0.6,0.7,0.8},
        };
        inline float b[3] = {0.0,0.1,0.2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::atan2(0.0f,0.0f), std::atan2(0.1f, 0.1f), std::atan2(0.2f,0.2f)},
            {std::atan2(0.3f,0.0f), std::atan2(0.4f, 0.1f), std::atan2(0.5f,0.2f)},
            {std::atan2(0.6f,0.0f), std::atan2(0.7f, 0.1f), std::atan2(0.8f,0.2f)},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCTAN2_HPP