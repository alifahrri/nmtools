#ifndef NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(flatten)
{

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t array[3] = {1,2,3};
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape_[1] = {3};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t array[2][3] = {
            {1,2,3},
            {3,4,5},
        };
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape_[1] = {6};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[6] = {1,2,3,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t array[2][3][1] = {
            {{1},{2},{3}},
            {{3},{4},{5}},
        };
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape_[1] = {6};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[6] = {1,2,3,3,4,5};
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t array[2][3][2] = {
            {
                {1,6},
                {2,7},
                {3,8}
            },
            {
                {3,9},
                {4,10},
                {5,11}
            },
        };
        NMTOOLS_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // isequal doesn't support tuple and raw yet
        inline int8_t shape_[1] = {12};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[12] = {1,6,2,7,3,8,3,9,4,10,5,11};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_flatten)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int8_t array[2][3][2] = {
            {
                {1,6},
                {2,7},
                {3,8}
            },
            {
                {3,9},
                {4,10},
                {5,11}
            },
        };
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int8_t expected[12] = {1,6,2,7,3,8,3,9,4,10,5,11};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP