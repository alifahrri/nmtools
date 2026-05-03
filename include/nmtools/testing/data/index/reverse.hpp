#ifndef NMTOOLS_TESTING_DATA_INDEX_REVERSE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_REVERSE_HPP

#include "nmtools/testing/testing.hpp"

namespace nm = nmtools;
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(reverse)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int indices[1] = {1};
        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto indices_nl1 = nmtools_array{null_int(1)};
        inline auto indices_nl2 = nmtools_array{null_int()};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[1] = {1};
        inline auto expected_nl2 = nmtools_array{null_int()};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int indices[2] = {0,1};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto indices_nl1 = nmtools_array{null_int(),null_int(1)};
        inline auto indices_nl2 = nmtools_array{null_int(0),null_int()};
        inline auto indices_mx1 = nmtools_tuple{0,1_ct};
        inline auto indices_mx2 = nmtools_tuple{0_ct,1};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[2] = {1,0};
        inline auto expected_nl1 = nmtools_array{null_int(1),null_int()};
        inline auto expected_nl2 = nmtools_array{null_int(),null_int(0)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int indices[3] = {2,0,1};
        inline auto indices_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        inline auto indices_nl1 = nmtools_array{null_int(),null_int(0),null_int(1)};
        inline auto indices_nl2 = nmtools_array{null_int(2),null_int(0),null_int()};
        inline auto indices_nl3 = nmtools_array{null_int(2),null_int(),null_int(1)};
        inline auto indices_mx1 = nmtools_tuple{2,0_ct,1_ct};
        inline auto indices_mx2 = nmtools_tuple{2_ct,0_ct,1};
        inline auto indices_mx3 = nmtools_tuple{2_ct,0,1_ct};
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int expected[3] = {1,0,2};
        inline auto expected_nl1 = nmtools_array{null_int(1),null_int(0),null_int()};
        inline auto expected_nl2 = nmtools_array{null_int(),null_int(0),null_int(2)};
        inline auto expected_nl3 = nmtools_array{null_int(1),null_int(),null_int(2)};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_reverse)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int indices[1] = {1};
        constexpr inline auto indices_ct = nmtools_tuple{1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int expected[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int indices[2] = {0,1};
        constexpr inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int expected[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int indices[3] = {2,0,1};
        constexpr inline auto indices_ct = nmtools_tuple{2_ct,0_ct,1_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int expected[3] = {1,0,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_REVERSE_HPP