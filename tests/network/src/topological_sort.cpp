#include "nmtools/network/topological_sort.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/data/network/topological_sort.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::network::digraph;
using nmtools::unwrap;
using namespace nmtools::literals;

#define TOPOLOGICAL_SORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    auto result = nmtools::network::topological_sort(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::sorted_nodes ); \
}

#define DIGRAPH_TOPOLOGICAL_SORT_SUBCASE(case_name, list, node_ids) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    auto digraph = nmtools::network::digraph(list,node_ids); \
    auto result = nmtools::network::topological_sort(digraph); \
    NMTOOLS_ASSERT_EQUAL( result, nmtools::network::map_ids(expect::sorted_nodes,node_ids) ); \
}

#define CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::topological_sort(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::sorted_nodes ); \
}

#define CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE(case_name, list, node_ids) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_sort, case_name); \
    using namespace args; \
    constexpr auto digraph = nmtools::network::digraph(list,node_ids); \
    constexpr auto result = nmtools::network::topological_sort(digraph); \
    NMTOOLS_ASSERT_EQUAL( result, nmtools::network::map_ids(expect::sorted_nodes,node_ids) ); \
}

TEST_CASE("topological_sort(case1)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case1, list_v_v );

    TOPOLOGICAL_SORT_SUBCASE( case1, list );
}

TEST_CASE("digraph_topological_sort(case1)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{ 1_ct, 2_ct, 3_ct };
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case1)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv_ct );
    
    constexpr auto node_ids = nmtools_array{1,2,3};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case1, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case2)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case2, list_v_v );

    TOPOLOGICAL_SORT_SUBCASE( case2, list );
}

TEST_CASE("digraph_topological_sort(case2)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{ 1_ct, 2_ct, 3_ct, 4_ct };
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case2)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_array{1,2,3,4};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case2, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case3)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case3, list_v_v );

    // Trigger assert at compile time (which is correct)
    // TOPOLOGICAL_SORT_SUBCASE( case3, list );
}

TEST_CASE("topological_sort(case3)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{ 1_ct, 2_ct, 3_ct };
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_v_v, node_ids );

    // Trigger assert at compile time (which is correct)
    // DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case3)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_array{1,2,3};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case3, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case5)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case5, list_v_v );

    TOPOLOGICAL_SORT_SUBCASE( case5, list );
}

TEST_CASE("topological_sort(case5)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{1_ct,2_ct,3_ct,4_ct};
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case5)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_array{1,2,3,4};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case5, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case6, list_v_v );

    TOPOLOGICAL_SORT_SUBCASE( case6, list );
}

TEST_CASE("topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{1_ct};
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_tuple{1};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case7)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case7, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case7, list_v_v );

    TOPOLOGICAL_SORT_SUBCASE( case7, list );
}

TEST_CASE("topological_sort(case7)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{1_ct,2_ct,3_ct,4_ct,5_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case7, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case6)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_array{1,2,3,4,5,6};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case6, list_sv_sv_ct, node_ids );
}

TEST_CASE("topological_sort(case8)" * doctest::test_suite("network::topological_sort"))
{
    TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_a_v );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_v );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_v_sv );
    TOPOLOGICAL_SORT_SUBCASE( case8, list_v_v );

    // TOPOLOGICAL_SORT_SUBCASE( case8, list );
}

TEST_CASE("digraph_topological_sort(case8)" * doctest::test_suite("network::topological_sort"))
{
    auto node_ids = nmtools_tuple{1_ct,2_ct};
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_v_v, node_ids );

    // DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list, node_ids );
}

TEST_CASE("constexpr_topological_sort(case8)" * doctest::test_suite("network::topological_sort"))
{
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv_ct );

    constexpr auto node_ids = nmtools_array{1,2};
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_a_sv_ct, node_ids );
    CONSTEXPR_DIGRAPH_TOPOLOGICAL_SORT_SUBCASE( case8, list_sv_sv_ct, node_ids );
}