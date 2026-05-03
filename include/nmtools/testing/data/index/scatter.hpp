#ifndef NMTOOLS_TESTING_DATA_INDEX_SCATTER_HPP
#define NMTOOLS_TESTING_DATA_INDEX_SCATTER_HPP

#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(scatter)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[3] = {1,2,3};
        inline int order[3] = {0,1,2};
        inline auto indices_ct  = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto order_ct    = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto indices_nl1 = nmtools_array{null_int(),null_int(2),null_int(3)};
        inline auto indices_nl2 = nmtools_array{null_int(1),null_int(),null_int(3)};
        inline auto indices_mx1 = nmtools_tuple{1,2_ct,3_ct};
        inline auto indices_mx2 = nmtools_tuple{1_ct,2,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[3] = {1,2,3};
        inline auto expected_nl1 = nmtools_array{null_int(),null_int(2),null_int(3)};
        inline auto expected_nl2 = nmtools_array{null_int(1),null_int(),null_int(3)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[3] = {1,2,3};
        inline int order[3] = {1,0,2};
        inline auto indices_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto order_ct = nmtools_tuple{1_ct,0_ct,2_ct};
        inline auto indices_nl1 = nmtools_array{null_int(),null_int(2),null_int(3)};
        inline auto indices_nl2 = nmtools_array{null_int(1),null_int(),null_int(3)};
        inline auto indices_mx1 = nmtools_tuple{1,2_ct,3_ct};
        inline auto indices_mx2 = nmtools_tuple{1_ct,2,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[3] = {2,1,3};
        inline auto expected_nl1 = nmtools_array{null_int(2),null_int(),null_int(3)};
        inline auto expected_nl2 = nmtools_array{null_int(),null_int(1),null_int(3)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {1,2,3};
        inline int order[3] = {1,2,0};
        inline auto indices_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        inline auto order_ct = nmtools_tuple{1_ct,2_ct,0_ct};
        inline auto indices_nl1 = nmtools_array{null_int(),null_int(2),null_int(3)};
        inline auto indices_nl2 = nmtools_array{null_int(1),null_int(),null_int(3)};
        inline auto indices_mx1 = nmtools_tuple{1,2_ct,3_ct};
        inline auto indices_mx2 = nmtools_tuple{1_ct,2,3_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[3] = {3,1,2};
        inline auto expected_nl1 = nmtools_array{null_int(3),null_int(),null_int(2)};
        inline auto expected_nl2 = nmtools_array{null_int(3),null_int(1),null_int()};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_scatter)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int indices[3] = {1,2,3};
        constexpr inline int order[3] = {0,1,2};
        constexpr inline auto indices_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        constexpr inline auto order_ct = nmtools_tuple{0_ct,1_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int indices[3] = {1,2,3};
        constexpr inline int order[3] = {1,0,2};
        constexpr inline auto indices_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        constexpr inline auto order_ct = nmtools_tuple{1_ct,0_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int expected[3] = {2,1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int indices[3] = {1,2,3};
        constexpr inline int order[3] = {1,2,0};
        constexpr inline auto indices_ct = nmtools_tuple{1_ct,2_ct,3_ct};
        constexpr inline auto order_ct = nmtools_tuple{1_ct,2_ct,0_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(order)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int expected[3] = {3,1,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_SCATTER_HPP