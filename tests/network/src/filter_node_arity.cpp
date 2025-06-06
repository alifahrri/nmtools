#include "nmtools/network/filter_node_arity.hpp"
#include "nmtools/testing/data/network/filter_node_arity.hpp"
#include "nmtools/testing/doctest.hpp"

#define FILTER_NODE_ARITY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, filter_node_arity, case_name); \
    using namespace args; \
    auto result = nmtools::network::filter_node_arity(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result_nodes ); \
}

#define CONSTEXPR_FILTER_NODE_ARITY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, filter_node_arity, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::filter_node_arity(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result_nodes ); \
}

TEST_CASE("filter_node_arity(case1)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case1, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case1, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case1, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case1, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case1, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case1, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case1, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case1, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case1, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case1)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case1, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case1, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case2)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case2, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case2, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case2, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case2, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case2, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case2, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case2, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case2, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case2, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case2)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case2, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case2, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case3)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case3, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case3, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case3, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case3, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case3, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case3, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case3, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case3, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case3, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case3)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case3, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case3, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case4)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case4, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case4, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case4, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case4, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case4, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case4, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case4, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case4, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case4, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case4)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case4, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case4, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case5)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case5, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case5, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case5, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case5, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case5, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case5, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case5, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case5, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case5, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case5)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case5, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case5, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case6)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case6, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case6, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case6, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case6, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case6, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case6, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case6, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case6, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case6, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case6)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case6, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case6, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case7)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case7, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case7, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case7, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case7, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case7, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case7, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case7, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case7, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case7, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case7)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case7, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case7, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case8)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case8, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case8, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case8, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case8, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case8, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case8, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case8, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case8, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case8, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case8)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case8, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case8, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case9)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case9, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case9, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case9, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case9, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case9, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case9, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case9, list_a_sv, arity_ct );
    // FILTER_NODE_ARITY_SUBCASE( case9, list, arity_ct );
    // FILTER_NODE_ARITY_SUBCASE( case9, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case9)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case9, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case9, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case10)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case10, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case10, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case10, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case10, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case10, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case10, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case10, list_a_sv, arity_ct );
    // FILTER_NODE_ARITY_SUBCASE( case10, list, arity_ct );
    // FILTER_NODE_ARITY_SUBCASE( case10, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case10)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case10, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case10, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case11)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case11, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case11, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case11, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case11, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case11, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case11, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case11, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case11, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case11, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case11)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case11, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case11, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case12)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case12, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case12, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case12, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case12, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case12, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case12, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case12, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case12, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case12, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case12)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case12, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case12, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case13)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case13, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case13, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case13, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case13, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case13, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case13, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case13, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case13, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case13, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case13)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case13, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case13, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case14)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case14, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case14, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case14, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case14, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case14, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case14, list_v_v, arity );

    FILTER_NODE_ARITY_SUBCASE( case14, list_a_sv, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case14, list, arity_ct );
    FILTER_NODE_ARITY_SUBCASE( case14, list, arity );
}

TEST_CASE("constexpr_filter_node_arity(case14)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case14, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case14, list_sv_sv_ct, arity );
}

TEST_CASE("filter_node_arity(case15)" * doctest::test_suite("network::filter_node_arity"))
{
    FILTER_NODE_ARITY_SUBCASE( case15, list_a_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case15, list_a_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case15, list_sv_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case15, list_sv_v, arity );
    FILTER_NODE_ARITY_SUBCASE( case15, list_v_sv, arity );
    FILTER_NODE_ARITY_SUBCASE( case15, list_v_v, arity );
}

TEST_CASE("constexpr_filter_node_arity(case15)" * doctest::test_suite("network::filter_node_arity"))
{
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case15, list_a_sv_ct, arity );
    CONSTEXPR_FILTER_NODE_ARITY_SUBCASE( case15, list_sv_sv_ct, arity );
}