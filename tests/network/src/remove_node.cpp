#include "nmtools/network/remove_node.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/testing/data/network/remove_node.hpp"
#include "nmtools/testing/doctest.hpp"

#define REMOVE_NODE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, remove_node, case_name ); \
    using namespace args; \
    auto result = nmtools::network::remove_node(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("remove_node(case1)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case1, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case1, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case1, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case1, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case1, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case1, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case2)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case2, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case2, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case2, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case2, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case2, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case2, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case3)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case3, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case3, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case3, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case3, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case3, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case3, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case4)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case4, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case4, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case4, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case4, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case4, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case4, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case5)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case5, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case5, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case5, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case5, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case5, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case5, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case6)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case6, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case6, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case6, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case6, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case6, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case6, list_v_v, node_to_remove );
}

TEST_CASE("remove_node(case7)" * doctest::test_suite("network::remove_node"))
{
    REMOVE_NODE_SUBCASE( case7, list_a_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case7, list_a_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case7, list_sv_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case7, list_sv_v, node_to_remove );
    REMOVE_NODE_SUBCASE( case7, list_v_sv, node_to_remove );
    REMOVE_NODE_SUBCASE( case7, list_v_v, node_to_remove );
}