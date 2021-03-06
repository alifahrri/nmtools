#ifndef NMTOOLS_TESTING_DATA_ARRAY_HYPOT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_HYPOT_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(view, hypot)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::hypot(0.f,0.f), std::hypot(1.f,1.f), std::hypot(2.f,2.f)},
            {std::hypot(3.f,0.f), std::hypot(4.f,1.f), std::hypot(5.f,2.f)},
            {std::hypot(6.f,0.f), std::hypot(7.f,1.f), std::hypot(8.f,2.f)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::hypot(0.f,2.f), std::hypot(1.f,2.f), std::hypot(2.f,2.f)},
            {std::hypot(3.f,2.f), std::hypot(4.f,2.f), std::hypot(5.f,2.f)},
            {std::hypot(6.f,2.f), std::hypot(7.f,2.f), std::hypot(8.f,2.f)},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_HYPOT_HPP