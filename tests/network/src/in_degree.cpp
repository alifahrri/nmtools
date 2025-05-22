#include "nmtools/network/in_degree.hpp"
#include "nmtools/testing/data/network/in_degree.hpp"
#include "nmtools/testing/doctest.hpp"

#define IN_DEGREE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_degree, case_name); \
    using namespace args; \
    auto result = nmtools::network::in_degree(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

#define CONSTEXPR_IN_DEGREE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, in_degree, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::in_degree(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

TEST_CASE("in_degree(case1)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case1, list );
    IN_DEGREE_SUBCASE( case1, list_a_sv );
    IN_DEGREE_SUBCASE( case1, list_a_v );
    IN_DEGREE_SUBCASE( case1, list_sv_sv );
    IN_DEGREE_SUBCASE( case1, list_sv_v );
    IN_DEGREE_SUBCASE( case1, list_v_sv );
    IN_DEGREE_SUBCASE( case1, list_v_v );
}

TEST_CASE("constexpr_in_degree(case1)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case1, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case1, list_a_sv_ct );
}

TEST_CASE("in_degree(case2)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case2, list );
    IN_DEGREE_SUBCASE( case2, list_a_sv );
    IN_DEGREE_SUBCASE( case2, list_a_v );
    IN_DEGREE_SUBCASE( case2, list_sv_sv );
    IN_DEGREE_SUBCASE( case2, list_sv_v );
    IN_DEGREE_SUBCASE( case2, list_v_sv );
    IN_DEGREE_SUBCASE( case2, list_v_v );
}

TEST_CASE("constexpr_in_degree(case2)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case2, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case2, list_a_sv_ct );
}

TEST_CASE("in_degree(case3)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case3, list );
    IN_DEGREE_SUBCASE( case3, list_a_sv );
    IN_DEGREE_SUBCASE( case3, list_a_v );
    IN_DEGREE_SUBCASE( case3, list_sv_sv );
    IN_DEGREE_SUBCASE( case3, list_sv_v );
    IN_DEGREE_SUBCASE( case3, list_v_sv );
    IN_DEGREE_SUBCASE( case3, list_v_v );
}

TEST_CASE("constexpr_in_degree(case3)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case3, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case3, list_a_sv_ct );
}

TEST_CASE("in_degree(case4)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case4, list );
    IN_DEGREE_SUBCASE( case4, list_a_sv );
    IN_DEGREE_SUBCASE( case4, list_a_v );
    IN_DEGREE_SUBCASE( case4, list_sv_sv );
    IN_DEGREE_SUBCASE( case4, list_sv_v );
    IN_DEGREE_SUBCASE( case4, list_v_sv );
    IN_DEGREE_SUBCASE( case4, list_v_v );
}

TEST_CASE("constexpr_in_degree(case4)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case4, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case4, list_a_sv_ct );
}

TEST_CASE("in_degree(case5)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case5, list );
    IN_DEGREE_SUBCASE( case5, list_a_sv );
    IN_DEGREE_SUBCASE( case5, list_a_v );
    IN_DEGREE_SUBCASE( case5, list_sv_sv );
    IN_DEGREE_SUBCASE( case5, list_sv_v );
    IN_DEGREE_SUBCASE( case5, list_v_sv );
    IN_DEGREE_SUBCASE( case5, list_v_v );
}

TEST_CASE("constexpr_in_degree(case5)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case5, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case5, list_a_sv_ct );
}

TEST_CASE("in_degree(case6)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case6, list );
    IN_DEGREE_SUBCASE( case6, list_a_sv );
    IN_DEGREE_SUBCASE( case6, list_a_v );
    IN_DEGREE_SUBCASE( case6, list_sv_sv );
    IN_DEGREE_SUBCASE( case6, list_sv_v );
    IN_DEGREE_SUBCASE( case6, list_v_sv );
    IN_DEGREE_SUBCASE( case6, list_v_v );
}

TEST_CASE("constexpr_in_degree(case6)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case6, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case6, list_a_sv_ct );
}

TEST_CASE("in_degree(case7)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case7, list );
    IN_DEGREE_SUBCASE( case7, list_a_sv );
    IN_DEGREE_SUBCASE( case7, list_a_v );
    IN_DEGREE_SUBCASE( case7, list_sv_sv );
    IN_DEGREE_SUBCASE( case7, list_sv_v );
    IN_DEGREE_SUBCASE( case7, list_v_sv );
    IN_DEGREE_SUBCASE( case7, list_v_v );
}

TEST_CASE("constexpr_in_degree(case7)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case7, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case7, list_a_sv_ct );
}

TEST_CASE("in_degree(case8)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case8, list );
    IN_DEGREE_SUBCASE( case8, list_a_sv );
    IN_DEGREE_SUBCASE( case8, list_a_v );
    IN_DEGREE_SUBCASE( case8, list_sv_sv );
    IN_DEGREE_SUBCASE( case8, list_sv_v );
    IN_DEGREE_SUBCASE( case8, list_v_sv );
    IN_DEGREE_SUBCASE( case8, list_v_v );
}

TEST_CASE("constexpr_in_degree(case8)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case8, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case8, list_a_sv_ct );
}

TEST_CASE("in_degree(case9)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case9, list );
    IN_DEGREE_SUBCASE( case9, list_a_sv );
    IN_DEGREE_SUBCASE( case9, list_a_v );
    IN_DEGREE_SUBCASE( case9, list_sv_sv );
    IN_DEGREE_SUBCASE( case9, list_sv_v );
    IN_DEGREE_SUBCASE( case9, list_v_sv );
    IN_DEGREE_SUBCASE( case9, list_v_v );
}

TEST_CASE("constexpr_in_degree(case10)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case9, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case9, list_a_sv_ct );
}

TEST_CASE("in_degree(case10)" * doctest::test_suite("network::in_degree"))
{
    IN_DEGREE_SUBCASE( case10, list );
    IN_DEGREE_SUBCASE( case10, list_a_sv );
    IN_DEGREE_SUBCASE( case10, list_a_v );
    IN_DEGREE_SUBCASE( case10, list_sv_sv );
    IN_DEGREE_SUBCASE( case10, list_sv_v );
    IN_DEGREE_SUBCASE( case10, list_v_sv );
    IN_DEGREE_SUBCASE( case10, list_v_v );
}

TEST_CASE("constexpr_in_degree(case10)" * doctest::test_suite("network::in_degree"))
{
    CONSTEXPR_IN_DEGREE_SUBCASE( case10, list );
    CONSTEXPR_IN_DEGREE_SUBCASE( case10, list_a_sv_ct );
}