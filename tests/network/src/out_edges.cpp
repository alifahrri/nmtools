#include "nmtools/network/out_edges.hpp"
#include "nmtools/testing/data/network/out_edges.hpp"
#include "nmtools/testing/doctest.hpp"

#define OUT_EDGES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, out_edges, case_name); \
    using namespace args; \
    auto result = nmtools::network::out_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges ); \
}

#define CONSTEXPR_OUT_EDGES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, out_edges, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::out_edges(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::edges ); \
}

TEST_CASE("out_edges(case1)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case1, list_a_sv );
    OUT_EDGES_SUBCASE(case1, list_a_v );
    OUT_EDGES_SUBCASE(case1, list_sv_sv );
    OUT_EDGES_SUBCASE(case1, list_sv_v );
    OUT_EDGES_SUBCASE(case1, list_v_sv );
    OUT_EDGES_SUBCASE(case1, list_v_v );

    OUT_EDGES_SUBCASE(case1, list );
}

TEST_CASE("constexpr_out_edges(case1)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("out_edges(case2)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case2, list_a_sv );
    OUT_EDGES_SUBCASE(case2, list_a_v );
    OUT_EDGES_SUBCASE(case2, list_sv_sv );
    OUT_EDGES_SUBCASE(case2, list_sv_v );
    OUT_EDGES_SUBCASE(case2, list_v_sv );
    OUT_EDGES_SUBCASE(case2, list_v_v );

    OUT_EDGES_SUBCASE(case2, list );
}

TEST_CASE("constexpr_out_edges(case2)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("out_edges(case3)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case3, list_a_sv );
    OUT_EDGES_SUBCASE(case3, list_a_v );
    OUT_EDGES_SUBCASE(case3, list_sv_sv );
    OUT_EDGES_SUBCASE(case3, list_sv_v );
    OUT_EDGES_SUBCASE(case3, list_v_sv );
    OUT_EDGES_SUBCASE(case3, list_v_v );

    OUT_EDGES_SUBCASE(case3, list );
}

TEST_CASE("constexpr_out_edges(case3)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("out_edges(case4)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case4, list_a_sv );
    OUT_EDGES_SUBCASE(case4, list_a_v );
    OUT_EDGES_SUBCASE(case4, list_sv_sv );
    OUT_EDGES_SUBCASE(case4, list_sv_v );
    OUT_EDGES_SUBCASE(case4, list_v_sv );
    OUT_EDGES_SUBCASE(case4, list_v_v );

    OUT_EDGES_SUBCASE(case4, list );
}

TEST_CASE("constexpr_out_edges(case4)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("out_edges(case5)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case5, list_a_sv );
    OUT_EDGES_SUBCASE(case5, list_a_v );
    OUT_EDGES_SUBCASE(case5, list_sv_sv );
    OUT_EDGES_SUBCASE(case5, list_sv_v );
    OUT_EDGES_SUBCASE(case5, list_v_sv );
    OUT_EDGES_SUBCASE(case5, list_v_v );

    OUT_EDGES_SUBCASE(case5, list );
}

TEST_CASE("constexpr_out_edges(case5)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("out_edges(case6)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case6, list_a_sv );
    OUT_EDGES_SUBCASE(case6, list_a_v );
    OUT_EDGES_SUBCASE(case6, list_sv_sv );
    OUT_EDGES_SUBCASE(case6, list_sv_v );
    OUT_EDGES_SUBCASE(case6, list_v_sv );
    OUT_EDGES_SUBCASE(case6, list_v_v );

    OUT_EDGES_SUBCASE(case6, list );
}

TEST_CASE("constexpr_out_edges(case6)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("out_edges(case7)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case7, list_a_sv );
    OUT_EDGES_SUBCASE(case7, list_a_v );
    OUT_EDGES_SUBCASE(case7, list_sv_sv );
    OUT_EDGES_SUBCASE(case7, list_sv_v );
    OUT_EDGES_SUBCASE(case7, list_v_sv );
    OUT_EDGES_SUBCASE(case7, list_v_v );

    OUT_EDGES_SUBCASE(case7, list );
}

TEST_CASE("constexpr_out_edges(case7)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("out_edges(case8)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case8, list_a_sv );
    OUT_EDGES_SUBCASE(case8, list_a_v );
    OUT_EDGES_SUBCASE(case8, list_sv_sv );
    OUT_EDGES_SUBCASE(case8, list_sv_v );
    OUT_EDGES_SUBCASE(case8, list_v_sv );
    OUT_EDGES_SUBCASE(case8, list_v_v );

    OUT_EDGES_SUBCASE(case8, list );
}

TEST_CASE("constexpr_out_edges(case8)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case8, list_sv_sv_ct );
}

TEST_CASE("out_edges(case9)" * doctest::test_suite("network::out_edges"))
{
    OUT_EDGES_SUBCASE(case9, list_a_sv );
    OUT_EDGES_SUBCASE(case9, list_a_v );
    OUT_EDGES_SUBCASE(case9, list_sv_sv );
    OUT_EDGES_SUBCASE(case9, list_sv_v );
    OUT_EDGES_SUBCASE(case9, list_v_sv );
    OUT_EDGES_SUBCASE(case9, list_v_v );

    OUT_EDGES_SUBCASE(case9, list );
}

TEST_CASE("constexpr_out_edges(case9)" * doctest::test_suite("network::out_edges"))
{
    CONSTEXPR_OUT_EDGES_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_OUT_EDGES_SUBCASE( case9, list_sv_sv_ct );
}