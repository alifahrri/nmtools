#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/transform/unary_fusion.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/transform/unary.hpp"

#define UNARY_SUBCASE(case_name, adj_list, src_node_ids, node_attributes, n_repeats) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( functional, transform_unary_fusion, case_name ); \
    using namespace args; \
    auto graph = nmtools::network::digraph( adj_list, src_node_ids, node_attributes ); \
    { \
        auto src_graphviz = nmtools::utils::to_string(nmtools::unwrap(graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, src_graphviz ); \
        std::ofstream src_dot; \
        src_dot.open("src-graphviz.dot", std::ios::out | std::ios::trunc); \
        src_dot << src_graphviz << std::endl; \
    } \
    { \
        auto exp_graph = nmtools::network::digraph( expect::adjacency_list, expect::node_ids, expect::node_attributes ); \
        auto exp_graphviz = nmtools::utils::to_string(nmtools::unwrap(exp_graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, exp_graphviz ); \
        std::ofstream exp_dot; \
        exp_dot.open("exp-graphviz.dot", std::ios::out | std::ios::trunc); \
        exp_dot << exp_graphviz << std::endl; \
    } \
    { \
        auto result = nmtools::functional::transform_unary_fusion( graph, n_repeats ); \
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).adjacency_list, expect::adjacency_list ); \
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).node_ids, expect::node_ids ); \
        auto src_graphviz = nmtools::utils::to_string(nmtools::unwrap(graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, src_graphviz ); \
        auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, graphviz ); \
        std::ofstream outputFile; \
        outputFile.open("res-graphviz.dot", std::ios::out | std::ios::trunc); \
        outputFile << graphviz << std::endl; \
    } \
}

#define CONSTEXPR_UNARY_SUBCASE(case_name, adj_list, src_node_ids, node_attributes, n_repeats) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( functional, transform_unary_fusion, case_name ); \
    using namespace args; \
    constexpr auto graph = nmtools::network::digraph( adj_list, src_node_ids, node_attributes ); \
    { \
        auto src_graphviz = nmtools::utils::to_string(nmtools::unwrap(graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, src_graphviz ); \
        std::ofstream src_dot; \
        src_dot.open("src-graphviz.dot", std::ios::out | std::ios::trunc); \
        src_dot << src_graphviz << std::endl; \
    } \
    { \
        auto exp_graph = nmtools::network::digraph( expect::adjacency_list, expect::node_ids, expect::node_attributes ); \
        auto exp_graphviz = nmtools::utils::to_string(nmtools::unwrap(exp_graph),nmtools::utils::Graphviz); \
        CHECK_MESSAGE( true, exp_graphviz ); \
        std::ofstream exp_dot; \
        exp_dot.open("exp-graphviz.dot", std::ios::out | std::ios::trunc); \
        exp_dot << exp_graphviz << std::endl; \
    } \
    constexpr auto result = nmtools::functional::transform_unary_fusion( graph, n_repeats ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).adjacency_list, expect::adjacency_list ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(result).node_ids, expect::node_ids ); \
    auto src_graphviz = nmtools::utils::to_string(nmtools::unwrap(graph),nmtools::utils::Graphviz); \
    CHECK_MESSAGE( true, src_graphviz ); \
    auto graphviz = nmtools::utils::to_string(nmtools::unwrap(result),nmtools::utils::Graphviz); \
    CHECK_MESSAGE( true, graphviz ); \
    std::ofstream outputFile; \
    outputFile.open("graphviz.dot", std::ios::out | std::ios::trunc); \
    outputFile << graphviz << std::endl; \
}

#if 1
TEST_CASE("unary(case1)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case1, adjacency_list_a_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case1, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case1, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case1, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case1, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case1, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case1)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case1, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case1, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}

TEST_CASE("unary(case2)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case2, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case2, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case2, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case2, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case2, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case2)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case2, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case2, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}

TEST_CASE("unary(case3)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case3, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case3, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case3, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case3, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case3, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case3)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case3, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case3, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}

TEST_CASE("unary(case4)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case4, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case4, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case4, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case4, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case4, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case4)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case4, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case4, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}

TEST_CASE("unary(case5)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case5, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case5, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case5, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case5, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case5, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case5)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case5, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case5, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}

TEST_CASE("unary(case6)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case6, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

TEST_CASE("constexpr_unary(case6)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case6, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case6, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}
#endif

TEST_CASE("unary(case6b)" * doctest::test_suite("transform"))
{
    UNARY_SUBCASE( case6b, adjacency_list_a_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6b, adjacency_list_sv_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6b, adjacency_list_sv_v, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6b, adjacency_list_v_sv, node_ids, node_attributes, n_repeats );
    UNARY_SUBCASE( case6b, adjacency_list_v_v, node_ids, node_attributes, n_repeats );
}

#if 1
TEST_CASE("constexpr_unary(case6)" * doctest::test_suite("transform"))
{
    CONSTEXPR_UNARY_SUBCASE( case6b, adjacency_list_a_sv_ct, node_ids, node_attributes, n_repeats );
    CONSTEXPR_UNARY_SUBCASE( case6b, adjacency_list_sv_sv_ct, node_ids, node_attributes, n_repeats );
}
#endif