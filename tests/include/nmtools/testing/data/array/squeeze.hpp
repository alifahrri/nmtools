#ifndef NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP

#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/testing.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
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

NMTOOLS_TESTING_DECLARE_CASE(squeeze)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[6] = {1,2,3,4,5,6};
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6},
        };
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape_[2] = {6,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline double array[1][6] = {
            {1,2,3,4,5,6}
        };
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline double array[6][1][1] = {
            {
                {1}
            },
            {
                {2}
            },
            {
                {3}
            },
            {
                {4}
            },
            {
                {5}
            },
            {
                {6}
            }
        };
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline double array[1][6][1] = {
            {
                {1},
                {2},
                {3},
                {4},
                {5},
                {6}
            }
        };
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,4,5,6};
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_SQUEEZE_HPP