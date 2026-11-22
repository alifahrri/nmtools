#include "nmtools/network/bfs_edges.hpp"
#include "nmtools/testing/data/network/bfs_edges.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

// NOTE: only adjacency-list variants are tested (no digraph/map_ids ones):
// bfs_edges emits (discoverer, discovered) pair rows and map_ids over such
// nested pair containers is not part of the contract yet.
//
// Subcase label conventions inside each TEST_CASE:
//   caseN        forward, flag omitted (default == false)
//   case1_xfalse forward, explicit forward_flag == false (spot-checked once,
//                in case1; must be identical to the default path)
//   caseN_rev    reverse, reverse_flag == true
//
// TODO: constexpr variants (constant adjacency lists / node indices)
//
// WARNING: `#name##suffix` is undefined preprocessor behaviour (gcc parses it
// as a string-literal UDL), so every subcase label below is passed explicitly.

#define BFS_EDGES_SUBCASE(label, case_name, ...) \
SUBCASE(#label) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, bfs_edges, case_name); \
    using namespace args; \
    auto result = nmtools::network::bfs_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::edges ); \
}

#define REVERSE_BFS_EDGES_SUBCASE(label, case_name, ...) \
SUBCASE(#label) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, bfs_edges, case_name); \
    using namespace args; \
    auto result = nmtools::network::bfs_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::redges ); \
}

TEST_CASE("bfs_edges(case1)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case1, case1, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case1_a_v, case1, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case1_sv_sv, case1, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case1_sv_v, case1, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case1_v_sv, case1, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case1_v_v, case1, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case1_ct, case1, list, node_idx_ct );

    // explicit forward_flag == false must equal the default (spot-check)
    BFS_EDGES_SUBCASE( case1_xfalse, case1, list_sv_sv, node_idx, forward_flag );

    REVERSE_BFS_EDGES_SUBCASE( case1_rev, case1, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case1_rev_a_v, case1, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case1_rev_sv_sv, case1, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case1_rev_sv_v, case1, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case1_rev_v_sv, case1, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case1_rev_v_v, case1, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case1_rev_ct, case1, list, node_idx_ct, reverse_flag );
}

TEST_CASE("bfs_edges(case2)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case2, case2, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case2_a_v, case2, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case2_sv_sv, case2, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case2_sv_v, case2, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case2_v_sv, case2, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case2_v_v, case2, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case2_ct, case2, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case2_rev, case2, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case2_rev_a_v, case2, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case2_rev_sv_sv, case2, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case2_rev_sv_v, case2, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case2_rev_v_sv, case2, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case2_rev_v_v, case2, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case2_rev_ct, case2, list, node_idx_ct, reverse_flag );
}

// forward star from the root
TEST_CASE("bfs_edges(case3)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case3, case3, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case3_a_v, case3, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case3_sv_sv, case3, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case3_sv_v, case3, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case3_v_sv, case3, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case3_v_v, case3, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case3_ct, case3, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case3_rev, case3, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case3_rev_a_v, case3, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case3_rev_sv_sv, case3, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case3_rev_sv_v, case3, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case3_rev_v_sv, case3, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case3_rev_v_v, case3, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case3_rev_ct, case3, list, node_idx_ct, reverse_flag );
}

// cyclic graph through the source; forward scan must follow row order {2,0}
TEST_CASE("bfs_edges(case4)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case4, case4, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case4_a_v, case4, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case4_sv_sv, case4, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case4_sv_v, case4, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case4_v_sv, case4, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case4_v_v, case4, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case4_ct, case4, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case4_rev, case4, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case4_rev_a_v, case4, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case4_rev_sv_sv, case4, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case4_rev_sv_v, case4, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case4_rev_v_sv, case4, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case4_rev_v_v, case4, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case4_rev_ct, case4, list, node_idx_ct, reverse_flag );
}

// diamond with cycle, reverse BFS from sink
TEST_CASE("bfs_edges(case5)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case5, case5, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case5_a_v, case5, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case5_sv_sv, case5, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case5_sv_v, case5, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case5_v_sv, case5, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case5_v_v, case5, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case5_ct, case5, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case5_rev, case5, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case5_rev_a_v, case5, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case5_rev_sv_sv, case5, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case5_rev_sv_v, case5, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case5_rev_v_sv, case5, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case5_rev_v_v, case5, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case5_rev_ct, case5, list, node_idx_ct, reverse_flag );
}

// same graph from root: multi-layer forward discovery
TEST_CASE("bfs_edges(case6)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case6, case6, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case6_a_v, case6, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case6_sv_sv, case6, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case6_sv_v, case6, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case6_v_sv, case6, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case6_v_v, case6, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case6_ct, case6, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case6_rev, case6, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case6_rev_a_v, case6, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case6_rev_sv_sv, case6, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case6_rev_sv_v, case6, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case6_rev_v_sv, case6, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case6_rev_v_v, case6, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case6_rev_ct, case6, list, node_idx_ct, reverse_flag );
}

// self-loop on source: emits nothing in either direction
TEST_CASE("bfs_edges(case7)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case7, case7, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case7_a_v, case7, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case7_sv_sv, case7, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case7_sv_v, case7, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case7_v_sv, case7, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case7_v_v, case7, list_v_v, node_idx );

    BFS_EDGES_SUBCASE( case7_ct, case7, list, node_idx_ct );

    REVERSE_BFS_EDGES_SUBCASE( case7_rev, case7, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case7_rev_a_v, case7, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case7_rev_sv_sv, case7, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case7_rev_sv_v, case7, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case7_rev_v_sv, case7, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case7_rev_v_v, case7, list_v_v, node_idx, reverse_flag );

    REVERSE_BFS_EDGES_SUBCASE( case7_rev_ct, case7, list, node_idx_ct, reverse_flag );
}

TEST_CASE("bfs_edges(case8)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case8, case8, list_a_sv, node_idx );
    BFS_EDGES_SUBCASE( case8_a_v, case8, list_a_v, node_idx );
    BFS_EDGES_SUBCASE( case8_sv_sv, case8, list_sv_sv, node_idx );
    BFS_EDGES_SUBCASE( case8_sv_v, case8, list_sv_v, node_idx );
    BFS_EDGES_SUBCASE( case8_v_sv, case8, list_v_sv, node_idx );
    BFS_EDGES_SUBCASE( case8_v_v, case8, list_v_v, node_idx );

    REVERSE_BFS_EDGES_SUBCASE( case8_rev, case8, list_a_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case8_rev_a_v, case8, list_a_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case8_rev_sv_sv, case8, list_sv_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case8_rev_sv_v, case8, list_sv_v, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case8_rev_v_sv, case8, list_v_sv, node_idx, reverse_flag );
    REVERSE_BFS_EDGES_SUBCASE( case8_rev_v_v, case8, list_v_v, node_idx, reverse_flag );
}

TEST_CASE("bfs_edges(case9)" * doctest::test_suite("network::bfs_edges"))
{
    BFS_EDGES_SUBCASE( case9, case9, list, node_idx );
    REVERSE_BFS_EDGES_SUBCASE( case9_rev, case9, list, node_idx, reverse_flag );
}
