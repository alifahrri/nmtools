#ifndef NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, take)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t array[6] = {4, 3, 5, 7, 6, 8};
        inline int8_t indices[3] = {0, 1, 4};
        inline int8_t axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct,4_ct};
        inline auto indices_cl = to_clipped(indices_ct);
        inline auto axis_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t result[3] = {4, 3, 6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int8_t indices[3] = {0,1,4};
        inline int8_t axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t result[2][3] = {
            {0,1,4},
            {5,6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t array[2][3][2] = {
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
        inline int8_t indices[3] = {0,5,6};
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t result[3] = {0,5,6};
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        inline int8_t indices[1] = {1};
        inline int8_t axis = 0;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t result[1][5] = {
            {5,6,7,8,9},
        };
    }
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t array[5][2] = {
            {0,5},
            {1,6},
            {2,7},
            {3,8},
            {4,9},
        };
        inline int8_t indices[4] = {1,4,3,2};
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t result[4] = {5,2,6,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int8_t array[2][3][2] = {
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
        inline int8_t indices[2] = {2,1};
        inline auto axis = 1;
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t result[2][2][2] = {
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
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_take)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t array[6] = {4, 3, 5, 7, 6, 8};
        constexpr inline int8_t indices[3] = {0, 1, 4};
        constexpr inline int8_t axis = 0;
        constexpr inline auto indices_ct = nmtools_tuple{0_ct,1_ct,4_ct};
        constexpr inline auto axis_ct = 0_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t result[3] = {4, 3, 6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int8_t array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        constexpr inline int8_t indices[3] = {0,1,4};
        constexpr inline int8_t axis = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int8_t result[2][3] = {
            {0,1,4},
            {5,6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int8_t array[2][3][2] = {
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
        constexpr inline int8_t indices[3] = {0,5,6};
        constexpr inline auto axis = None;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int8_t result[3] = {0,5,6};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TAKE_HPP