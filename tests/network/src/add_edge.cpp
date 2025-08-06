#include "nmtools/network/add_edge.hpp"
#include "nmtools/testing/data/network/add_edge.hpp"
#include "nmtools/testing/doctest.hpp"

#define ADD_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, add_edge, case_name ); \
    using namespace args; \
    auto result = nmtools::network::add_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_ADD_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, add_edge, case_name ); \
    using namespace args; \
    constexpr auto result = nmtools::network::add_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("add_edge(case1)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case1, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case1, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case1, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case1, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case1, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case1, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case1, list_a_sv,  u_ct, v_ct );
    ADD_EDGE_SUBCASE( case1, list_a_v,   u_ct, v_ct );
    ADD_EDGE_SUBCASE( case1, list_sv_sv, u_ct, v_ct );
    ADD_EDGE_SUBCASE( case1, list_sv_v,  u_ct, v_ct );
    ADD_EDGE_SUBCASE( case1, list_v_sv,  u_ct, v_ct );
    ADD_EDGE_SUBCASE( case1, list_v_v,   u_ct, v_ct );

    ADD_EDGE_SUBCASE( case1, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case1)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case1, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case1, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case2)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case2, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case2, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case2, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case2, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case2, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case2, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case2, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case2)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case2, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case2, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case3)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case3, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case3, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case3, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case3, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case3, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case3, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case3, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case3)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case3, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case3, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case3b)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case3b, list_a_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case3b, list_a_v, u, v, multi );
    ADD_EDGE_SUBCASE( case3b, list_sv_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case3b, list_sv_v, u, v, multi );
    ADD_EDGE_SUBCASE( case3b, list_v_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case3b, list_v_v, u, v, multi );

    ADD_EDGE_SUBCASE( case3b, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("add_edge(case4)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case4, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case4, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case4, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case4, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case4, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case4, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case4, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case4)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case4, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case4, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case5)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case5, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case5, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case5, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case5, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case5, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case5, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case5, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case5)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case5, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case5, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case6)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case6, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case6, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case6, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case6, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case6, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case6, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case6, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case6)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case6, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case6, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case7)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case7, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case7, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case7, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case7, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case7, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case7, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case7, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case7)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case7, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case7, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case8)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case8, list_a_sv, u, v );
    ADD_EDGE_SUBCASE( case8, list_a_v, u, v );
    ADD_EDGE_SUBCASE( case8, list_sv_sv, u, v );
    ADD_EDGE_SUBCASE( case8, list_sv_v, u, v );
    ADD_EDGE_SUBCASE( case8, list_v_sv, u, v );
    ADD_EDGE_SUBCASE( case8, list_v_v, u, v );

    ADD_EDGE_SUBCASE( case8, list, u_ct, v_ct );
}

TEST_CASE("constexpr_add_edge(case8)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case8, list_a_sv_ct, u, v );
    CONSTEXPR_ADD_EDGE_SUBCASE( case8, list_sv_sv_ct, u, v );
}

TEST_CASE("add_edge(case9)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case9, list_a_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case9, list_a_v, u, v, multi );
    ADD_EDGE_SUBCASE( case9, list_sv_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case9, list_sv_v, u, v, multi );
    ADD_EDGE_SUBCASE( case9, list_v_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case9, list_v_v, u, v, multi );

    ADD_EDGE_SUBCASE( case9, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("constexpr_add_edge(case9)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case9, list_a_sv_ct, u, v, multi );
    CONSTEXPR_ADD_EDGE_SUBCASE( case9, list_sv_sv_ct, u, v, multi );
}

TEST_CASE("add_edge(case10)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case10, list_a_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case10, list_a_v, u, v, multi );
    ADD_EDGE_SUBCASE( case10, list_sv_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case10, list_sv_v, u, v, multi );
    ADD_EDGE_SUBCASE( case10, list_v_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case10, list_v_v, u, v, multi );

    ADD_EDGE_SUBCASE( case10, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("constexpr_add_edge(case10)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case10, list_a_sv_ct, u, v, multi );
    CONSTEXPR_ADD_EDGE_SUBCASE( case10, list_sv_sv_ct, u, v, multi );
}

TEST_CASE("add_edge(case11)" * doctest::test_suite("network::add_edge"))
{
    ADD_EDGE_SUBCASE( case11, list_a_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case11, list_a_v, u, v, multi );
    ADD_EDGE_SUBCASE( case11, list_sv_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case11, list_sv_v, u, v, multi );
    ADD_EDGE_SUBCASE( case11, list_v_sv, u, v, multi );
    ADD_EDGE_SUBCASE( case11, list_v_v, u, v, multi );

    ADD_EDGE_SUBCASE( case11, list, u_ct, v_ct, multi_ct );
}

TEST_CASE("constexpr_add_edge(case11)" * doctest::test_suite("network::add_edge"))
{
    CONSTEXPR_ADD_EDGE_SUBCASE( case11, list_a_sv_ct, u, v, multi );
    CONSTEXPR_ADD_EDGE_SUBCASE( case11, list_sv_sv_ct, u, v, multi );
}