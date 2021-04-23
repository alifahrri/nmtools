#ifndef NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/constants.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(array, ones)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[3] = {2,3,2};
        inline auto dtype = float32;
        CAST_ARRAYS(shape);
        using namespace nmtools::literals;
        inline auto shape_ct = std::tuple{2_ct,3_ct,2_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {
            {
                {1, 1},
                {1, 1},
                {1, 1},
            },
            {
                {1, 1},
                {1, 1},
                {1, 1},
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ONES_HPP