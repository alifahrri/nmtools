#ifndef NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/array/index/as_tuple.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(reshape)
{
    using namespace nm::literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int8_t newshape[2] = {12,1};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto newshape_ct = nmtools_tuple{12_ct, 1_ct};
        // TODO: remove this tuple
        inline auto newshape_t = ::nmtools::index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // isclose doesn't support tuple and raw yet
        inline int8_t shape_[2] = {12,1};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[12][1] = {
            {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int8_t newshape[2] = {3,4};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto newshape_ct = nmtools_tuple{3_ct, 4_ct};
        inline auto newshape_t = ::nmtools::index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // isclose doesn support tuple and raw yet
        inline int8_t shape_[2] = {3,4};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[3][4] = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline int8_t newshape[4] = {1,2,3,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
        inline auto newshape_ct = nmtools_tuple{1_ct, 2_ct, 3_ct, 2_ct};
        inline auto newshape_t = ::nmtools::index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // isclose doesn support tuple and raw yet
        inline int8_t shape_[4] = {1,2,3,2};
        inline auto shape = cast<int8_t>(shape_);
        inline int8_t expected[1][2][3][2] = {
            {
                {
                    {1, 2},
                    {3, 4},
                    {5, 6}
                },
                {
                    {7,  8},
                    {9, 10},
                    {11,12}
                }
            }
        };
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline auto newshape = nmtools_array{-1,3,2};
        inline auto newshape_ct = nmtools_tuple{"-1"_ct,3_ct,2_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline uint8_t shape_[3] = {2,3,2};
        inline int expected[2][3][2] = {
            {
                {1, 2},
                {3, 4},
                {5, 6}
            },
            {
                {7,  8},
                {9, 10},
                {11,12}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline auto newshape = nmtools_array{2,-1,2};
        inline auto newshape_ct = nmtools_tuple{2_ct,"-1"_ct,2_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline uint8_t shape_[3] = {2,3,2};
        inline int expected[2][3][2] = {
            {
                {1, 2},
                {3, 4},
                {5, 6}
            },
            {
                {7,  8},
                {9, 10},
                {11,12}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        inline auto newshape = nmtools_array{-1,-1,2};
        inline auto newshape_ct = nmtools_tuple{"-1"_ct,"-1"_ct,2_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_INDEX_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline auto expected = meta::Nothing;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_reshape)
{
    using namespace nm::literals;
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        constexpr inline int8_t newshape[2] = {12,1};
        constexpr inline auto newshape_ct = nmtools_tuple{12_ct, 1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(newshape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t expected[12][1] = {
            {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP