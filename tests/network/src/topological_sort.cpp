#include "nmtools/network/topological_sort.hpp"
#include "nmtools/testing/data/network/topological_sort.hpp"
#include "nmtools/testing/doctest.hpp"

#define TOPOLOGICAL_SORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    auto result = nmtools::network::topological_sort(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::sorted_nodes ); \
}

#define CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    auto result = nmtools::network::topological_sort(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::sorted_nodes ); \
}

TEST_CASE("topological_sort(case1)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case1)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv );
}

TEST_CASE("topological_sort(case2)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case2)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv );
}

TEST_CASE("topological_sort(case3)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case3)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv );
}

TEST_CASE("topological_sort(case5)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case5)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv );
}

TEST_CASE("topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv );
}

TEST_CASE("topological_sort(case7)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case7, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv );
}

TEST_CASE("topological_sort(case8)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_v_v );
}

TEST_CASE("constexpr_topological_sort(case8)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv );
}