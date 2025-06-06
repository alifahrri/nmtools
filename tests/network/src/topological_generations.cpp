#include "nmtools/network/topological_generations.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/testing/data/network/topological_generations.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::unwrap;
using namespace nmtools::literals;

#define TOPOLOGICAL_GENERATIONS_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network,topological_generations,case_name); \
    using namespace args; \
    auto result = nmtools::network::topological_generations(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::generations ); \
}

#define CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network,topological_generations,case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::topological_generations(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::generations ); \
}

#define DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE(case_name, list, node_ids) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, topological_generations, case_name); \
    using namespace args; \
    auto digraph = nmtools::network::digraph(list,node_ids); \
    auto result = nmtools::network::topological_generations(digraph); \
    NMTOOLS_ASSERT_EQUAL( result, nmtools::network::map_ids(expect::generations,node_ids) ); \
}

TEST_CASE("topological_generations(case1)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list );
}

TEST_CASE("constexpr_topological_generations(case1)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case1)" * doctest::test_suite("network::topological_generations"))
{
    // auto node_ids = nmtools_tuple{};
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_a_sv, node_ids );
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_a_v, node_ids );
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_sv_sv, node_ids );
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_sv_v, node_ids );
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_v_sv, node_ids );
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list_v_v, node_ids );

    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case1, list );
}

TEST_CASE("topological_generations(case2)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list );
}

TEST_CASE("constexpr_topological_generations(case2)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case2)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case2, list, node_ids );
}

TEST_CASE("topological_generations(case3)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list );
}

TEST_CASE("digraph_topological_generations(case2)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list, node_ids );
}

TEST_CASE("constexpr_topological_generations(case3)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("topological_generations(case4)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list );
}

TEST_CASE("constexpr_topological_generations(case4)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case4)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case4, list, node_ids );
}

TEST_CASE("topological_generations(case5)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list );
}

TEST_CASE("constexpr_topological_generations(case5)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case2)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case5, list, node_ids );
}

TEST_CASE("topological_generations(case6)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list );
}

TEST_CASE("digraph_topological_generations(case6)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list, node_ids );
}

TEST_CASE("constexpr_topological_generations(case6)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("topological_generations(case7)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list );
}

TEST_CASE("digraph_topological_generations(case7)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct,8_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list, node_ids );
}

TEST_CASE("constexpr_topological_generations(case7)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("topological_generations(case8)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_v_v );

    TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list );
}

TEST_CASE("constexpr_topological_generations(case8)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case8)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct,7_ct,8_ct,9_ct,10_ct,11_ct,12_ct,13_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list_v_v, node_ids );

    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case8, list, node_ids );
}

TEST_CASE("topological_generations(case9)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_v_v );

    // trigger assert at compile-time (which is correct)
    // TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list );
}

TEST_CASE("constexpr_topological_generations(case9)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case9)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list_v_v, node_ids );

    // failed to compile (correct)
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case9, list, node_ids );
}

TEST_CASE("topological_generations(case10)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_v_v );

    // trigger assert at compile-time (which is correct)
    // TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list );
}

TEST_CASE("constexpr_topological_generations(case10)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case10)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list_v_v, node_ids );

    // failed to compile (correct)
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case10, list, node_ids );
}

TEST_CASE("topological_generations(case11)" * doctest::test_suite("network::topological_generations"))
{
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_a_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_a_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_sv_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_sv_v );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_v_sv );
    TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_v_v );

    // trigger assert at compile-time (which is correct)
    // TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list );
}

TEST_CASE("constexpr_topological_generations(case11)" * doctest::test_suite("network::topological_generations"))
{
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_a_sv_ct );
    CONSTEXPR_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_sv_sv_ct );
}

TEST_CASE("digraph_topological_generations(case11)" * doctest::test_suite("network::topological_generations"))
{
    auto node_ids = nmtools_tuple{3_ct,4_ct,5_ct,6_ct};
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_a_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_a_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_sv_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_sv_v, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_v_sv, node_ids );
    DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list_v_v, node_ids );

    // failed to compile (correct)
    // DIGRAPH_TOPOLOGICAL_GENERATIONS_SUBCASE( case11, list, node_ids );
}