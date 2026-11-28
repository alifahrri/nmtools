#include "nmtools/network/descendants.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/descendants.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define DESCENDANTS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, descendants, case_name); \
    using namespace args; \
    auto result = nmtools::network::descendants(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::descendants ); \
}

#define CONSTEXPR_DESCENDANTS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, descendants, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::descendants(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::descendants ); \
}

#define DIGRAPH_DESCENDANTS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, descendants, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::descendants(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::descendants,src_node_ids) ); \
}

#define MULTI_DIGRAPH_DESCENDANTS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, descendants, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::descendants(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::descendants,src_node_ids) ); \
}

TEST_CASE("descendants(case1)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case1, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case1, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case1, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case1, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case1, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case1, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case1)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case1, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case1, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("digraph_descendants(case1)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DESCENDANTS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_descendants(case1)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("descendants(case2)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case2, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case2, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case2, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case2, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case2, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case2, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case2)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case2, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case2, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("digraph_descendants(case2)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DESCENDANTS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_descendants(case2)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("descendants(case3)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case3, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case3, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case3, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case3, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case3, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case3, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case3)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case3, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case3, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("digraph_descendants(case3)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DESCENDANTS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_descendants(case3)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("descendants(case4)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case4, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case4, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case4, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case4, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case4, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case4, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case4)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case4, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case4, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("digraph_descendants(case4)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DESCENDANTS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_descendants(case4)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("descendants(case5)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case5, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case5, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case5, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case5, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case5, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case5, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case5)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case5, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case5, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("digraph_descendants(case5)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    DIGRAPH_DESCENDANTS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_descendants(case5)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

// self-loop on the source -> empty result
TEST_CASE("descendants(case6)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case6, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case6, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case6, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case6, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case6, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case6, list_v_v, node_idx );

    DESCENDANTS_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case6)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case6, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case6, list_sv_sv_ct, node_idx );

    CONSTEXPR_DESCENDANTS_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("descendants(case7)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case7, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case7, list_a_v, node_idx );
    DESCENDANTS_SUBCASE( case7, list_sv_sv, node_idx );
    DESCENDANTS_SUBCASE( case7, list_sv_v, node_idx );
    DESCENDANTS_SUBCASE( case7, list_v_sv, node_idx );
    DESCENDANTS_SUBCASE( case7, list_v_v, node_idx );
}

TEST_CASE("constexpr_descendants(case7)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case7, list_a_sv_ct, node_idx );
    CONSTEXPR_DESCENDANTS_SUBCASE( case7, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_descendants(case7)" * doctest::test_suite("network::descendants"))
{
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_DESCENDANTS_SUBCASE( case7, list_v_v, src_node_ids, node_idx );
}

TEST_CASE("multi_digraph_descendants(case7)" * doctest::test_suite("network::descendants"))
{
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case7, list_v_v, src_node_ids, node_idx );
}

// empty graph -> Nothing
TEST_CASE("descendants(case8)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case8, list, node_idx );
}

TEST_CASE("constexpr_descendants(case8)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case8, list, node_idx_ct );
}

// multi-source: {0,1} on the diamond+cycle graph
TEST_CASE("descendants(case9)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case9, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case9, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case9, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case9, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case9, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case9, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case9, list, source_nodes );

    DIGRAPH_DESCENDANTS_SUBCASE( case9, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case9, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_descendants(case9)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case9, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case9, list_sv_sv_ct, source_nodes );
}

// multi-source: single-element seed set must equal the single-source result
TEST_CASE("descendants(case10)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case10, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case10, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case10, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case10, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case10, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case10, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case10, list, source_nodes );

    DESCENDANTS_SUBCASE( case10, list_a_sv, node_idx );
    DESCENDANTS_SUBCASE( case10, list, node_idx_ct );
}

TEST_CASE("constexpr_descendants(case10)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case10, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case10, list_sv_sv_ct, source_nodes );
}

// multi-source: two disconnected components + isolated node
TEST_CASE("descendants(case11)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case11, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case11, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case11, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case11, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case11, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case11, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case11, list, source_nodes );
}

TEST_CASE("constexpr_descendants(case11)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case11, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case11, list_sv_sv_ct, source_nodes );
}

// multi-source: seeds share one descendant -> reported once
TEST_CASE("descendants(case12)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case12, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case12, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case12, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case12, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case12, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case12, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case12, list, source_nodes );
}

TEST_CASE("constexpr_descendants(case12)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case12, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case12, list_sv_sv_ct, source_nodes );
}

// multi-source: one seed is a descendant of another seed (still excluded)
TEST_CASE("descendants(case13)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case13, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case13, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case13, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case13, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case13, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case13, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case13, list, source_nodes );

    DIGRAPH_DESCENDANTS_SUBCASE( case13, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case13, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_descendants(case13)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case13, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case13, list_sv_sv_ct, source_nodes );
}

// multi-source: descending + duplicate seeds must not change the result
TEST_CASE("descendants(case14)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case14, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case14, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case14, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case14, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case14, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case14, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case14, list, source_nodes );
}

TEST_CASE("constexpr_descendants(case14)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case14, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case14, list_sv_sv_ct, source_nodes );
}

// multi-source: one out-of-range seed -> Nothing
TEST_CASE("descendants(case15)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case15, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case15, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case15, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case15, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case15, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case15, list_v_v, source_nodes );
    // no digraph variants: map_ids on an index *array* input doesn't
    // bounds-check; the invalid digraph path is covered by case7.
}

TEST_CASE("constexpr_descendants(case15)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case15, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case15, list_sv_sv_ct, source_nodes );
}

// multi-source: every node is a seed -> empty result
TEST_CASE("descendants(case16)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case16, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case16, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case16, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case16, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case16, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case16, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case16, list, source_nodes );
}

TEST_CASE("constexpr_descendants(case16)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case16, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case16, list_sv_sv_ct, source_nodes );
}

// multi-source: empty seed set -> empty result
TEST_CASE("descendants(case17)" * doctest::test_suite("network::descendants"))
{
    DESCENDANTS_SUBCASE( case17, list_a_sv, source_nodes );
    DESCENDANTS_SUBCASE( case17, list_a_v, source_nodes );
    DESCENDANTS_SUBCASE( case17, list_sv_sv, source_nodes );
    DESCENDANTS_SUBCASE( case17, list_sv_v, source_nodes );
    DESCENDANTS_SUBCASE( case17, list_v_sv, source_nodes );
    DESCENDANTS_SUBCASE( case17, list_v_v, source_nodes );

    DESCENDANTS_SUBCASE( case17, list, source_nodes );

    DIGRAPH_DESCENDANTS_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_DESCENDANTS_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_descendants(case17)" * doctest::test_suite("network::descendants"))
{
    CONSTEXPR_DESCENDANTS_SUBCASE( case17, list_a_sv_ct, source_nodes );
    CONSTEXPR_DESCENDANTS_SUBCASE( case17, list_sv_sv_ct, source_nodes );
}
