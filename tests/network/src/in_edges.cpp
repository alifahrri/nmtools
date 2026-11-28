#include "nmtools/network/in_edges.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/in_edges.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define IN_EDGES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_edges, case_name); \
    using namespace args; \
    auto result = nmtools::network::in_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges ); \
}

#define CONSTEXPR_IN_EDGES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_edges, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::in_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges ); \
}

#define DIGRAPH_IN_EDGES_SUBCASE(case_name, adj_list, src_node_ids, nbunch) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_edges, case_name); \
    using namespace args; \
    auto nbunch_id = nmtools::network::map_ids(nbunch,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = digraph.in_edges(nbunch_id); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges_ids ); \
}

#define MULTI_DIGRAPH_IN_EDGES_SUBCASE(case_name, adj_list, src_node_ids, nbunch, multi) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_edges, case_name); \
    using namespace args; \
    auto nbunch_id = nmtools::network::map_ids(nbunch,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids); \
    auto result = digraph.in_edges(nbunch_id); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges_ids ); \
}

// nbunch is already given in node id space, so it is passed as-is
#define DIGRAPH_IN_EDGES_ID_SUBCASE(case_name, adj_list, src_node_ids, nbunch_id) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_edges, case_name); \
    using namespace args; \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = digraph.in_edges(nbunch_id); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges_ids ); \
}

TEST_CASE("in_edges(case1)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case1, list_a_sv );
    IN_EDGES_SUBCASE( case1, list_a_v );
    IN_EDGES_SUBCASE( case1, list_sv_sv );
    IN_EDGES_SUBCASE( case1, list_sv_v );
    IN_EDGES_SUBCASE( case1, list_v_sv );
    IN_EDGES_SUBCASE( case1, list_v_v );

    IN_EDGES_SUBCASE( case1, list );
}

TEST_CASE("constexpr_in_edges(case1)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case1, list_sv_sv_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case1, list );
}

TEST_CASE("digraph_in_edges(case1)" * doctest::test_suite("network::in_edges"))
{
    DIGRAPH_IN_EDGES_SUBCASE( case1, list_a_sv, src_node_ids, nmtools::None );
    DIGRAPH_IN_EDGES_SUBCASE( case1, list_sv_sv, src_node_ids, nmtools::None );

    // constant adjacency list with constant node ids
    DIGRAPH_IN_EDGES_SUBCASE( case1, list, src_node_ids_ct, nmtools::None );
}

TEST_CASE("in_edges(case1b)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case1b, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case1b, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case1b, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case1b, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case1b, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case1b, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case1b, list, nbunch_ct );
}

TEST_CASE("constexpr_in_edges(case1b)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case1b, list_a_sv_ct, nbunch_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case1b, list_sv_sv_ct, nbunch_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case1b, list, nbunch_ct );
}

TEST_CASE("digraph_in_edges(case1b)" * doctest::test_suite("network::in_edges"))
{
    DIGRAPH_IN_EDGES_SUBCASE( case1b, list_a_sv, src_node_ids, nbunch );
    DIGRAPH_IN_EDGES_SUBCASE( case1b, list_sv_sv, src_node_ids, nbunch );

    // constant adjacency list with constant node ids
    DIGRAPH_IN_EDGES_SUBCASE( case1b, list, src_node_ids_ct, nbunch_ct );
}

TEST_CASE("in_edges(case1c)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case1c, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case1c, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case1c, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case1c, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case1c, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case1c, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case1c, list, nbunch_ct );
}

TEST_CASE("constexpr_in_edges(case1c)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case1c, list_a_sv_ct, nbunch_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case1c, list_sv_sv_ct, nbunch_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case1c, list, nbunch_ct );
}

TEST_CASE("in_edges(case2)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case2, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case2, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case2, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case2, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case2, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case2, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case2, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case2)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case2, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case2, list_sv_sv_ct, nbunch );
}

TEST_CASE("digraph_in_edges(case2)" * doctest::test_suite("network::in_edges"))
{
    DIGRAPH_IN_EDGES_SUBCASE( case2, list_a_sv, src_node_ids, nbunch );
    DIGRAPH_IN_EDGES_SUBCASE( case2, list_sv_sv, src_node_ids, nbunch );
}

TEST_CASE("in_edges(case2b)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case2b, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case2b, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case2b, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case2b, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case2b, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case2b, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case2b, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case2b)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case2b, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case2b, list_sv_sv_ct, nbunch );
}

TEST_CASE("in_edges(case3)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case3, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case3, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case3, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case3, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case3, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case3, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case3, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case3)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case3, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case3, list_sv_sv_ct, nbunch );
}

TEST_CASE("in_edges(case4)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case4, list_a_sv );
    IN_EDGES_SUBCASE( case4, list_a_v );
    IN_EDGES_SUBCASE( case4, list_sv_sv );
    IN_EDGES_SUBCASE( case4, list_sv_v );
    IN_EDGES_SUBCASE( case4, list_v_sv );
    IN_EDGES_SUBCASE( case4, list_v_v );

    IN_EDGES_SUBCASE( case4, list );
}

TEST_CASE("constexpr_in_edges(case4)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case4, list_sv_sv_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case4, list );
}

TEST_CASE("digraph_in_edges(case4)" * doctest::test_suite("network::in_edges"))
{
    DIGRAPH_IN_EDGES_SUBCASE( case4, list_a_sv, src_node_ids, nmtools::None );
    DIGRAPH_IN_EDGES_SUBCASE( case4, list_sv_sv, src_node_ids, nmtools::None );
}

TEST_CASE("in_edges(case5)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case5, list_a_sv, nbunch, multi );
    IN_EDGES_SUBCASE( case5, list_a_v, nbunch, multi );
    IN_EDGES_SUBCASE( case5, list_sv_sv, nbunch, multi );
    IN_EDGES_SUBCASE( case5, list_sv_v, nbunch, multi );
    IN_EDGES_SUBCASE( case5, list_v_sv, nbunch, multi );
    IN_EDGES_SUBCASE( case5, list_v_v, nbunch, multi );

    IN_EDGES_SUBCASE( case5, list, nbunch, multi );
}

TEST_CASE("constexpr_in_edges(case5)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case5, list_a_sv_ct, nbunch, multi );
    CONSTEXPR_IN_EDGES_SUBCASE( case5, list_sv_sv_ct, nbunch, multi );
}

TEST_CASE("multi_digraph_in_edges(case5)" * doctest::test_suite("network::in_edges"))
{
    MULTI_DIGRAPH_IN_EDGES_SUBCASE( case5, list_a_sv, src_node_ids, nbunch, multi );
    MULTI_DIGRAPH_IN_EDGES_SUBCASE( case5, list_sv_sv, src_node_ids, nbunch, multi );

    // constant adjacency list
    MULTI_DIGRAPH_IN_EDGES_SUBCASE( case5, list, src_node_ids, nbunch, multi );
}

TEST_CASE("in_edges(case6)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case6, list_a_sv );
    IN_EDGES_SUBCASE( case6, list_a_v );
    IN_EDGES_SUBCASE( case6, list_sv_sv );
    IN_EDGES_SUBCASE( case6, list_sv_v );
    IN_EDGES_SUBCASE( case6, list_v_sv );
    IN_EDGES_SUBCASE( case6, list_v_v );

    IN_EDGES_SUBCASE( case6, list );
}

TEST_CASE("constexpr_in_edges(case6)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case6, list_sv_sv_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case6, list );
}

TEST_CASE("in_edges(case7)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case7, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case7, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case7, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case7, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case7, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case7, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case7, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case7)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case7, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case7, list_sv_sv_ct, nbunch );
}

TEST_CASE("in_edges(case8)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case8, list_a_sv );
    IN_EDGES_SUBCASE( case8, list_a_v );
    IN_EDGES_SUBCASE( case8, list_sv_sv );
    IN_EDGES_SUBCASE( case8, list_sv_v );
    IN_EDGES_SUBCASE( case8, list_v_sv );
    IN_EDGES_SUBCASE( case8, list_v_v );

    IN_EDGES_SUBCASE( case8, list );
}

TEST_CASE("constexpr_in_edges(case8)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case8, list_sv_sv_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case8, list );
}

TEST_CASE("in_edges(case9)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case9, list_a_sv );
    IN_EDGES_SUBCASE( case9, list_a_v );
    IN_EDGES_SUBCASE( case9, list_sv_sv );
    IN_EDGES_SUBCASE( case9, list_sv_v );
    IN_EDGES_SUBCASE( case9, list_v_sv );
    IN_EDGES_SUBCASE( case9, list_v_v );

    IN_EDGES_SUBCASE( case9, list );
}

TEST_CASE("constexpr_in_edges(case9)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_IN_EDGES_SUBCASE( case9, list_sv_sv_ct );

    CONSTEXPR_IN_EDGES_SUBCASE( case9, list );
}

TEST_CASE("in_edges(case10)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case10, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case10, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case10, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case10, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case10, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case10, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case10, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case10)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case10, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case10, list_sv_sv_ct, nbunch );
}

TEST_CASE("in_edges(case11)" * doctest::test_suite("network::in_edges"))
{
    IN_EDGES_SUBCASE( case11, list_a_sv, nbunch );
    IN_EDGES_SUBCASE( case11, list_a_v, nbunch );
    IN_EDGES_SUBCASE( case11, list_sv_sv, nbunch );
    IN_EDGES_SUBCASE( case11, list_sv_v, nbunch );
    IN_EDGES_SUBCASE( case11, list_v_sv, nbunch );
    IN_EDGES_SUBCASE( case11, list_v_v, nbunch );

    IN_EDGES_SUBCASE( case11, list, nbunch );
}

TEST_CASE("constexpr_in_edges(case11)" * doctest::test_suite("network::in_edges"))
{
    CONSTEXPR_IN_EDGES_SUBCASE( case11, list_a_sv_ct, nbunch );
    CONSTEXPR_IN_EDGES_SUBCASE( case11, list_sv_sv_ct, nbunch );
}

TEST_CASE("digraph_in_edges(case12)" * doctest::test_suite("network::in_edges"))
{
    DIGRAPH_IN_EDGES_ID_SUBCASE( case12, list_a_sv, src_node_ids, nbunch );
    DIGRAPH_IN_EDGES_ID_SUBCASE( case12, list_sv_sv, src_node_ids, nbunch );
    DIGRAPH_IN_EDGES_ID_SUBCASE( case12, list_a_sv, src_node_ids, nbunch_bad );
    DIGRAPH_IN_EDGES_ID_SUBCASE( case12, list_sv_sv, src_node_ids, nbunch_bad );
}
