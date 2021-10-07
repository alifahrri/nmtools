#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <tuple>

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

NMTOOLS_TESTING_DECLARE_CASE(view, concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[1][2] = {{5,6}};
        inline int axis = 0;
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline int expected[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[2][1] = {{5},{6}};
        inline int axis = 1;
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,3};
        inline int expected[2][3] = {
            {1,2,5},
            {3,4,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[2][1] = {{5},{6}};
        inline auto axis = None;
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[1] = {6};
        inline int expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[2][1][2] = {{{1,2}},{{3,4}}};
        inline int rhs[2][1][1] = {{{5}},{{6}}};
        inline int axis = 2;
        CAST_ARRAYS(lhs);
        CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[3] = {2,1,3};
        inline int expected[2][1][3] = {
            {
                {1,2,5}
            },
            {
                {3,4,6},
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP