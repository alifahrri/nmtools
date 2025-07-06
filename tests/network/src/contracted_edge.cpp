#include "nmtools/network/contracted_edge.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/data/network/contracted_edge.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONTRACTED_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, contracted_edge, case_name ); \
    using namespace args; \
    auto result = nmtools::network::contracted_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::contracted_list ); \
}

#define CONSTEXPR_CONTRACTED_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, contracted_edge, case_name ); \
    using namespace args; \
    constexpr auto result = nmtools::network::contracted_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::contracted_list ); \
}

#define DIGRAPH_CONTRACTED_EDGE_SUBCASE(case_name, adj_list, src_node_ids, src_node_attributes, edge_id, self_loop) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, contracted_edge, case_name ); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids,src_node_attributes); \
    auto edge = nmtools::network::map_ids(edge_id,src_node_ids); \
    auto contracted = nmtools::network::contracted_edge(digraph,edge,nmtools::None,self_loop); \
    const auto& result_list = nmtools::unwrap(contracted).adjacency_list; \
    const auto& result_ids  = nmtools::unwrap(contracted).node_ids; \
    NMTOOLS_ASSERT_EQUAL( result_list, expect::contracted_list); \
    NMTOOLS_ASSERT_EQUAL( result_ids, expect::dst_node_ids); \
    auto graphviz = nmtools::utils::to_string(nmtools::unwrap(contracted),nmtools::utils::Graphviz); \
    CHECK_MESSAGE( true, graphviz ); \
    std::ofstream outputFile; \
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc); \
    outputFile << graphviz << std::endl; \
}

TEST_CASE("contracted_edge(case1)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case1, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case1, list, edge_to_contract_ct, self_loops_flag_ct )
}

TEST_CASE("constexpr_contracted_edge(case1)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case1, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case1, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case1)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case1, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case2)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case2, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case2, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case2)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case2, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case2, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case2)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case2, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case3)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case3, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case3, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case3)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case3, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case3, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case3)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case3, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case4)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case4, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case4, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif 

TEST_CASE("constexpr_contracted_edge(case4)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case4, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case4, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case4)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case4, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case5)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case5, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case5, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case5)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case5, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case5, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case5)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case5, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

TEST_CASE("contracted_edge(case6)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case6, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case6, list, edge_to_contract_ct, self_loops_flag_ct )
}

TEST_CASE("constexpr_contracted_edge(case6)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case6, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case6, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case6)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case6, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case7)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case7, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case7, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case7)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case7, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case7, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("digraph_contracted_edge(case7)" * doctest::test_suite("network::contracted_edge"))
{
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_a_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_a_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_sv_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_sv_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_v_sv, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
    DIGRAPH_CONTRACTED_EDGE_SUBCASE( case7, list_v_v, src_node_ids, node_attributes, edge_to_contract, self_loops_flag )
}