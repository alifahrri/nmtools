#ifndef NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[6] = {4, 3, 5, 7, 6, 8};
        inline int indices[3] = {0, 1, 4};
        inline int axis = 0;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3] = {4, 3, 6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int indices[3] = {0,1,4};
        inline int axis = 1;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][3] = {
            {0,1,4},
            {5,6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int indices[1] = {1};
        inline int axis = 0;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[1][5] = {
            {5,6,7,8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[5][2] = {
            {0,5},
            {1,6},
            {2,7},
            {3,8},
            {4,9},
        };
        inline int indices[4] = {1,4,3,2};
        inline auto axis = None;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[4] = {5,2,6,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][3][2] = {
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
        inline int indices[3] = {0,5,6};
        inline auto axis = None;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[3] = {0,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[2][3][2] = {
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
        inline int indices[2] = {2,1};
        inline auto axis = 1;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2][2][2] = {
            {
                {4,5},
                {2,3},
            },
            {
                {10,11},
                { 8, 9},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP