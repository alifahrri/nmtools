#ifndef NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP

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
namespace view = nm::view;
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

NMTOOLS_TESTING_DECLARE_CASE(array, repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 3;
        inline auto axis = None;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[1] = {12};
        inline int dim = 1;
        inline int result[12] = {1,1,1,2,2,2,3,3,3,4,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {4,2};
        inline int dim = 2;
        inline int result[4][2] = {
            {1,2},
            {1,2},
            {3,4},
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 1;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,4};
        inline int dim = 2;
        inline int result[2][4] = {
            {1,1,2,2},
            {3,3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = std::array{1,2};
        inline auto axis = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {3,2};
        inline int dim = 2;
        inline int result[3][2] = {
            {1,2},
            {3,4},
            {3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = std::array{1,2};
        inline auto axis = 1;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {2,3};
        inline int dim = 2;
        inline int result[2][3] = {
            {1,2,2},
            {3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[1][2][2] = {{{1,2},{3,4}}};
        inline auto repeats = 2;
        inline auto axis = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {2,2,2};
        inline int dim = 3;
        inline int result[2][2][2] = {
            {
                {1,2},
                {3,4}
            },
            {
                {1,2},
                {3,4}
            },
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP