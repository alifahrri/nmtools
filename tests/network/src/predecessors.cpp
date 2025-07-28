#include "nmtools/network/predecessors.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/predecessors.hpp"
#include "nmtools/testing/doctest.hpp"

#define PREDECESSORS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, predecessors, case_name); \
    using namespace args; \
    auto result = nmtools::network::predecessors(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::preds ); \
}

#define CONSTEXPR_PREDECESSORS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, predecessors, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::predecessors(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::preds ); \
}

#define DIGRAPH_PREDECESSORS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, predecessors, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::predecessors(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::preds,src_node_ids) ); \
}

#define MULTI_DIGRAPH_PREDECESSORS_SUBCASE(case_name, adj_list, src_node_ids, source) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, predecessors, case_name); \
    using namespace args; \
    auto source_id = nmtools::network::map_ids(source,src_node_ids); \
    auto digraph = nmtools::network::multi_digraph(adj_list,src_node_ids); \
    auto result = nmtools::network::predecessors(digraph,source_id); \
    NMTOOLS_ASSERT_EQUAL(result, nmtools::network::map_ids(expect::preds,src_node_ids) ); \
}

TEST_CASE("predecessors(case1)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case1, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case1, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case1, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_v_v, node_idx );

    PREDECESSORS_SUBCASE( case1, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case1)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case1, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case1, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case1)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case1)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case1, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("predecessors(case2)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case2, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case2, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case2, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_v_v, node_idx );

    PREDECESSORS_SUBCASE( case2, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case2)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case2, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case2, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case2)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case2)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case2, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("predecessors(case3)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case3, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case3, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case3, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_v_v, node_idx );

    PREDECESSORS_SUBCASE( case3, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case3)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case3, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case3, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case3)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case3)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case3, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("predecessors(case4)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case4, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case4, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case4, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_v_v, node_idx );

    PREDECESSORS_SUBCASE( case4, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case4)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case4, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case4, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case4)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case4)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case4, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("predecessors(case5)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case5, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case5, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case5, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_v_v, node_idx );

    PREDECESSORS_SUBCASE( case5, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case5)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case5, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case5, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case5)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case5)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list_v_v, src_node_ids, node_idx );

    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case5, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("predecessors(case6)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case6, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case6, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case6, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_v_v, node_idx );

    // node doesn't exists in adj list
    // TODO: better error message
    // PREDECESSORS_SUBCASE( case6, list, node_idx_ct );
}

TEST_CASE("constexpr_predecessors(case6)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case6, list_a_sv_ct, node_idx );
    CONSTEXPR_PREDECESSORS_SUBCASE( case6, list_sv_sv_ct, node_idx );
}

TEST_CASE("digraph_predecessors(case6)" * doctest::test_suite("network::predecessors"))
{
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case6, list_v_v, src_node_ids, node_idx );
    
    // DIGRAPH_PREDECESSORS_SUBCASE( case6, list, src_node_ids_ct, node_idx_ct );
}

TEST_CASE("multi_digraph_predecessors(case6)" * doctest::test_suite("network::predecessors"))
{
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_a_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_a_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_sv_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_sv_v, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_v_sv, src_node_ids, node_idx );
    MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list_v_v, src_node_ids, node_idx );
    
    // MULTI_DIGRAPH_PREDECESSORS_SUBCASE( case6, list, src_node_ids_ct, node_idx_ct );
}

// TEST_CASE("predecessors(case7)" * doctest::test_suite("network::predecessors"))
// {
//     PREDECESSORS_SUBCASE( case7, list_a_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_a_v, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_sv_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_sv_v, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_v_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_v_v, node_idx );
// }

TEST_CASE("predecessors(case8)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case8, list_a_sv );
    PREDECESSORS_SUBCASE( case8, list_a_v );
    PREDECESSORS_SUBCASE( case8, list_sv_sv );
    PREDECESSORS_SUBCASE( case8, list_sv_v );
    PREDECESSORS_SUBCASE( case8, list_v_sv );
    PREDECESSORS_SUBCASE( case8, list_v_v );

    PREDECESSORS_SUBCASE( case8, list );
}

TEST_CASE("constexpr_predecessors(case8)" * doctest::test_suite("network::predecessors"))
{
    CONSTEXPR_PREDECESSORS_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_PREDECESSORS_SUBCASE( case8, list_sv_sv_ct );
}

// TODO: fix isequal
#if 0
TEST_CASE("digraph_predecessors(case8)" * doctest::test_suite("network::predecessors"))
{
    auto node_idx = nmtools::None;
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_a_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_a_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_sv_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_sv_v, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_v_sv, src_node_ids, node_idx );
    DIGRAPH_PREDECESSORS_SUBCASE( case8, list_v_v, src_node_ids, node_idx );

    DIGRAPH_PREDECESSORS_SUBCASE( case8, list, src_node_ids_ct, node_idx );
}
#endif