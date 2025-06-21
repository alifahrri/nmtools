#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_TO_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_TO_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int8_t x[3] = {1,2,3};
        constexpr auto shape = nmtools_array{2,3,3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int8_t expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_broadcast_to)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t x[3] = {1,2,3};
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int8_t x[1][3] = {{1,2,3}};
        constexpr inline auto shape = nmtools_array{3,3};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int8_t x = 1;
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int8_t expected[1][3] = {
            {1,1,1}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_BROADCAST_TO_HPP