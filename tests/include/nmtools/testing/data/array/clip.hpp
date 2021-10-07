#ifndef NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(array, clip)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline float amin[2] = {1,0};
        inline float amax[1] = {3};
        CAST_ARRAYS(a)
        CAST_ARRAYS(amin)
        CAST_ARRAYS(amax)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            {1,1},
            {2,3},
            {3,3},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline float amin[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline float amax[1] = {3};
        CAST_ARRAYS(a)
        CAST_ARRAYS(amin)
        CAST_ARRAYS(amax)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {3,3},
            },
            {
                {3,3},
                {3,3},
                {3,3},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline float amin[2] = {1,0};
        inline float amax = 3;
        CAST_ARRAYS(a)
        CAST_ARRAYS(amin)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            {1,1},
            {2,3},
            {3,3},
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_CLIP_HPP