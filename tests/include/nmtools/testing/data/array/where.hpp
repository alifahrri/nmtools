#ifndef NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP

#include "nmtools/array/view/where.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <array>
#include <vector>

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

NMTOOLS_TESTING_DECLARE_CASE(view, where)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline bool condition[10] = {true, true, true, true, true, false, false, false, false, false};
        inline int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        inline int y[10] = {0,10,20,30,40,50,60,70,80,90};
        CAST_ARRAYS(condition)
        CAST_ARRAYS(x)
        CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dim = 1;
        inline int shape[1] = {10};
        inline int result[10] = {0, 1, 2, 3, 4, 50, 60, 70, 80, 90};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int x[3][1] = {
            {0},
            {1},
            {2},
        };
        inline int y[1][4] = {{10,11,12,13}};
        CAST_ARRAYS(condition)
        CAST_ARRAYS(x)
        CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dim = 2;
        inline int shape[2] = {3,4};
        inline int result[3][4] = {
            {10,  0,  0, 0},
            {10, 11,  1, 1},
            {10, 11, 12, 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int x[1][3][1] = {
            {
                {0},
                {1},
                {2},
            }
        };
        inline int y[1][4] = {{10,11,12,13}};
        CAST_ARRAYS(condition)
        CAST_ARRAYS(x)
        CAST_ARRAYS(y)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int dim = 3;
        inline int shape[3] = {1,3,4};
        inline int result[1][3][4] = {
            {
                {10,  0,  0, 0},
                {10, 11,  1, 1},
                {10, 11, 12, 2},
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP