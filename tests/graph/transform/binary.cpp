#include "nmtools/core/computational_graph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/core/transform/binary_fusion.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/transform/binary.hpp"

#define BINARY_SUBCASE(case_name, adj_list, src_node_ids, node_attributes, n_repeats) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( functional, transform_binary_fusion, case_name ); \
    using namespace args; \
    auto graph = nmtools::network::multi_digraph( adj_list, src_node_ids, node_attributes ); \
    { \
        auto src_graphviz = nmtools::utils::to_string(nmtools::unwrap(graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, src_graphviz ); \
        std::ofstream src_dot; \
        src_dot.open("src-graphviz.dot", std::ios::out | std::ios::trunc); \
        src_dot << src_graphviz << std::endl; \
    } \
    auto exp_graph = nmtools::network::multi_digraph( expect::adjacency_list, expect::node_ids, expect::node_attributes ); \
    { \
        auto exp_graphviz = nmtools::utils::to_string(nmtools::unwrap(exp_graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, exp_graphviz ); \
        std::ofstream exp_dot; \
        exp_dot.open("exp-graphviz.dot", std::ios::out | std::ios::trunc); \
        exp_dot << exp_graphviz << std::endl; \
    } \
    { \
        auto result = nmtools::functional::transform_binary_fusion( graph, n_repeats ); \
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).adjacency_list, expect::adjacency_list ); \
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).node_ids, expect::node_ids ); \
        \
        auto res_graphviz = nmtools::utils::to_string(nmtools::unwrap(result),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, res_graphviz ); \
        std::ofstream res_dot; \
        res_dot.open("res-graphviz.dot", std::ios::out | std::ios::trunc); \
        res_dot << res_graphviz << std::endl; \
    } \
}

TEST_CASE("binary(case1)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case1, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case1b)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case1b, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1b, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1b, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1b, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1b, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1b, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

// TODO: fix runtime, excess id
TEST_CASE("binary(case1c)" * doctest::test_suite("transform") * doctest::may_fail())
{
    BINARY_SUBCASE( case1c, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1c, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1c, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1c, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1c, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case1c, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case2)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case2, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case2, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case2, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case2, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case2, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case2, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case3a)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case3a, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3a, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3a, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3a, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3a, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3a, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case3b)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case3b, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3b, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3b, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3b, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3b, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3b, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case3c)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case3c, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3c, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3c, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3c, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3c, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3c, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case3d)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case3d, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3d, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3d, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3d, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3d, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3d, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("binary(case3e)" * doctest::test_suite("transform"))
{
    BINARY_SUBCASE( case3e, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3e, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3e, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3e, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3e, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    BINARY_SUBCASE( case3e, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}