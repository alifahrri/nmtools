#include "nmtools/network/is_directed_acyclic_graph.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/data/network/is_directed_acyclic_graph.hpp"
#include "nmtools/testing/doctest.hpp"

#define IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_directed_acyclic_graph, case_name); \
    using namespace args; \
    auto result = nmtools::network::is_directed_acyclic_graph(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_directed_acyclic_graph, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::is_directed_acyclic_graph(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_directed_acyclic_graph, case_name); \
    using namespace args; \
    auto digraph = nmtools::network::digraph(adj_list); \
    auto result = nmtools::network::is_directed_acyclic_graph(digraph); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("is_directed_acyclic_graph(case1)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case1)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("digraph_is_directed_acyclic_graph(case1)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_a_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_a_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_sv_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_sv_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_v_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list_v_v );

    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case1, list );
}

TEST_CASE("is_directed_acyclic_graph(case2)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case2)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("digraph_is_directed_acyclic_graph(case2)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_a_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_a_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_sv_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_sv_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_v_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list_v_v );

    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case2, list );
}

TEST_CASE("is_directed_acyclic_graph(case3)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case3)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("digraph_is_directed_acyclic_graph(case3)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_a_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_a_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_sv_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_sv_v );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_v_sv );
    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list_v_v );

    DIGRAPH_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case3, list );
}

TEST_CASE("is_directed_acyclic_graph(case4)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case4)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case5)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case5)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case6)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case6)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case7)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case7)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case8)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case8)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case8, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case9)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case9)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case9, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case10)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case10)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case10, list_sv_sv_ct );
}

TEST_CASE("is_directed_acyclic_graph(case11)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_a_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_a_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_sv_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_sv_v );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_v_sv );
    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_v_v );

    IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list );
}

TEST_CASE("constexpr_is_directed_acyclic_graph(case11)" * doctest::test_suite("network::is_directed_acyclic_graph"))
{
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_a_sv_ct );
    CONSTEXPR_IS_DIRECTED_ACYCLIC_GRAPH_SUBCASE( case11, list_sv_sv_ct );
}