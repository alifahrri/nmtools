#ifndef NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

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

NMTOOLS_TESTING_DECLARE_CASE(view, arctanh)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {.1f,.1f,.2f},
            {.3f,.4f,.5f},
            {.6f,.7f,.8f},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::atanh(.1f),std::atanh(.1f),std::atanh(.2f)},
            {std::atanh(.3f),std::atanh(.4f),std::atanh(.5f)},
            {std::atanh(.6f),std::atanh(.7f),std::atanh(.8f)},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_ARCTANH_HPP