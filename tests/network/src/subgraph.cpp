#include "nmtools/network/subgraph.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/subgraph.hpp"
#include "nmtools/testing/doctest.hpp"

#define SUBGRAPH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, subgraph, case_name ); \
    using namespace args; \
    auto result = nmtools::network::subgraph(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define DIGRAPH_SUBGRAPH_SUBCASE(case_name, g_list, g_map_id, g_node_data, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, subgraph, case_name ); \
    using namespace args; \
    auto G = nmtools::network::digraph(g_list,g_map_id,g_node_data); \
    auto result = unwrap(G.subgraph(__VA_ARGS__)); \
    NMTOOLS_ASSERT_EQUAL( result.adjacency_list, expect::result ); \
    NMTOOLS_ASSERT_EQUAL( result.node_ids, expect::node_ids ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( result.node_attributes, expect::node_data ); \
}

TEST_CASE("subgraph(case1)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case1, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case1, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case1, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case1, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case1, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case1, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case1, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case1, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case1, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case1, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case1, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case1, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case1, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case1, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case1, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case1, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case1, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case1, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case1, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case1, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case1, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case1, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case1, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case1, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case1, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case1, list, node_ids, node_data, keep_nodes );
}

TEST_CASE("subgraph(case2)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case2, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case2, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case2, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case2, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case2, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case2, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case2, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case2, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case2, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case2, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case2, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case2, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case2, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case2, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case2, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case2, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case2, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case2, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case2, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case2, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case2, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case2, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case2, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case2, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case2, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case2, list, node_ids, node_data, keep_nodes );
}

TEST_CASE("subgraph(case3)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case3, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case3, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case3, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case3, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case3, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case3, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case3, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case3, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case3, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case3, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case3, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case3, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case3, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case3, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case3, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case3, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case3, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case3, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case3, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case3, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case3, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case3, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case3, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case3, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case3, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case3, list, node_ids, node_data, keep_nodes );
}

TEST_CASE("subgraph(case4)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case4, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case4, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case4, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case4, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case4, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case4, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case4, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case4, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case4, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case4, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case4, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case4, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case4, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case4, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case4, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case4, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case4, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case4, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case4, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case4, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case4, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case4, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case4, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case4, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case4, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case4, list, node_ids, node_data, keep_nodes );
}

TEST_CASE("subgraph(case5)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case5, list_a_sv, nodes );
    SUBGRAPH_SUBCASE( case5, list_a_v, nodes );
    SUBGRAPH_SUBCASE( case5, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case5, list_sv_v, nodes );
    SUBGRAPH_SUBCASE( case5, list_v_sv, nodes );
    SUBGRAPH_SUBCASE( case5, list_v_v, nodes );
}

TEST_CASE("subgraph(case6)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case6, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case6, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case6, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case6, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case6, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case6, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case6, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case6, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case6, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case6, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case6, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case6, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case6, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case6, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case6, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case6, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case6, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case6, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case6, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case6, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case6, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case6, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case6, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case6, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case6, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case6, list, node_ids, node_data, keep_nodes );
}

TEST_CASE("subgraph(case7)" * doctest::test_suite("network::subgraph"))
{
    SUBGRAPH_SUBCASE( case7, list_a_sv,  nodes );
    SUBGRAPH_SUBCASE( case7, list_a_v,   nodes );
    SUBGRAPH_SUBCASE( case7, list_sv_sv, nodes );
    SUBGRAPH_SUBCASE( case7, list_sv_v,  nodes );
    SUBGRAPH_SUBCASE( case7, list_v_sv,  nodes );
    SUBGRAPH_SUBCASE( case7, list_v_v,   nodes );

    SUBGRAPH_SUBCASE( case7, list_a_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case7, list_a_v,   nodes_a );
    SUBGRAPH_SUBCASE( case7, list_sv_sv, nodes_a );
    SUBGRAPH_SUBCASE( case7, list_sv_v,  nodes_a );
    SUBGRAPH_SUBCASE( case7, list_v_sv,  nodes_a );
    SUBGRAPH_SUBCASE( case7, list_v_v,   nodes_a );

    SUBGRAPH_SUBCASE( case7, list_a_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case7, list_a_v,   nodes_h );
    SUBGRAPH_SUBCASE( case7, list_sv_sv, nodes_h );
    SUBGRAPH_SUBCASE( case7, list_sv_v,  nodes_h );
    SUBGRAPH_SUBCASE( case7, list_v_sv,  nodes_h );
    SUBGRAPH_SUBCASE( case7, list_v_v,   nodes_h );

    SUBGRAPH_SUBCASE( case7, list_a_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case7, list_a_v,   nodes_v );
    SUBGRAPH_SUBCASE( case7, list_sv_sv, nodes_v );
    SUBGRAPH_SUBCASE( case7, list_sv_v,  nodes_v );
    SUBGRAPH_SUBCASE( case7, list_v_sv,  nodes_v );
    SUBGRAPH_SUBCASE( case7, list_v_v,   nodes_v );

    SUBGRAPH_SUBCASE( case7, list, nodes_ct );

    DIGRAPH_SUBGRAPH_SUBCASE( case7, list, node_ids, node_data, keep_nodes );
}