#include "nmtools/network/ancestors.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/ancestors.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define ANCESTORS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, ancestors, case_name); \
    using namespace args; \
    auto result = nmtools::network::ancestors(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::ancestors ); \
}

#define CONSTEXPR_ANCESTORS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, ancestors, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::ancestors(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::ancestors ); \
}

#define DIGRAPH_ANCESTORS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, ancestors, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::ancestors(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::ancestors,src_node_ids) ); \
}

#define MULTI_DIGRAPH_ANCESTORS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, ancestors, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::ancestors(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::ancestors,src_node_ids) ); \
}

TEST_CASE("ancestors(case1)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case1, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case1, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case1, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case1, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case1, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case1, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case1, list, node_idx_ct );
}
TEST_CASE("constexpr_ancestors(case1)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case1, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case1, list_sv_sv_ct, node_idx );

    // constant adjacency list + constant node index
    CONSTEXPR_ANCESTORS_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("digraph_ancestors(case1)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    DIGRAPH_ANCESTORS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_ancestors(case1)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("ancestors(case2)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case2, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case2, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case2, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case2, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case2, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case2, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case2)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case2, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case2, list_sv_sv_ct, node_idx );

    CONSTEXPR_ANCESTORS_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("digraph_ancestors(case2)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    DIGRAPH_ANCESTORS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_ancestors(case2)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("ancestors(case3)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case3, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case3, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case3, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case3, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case3, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case3, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case3)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case3, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case3, list_sv_sv_ct, node_idx );

    CONSTEXPR_ANCESTORS_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("digraph_ancestors(case3)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    DIGRAPH_ANCESTORS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_ancestors(case3)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

// cyclic graph: reverse BFS must terminate and exclude the source
TEST_CASE("ancestors(case4)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case4, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case4, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case4, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case4, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case4, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case4, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case4)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case4, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case4, list_sv_sv_ct, node_idx );

    CONSTEXPR_ANCESTORS_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("digraph_ancestors(case4)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    DIGRAPH_ANCESTORS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_ancestors(case4)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("ancestors(case5)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case5, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case5, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case5, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case5, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case5, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case5, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case5)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case5, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case5, list_sv_sv_ct, node_idx );

    CONSTEXPR_ANCESTORS_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("digraph_ancestors(case5)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    DIGRAPH_ANCESTORS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_ancestors(case5)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

// self-loop on source: never resurrected
TEST_CASE("ancestors(case6)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case6, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case6, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case6, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case6, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case6, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case6, list_v_v, node_idx );

    ANCESTORS_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case6)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case6, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case6, list_sv_sv_ct, node_idx );

    CONSTEXPR_ANCESTORS_SUBCASE( case6, list, node_idx_ct );
}

// source out of range -> Nothing
TEST_CASE("ancestors(case7)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case7, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case7, list_a_v, node_idx );
    ANCESTORS_SUBCASE( case7, list_sv_sv, node_idx );
    ANCESTORS_SUBCASE( case7, list_sv_v, node_idx );
    ANCESTORS_SUBCASE( case7, list_v_sv, node_idx );
    ANCESTORS_SUBCASE( case7, list_v_v, node_idx );
}

TEST_CASE("constexpr_ancestors(case7)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case7, list_a_sv_ct, node_idx );
    CONSTEXPR_ANCESTORS_SUBCASE( case7, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_ancestors(case7)" * doctest::test_suite("network::ancestors"))
{
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_ANCESTORS_SUBCASE( case7, list_v_v, src_node_ids, node_idx );
}

TEST_CASE("multi_digraph_ancestors(case7)" * doctest::test_suite("network::ancestors"))
{
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case7, list_v_v, src_node_ids, node_idx );
}

// empty graph -> Nothing
TEST_CASE("ancestors(case8)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case8, list, node_idx );
}

// empty graph -> Nothing (constant path falls back to runtime container)
TEST_CASE("constexpr_ancestors(case8)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case8, list, node_idx_ct );
}

// multi-source overload (stackifier live-set use case), cases 9-17.
// The digraph overload accepts a container of node ids as well, so the
// multi-source cases are also exercised through digraph/multi_digraph.
TEST_CASE("ancestors(case9)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case9, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case9, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case9, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case9, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case9, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case9, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case9, list, source_nodes );

    // multi-source through the digraph overload (container of node ids)
    DIGRAPH_ANCESTORS_SUBCASE( case9, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case9, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_ancestors(case9)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case9, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case9, list_sv_sv_ct, source_nodes );
}

// multi-source: single-element seed set must equal the single-source result
TEST_CASE("ancestors(case10)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case10, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case10, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case10, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case10, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case10, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case10, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case10, list, source_nodes );

    // same expectation from the single-source overload
    ANCESTORS_SUBCASE( case10, list_a_sv, node_idx );
    ANCESTORS_SUBCASE( case10, list, node_idx_ct );
}

TEST_CASE("constexpr_ancestors(case10)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case10, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case10, list_sv_sv_ct, source_nodes );
}

// multi-source: two disconnected components + isolated node
TEST_CASE("ancestors(case11)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case11, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case11, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case11, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case11, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case11, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case11, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case11, list, source_nodes );
}

TEST_CASE("constexpr_ancestors(case11)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case11, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case11, list_sv_sv_ct, source_nodes );
}

// multi-source: seeds share one ancestor -> reported once
TEST_CASE("ancestors(case12)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case12, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case12, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case12, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case12, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case12, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case12, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case12, list, source_nodes );
}

TEST_CASE("constexpr_ancestors(case12)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case12, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case12, list_sv_sv_ct, source_nodes );
}

// multi-source: one seed is an ancestor of another seed (still excluded)
TEST_CASE("ancestors(case13)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case13, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case13, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case13, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case13, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case13, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case13, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case13, list, source_nodes );

    DIGRAPH_ANCESTORS_SUBCASE( case13, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case13, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_ancestors(case13)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case13, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case13, list_sv_sv_ct, source_nodes );
}

// multi-source: descending + duplicate seeds must not change the result
TEST_CASE("ancestors(case14)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case14, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case14, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case14, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case14, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case14, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case14, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case14, list, source_nodes );
}

TEST_CASE("constexpr_ancestors(case14)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case14, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case14, list_sv_sv_ct, source_nodes );
}

// multi-source: one out-of-range seed -> Nothing
TEST_CASE("ancestors(case15)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case15, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case15, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case15, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case15, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case15, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case15, list_v_v, source_nodes );
    // NOTE: no digraph variants here -- map_ids on an index *array* input
    // doesn't bounds-check, so the out-of-range seed can't be mapped to a
    // node id. The invalid path through the digraph overload is covered by
    // case7 (single source, map_ids scalar branch -> Nothing).
}

TEST_CASE("constexpr_ancestors(case15)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case15, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case15, list_sv_sv_ct, source_nodes );
}

// multi-source: every node is a seed -> empty result
TEST_CASE("ancestors(case16)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case16, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case16, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case16, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case16, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case16, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case16, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case16, list, source_nodes );
}

TEST_CASE("constexpr_ancestors(case16)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case16, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case16, list_sv_sv_ct, source_nodes );
}

// multi-source: empty seed set -> empty result
TEST_CASE("ancestors(case17)" * doctest::test_suite("network::ancestors"))
{
    ANCESTORS_SUBCASE( case17, list_a_sv, source_nodes );
    ANCESTORS_SUBCASE( case17, list_a_v, source_nodes );
    ANCESTORS_SUBCASE( case17, list_sv_sv, source_nodes );
    ANCESTORS_SUBCASE( case17, list_sv_v, source_nodes );
    ANCESTORS_SUBCASE( case17, list_v_sv, source_nodes );
    ANCESTORS_SUBCASE( case17, list_v_v, source_nodes );

    ANCESTORS_SUBCASE( case17, list, source_nodes );

    DIGRAPH_ANCESTORS_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
    MULTI_DIGRAPH_ANCESTORS_SUBCASE( case17, list_a_sv, src_node_ids, source_nodes );
}

TEST_CASE("constexpr_ancestors(case17)" * doctest::test_suite("network::ancestors"))
{
    CONSTEXPR_ANCESTORS_SUBCASE( case17, list_a_sv_ct, source_nodes );
    CONSTEXPR_ANCESTORS_SUBCASE( case17, list_sv_sv_ct, source_nodes );
}