#ifndef NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP

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

NMTOOLS_TESTING_DECLARE_CASE(array, compress)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int condition[2] = {0,1};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 0;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {1,2};
        inline int result[1][2] = {
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int condition[2] = {0,1};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 1;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,1};
        inline int result[3][1] = {
            {2},
            {4},
            {6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline bool condition[3] = {false,true,true};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline int axis = 0;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline bool condition[5] = {false,true,true,false,true};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline auto axis = None;
        CAST_ARRAYS(condition)
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {3};
        inline int result[3] = {2,3,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline auto condition = std::tuple{False,True,True,False,True};
        inline int array[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
        inline auto axis = None;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {3};
        inline int result[3] = {2,3,5};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_COMPRESS_HPP