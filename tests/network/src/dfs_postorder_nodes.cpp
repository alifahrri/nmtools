#include "nmtools/network/dfs_postorder_nodes.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/dfs_postorder_nodes.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define DFS_POSTORDER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, dfs_postorder_nodes, case_name); \
    using namespace args; \
    auto result = nmtools::network::dfs_postorder_nodes(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::postorder ); \
}

#define CONSTEXPR_DFS_POSTORDER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, dfs_postorder_nodes, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::dfs_postorder_nodes(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::postorder ); \
}

#define DIGRAPH_DFS_POSTORDER_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, dfs_postorder_nodes, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::dfs_postorder_nodes(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::postorder,src_node_ids) ); \
}

#define MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, dfs_postorder_nodes, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::dfs_postorder_nodes(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::postorder,src_node_ids) ); \
}

TEST_CASE("dfs_postorder_nodes(case1)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case1, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case1, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case1, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case1, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case1, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case1, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case1)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case1, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case1, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case1)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case1)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case2)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case2, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case2, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case2, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case2, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case2, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case2, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case2)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case2, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case2, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case2)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case2)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case3)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case3, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case3, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case3, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case3, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case3, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case3, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case3)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case3, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case3, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case3)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case3)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case4)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case4, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case4, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case4, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case4, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case4, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case4, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case4)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case4, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case4, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case4)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case4)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case5)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case5, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case5, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case5, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case5, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case5, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case5, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case5)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case5, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case5, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case5)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case5)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case6)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case6, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case6, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case6, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case6, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case6, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case6, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case6)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case6, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case6, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case6)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case6)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case6, list, src_node_ids_ct, node_idx_ct );
}

// self-loop on the source -> emitted once
TEST_CASE("dfs_postorder_nodes(case7)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case7, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case7, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case7, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case7, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case7, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case7, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case7, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case7)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case7, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case7, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case7, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case7)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case7)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case7, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case8)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case8, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case8, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case8, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case8, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case8, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case8, list_v_v, node_idx );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case8)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case8, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case8, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_dfs_postorder_nodes(case8)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_v_v, src_node_ids, node_idx );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case8)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case8, list_v_v, src_node_ids, node_idx );
}

// empty graph -> Nothing
TEST_CASE("dfs_postorder_nodes(case9)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case9, list, node_idx );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case9)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case9, list, node_idx_ct );
}

TEST_CASE("dfs_postorder_nodes(case10)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case10, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case10, list_a_v, node_idx );
    DFS_POSTORDER_SUBCASE( case10, list_sv_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case10, list_sv_v, node_idx );
    DFS_POSTORDER_SUBCASE( case10, list_v_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case10, list_v_v, node_idx );

    DFS_POSTORDER_SUBCASE( case10, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case10)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case10, list_a_sv_ct, node_idx );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case10, list_sv_sv_ct, node_idx );

    CONSTEXPR_DFS_POSTORDER_SUBCASE( case10, list, node_idx_ct );
}

TEST_CASE("digraph_dfs_postorder_nodes(case10)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_dfs_postorder_nodes(case10)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case10, list, src_node_ids_ct, node_idx_ct );
}

// multi-source: two disconnected components
TEST_CASE("dfs_postorder_nodes(case11)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case11, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case11, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case11, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case11, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case11, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case11, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case11, list, source_nodes );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case11, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case11, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case11)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case11, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case11, list_sv_sv_ct, source_nodes );
}

// multi-source: a seed already emitted as part of the first tree is skipped
TEST_CASE("dfs_postorder_nodes(case12)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case12, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case12, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case12, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case12, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case12, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case12, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case12, list, source_nodes );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case12)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case12, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case12, list_sv_sv_ct, source_nodes );
}

// multi-source: descending seeds, later seed reaches an emitted node
TEST_CASE("dfs_postorder_nodes(case13)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case13, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case13, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case13, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case13, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case13, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case13, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case13, list, source_nodes );

    // same expectation from the single-source overload
    DFS_POSTORDER_SUBCASE( case13, list_a_sv, node_idx );
    DFS_POSTORDER_SUBCASE( case13, list, node_idx_ct );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case13)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case13, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case13, list_sv_sv_ct, source_nodes );
}

// multi-source: every node is a seed == nx source=None (whole graph)
TEST_CASE("dfs_postorder_nodes(case14)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case14, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case14, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case14, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case14, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case14, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case14, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case14, list, source_nodes );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case14, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case14, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case14)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case14, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case14, list_sv_sv_ct, source_nodes );
}

// multi-source: duplicate + descending seeds {4,3,4}
TEST_CASE("dfs_postorder_nodes(case15)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case15, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case15, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case15, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case15, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case15, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case15, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case15, list, source_nodes );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case15, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case15, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case15)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case15, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case15, list_sv_sv_ct, source_nodes );
}

// multi-source: one out-of-range seed -> Nothing
TEST_CASE("dfs_postorder_nodes(case16)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case16, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case16, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case16, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case16, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case16, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case16, list_v_v, source_nodes );
    // no digraph variants: map_ids on an index *array* input doesn't
    // bounds-check; the invalid digraph path is covered by case8.
}

TEST_CASE("constexpr_dfs_postorder_nodes(case16)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case16, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case16, list_sv_sv_ct, source_nodes );
}

// multi-source: empty seed set -> empty result
TEST_CASE("dfs_postorder_nodes(case17)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    DFS_POSTORDER_SUBCASE( case17, list_a_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case17, list_a_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case17, list_sv_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case17, list_sv_v, source_nodes );
    DFS_POSTORDER_SUBCASE( case17, list_v_sv, source_nodes );
    DFS_POSTORDER_SUBCASE( case17, list_v_v, source_nodes );

    DFS_POSTORDER_SUBCASE( case17, list, source_nodes );

    DIGRAPH_DFS_POSTORDER_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DFS_POSTORDER_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_dfs_postorder_nodes(case17)" * doctest::test_suite("network::dfs_postorder_nodes"))
{
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case17, list_a_sv_ct, source_nodes );
    CONSTEXPR_DFS_POSTORDER_SUBCASE( case17, list_sv_sv_ct, source_nodes );
}
