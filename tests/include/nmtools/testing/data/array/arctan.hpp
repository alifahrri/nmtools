#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, arctan)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0.0,0.1,0.2},
            {0.3,0.4,0.5},
            {0.6,0.7,0.8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::atan(0.0f),std::atan(0.1f),std::atan(0.2f)},
            {std::atan(0.3f),std::atan(0.4f),std::atan(0.5f)},
            {std::atan(0.6f),std::atan(0.7f),std::atan(0.8f)},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCTAN_HPP