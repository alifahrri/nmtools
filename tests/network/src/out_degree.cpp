#include "nmtools/network/out_degree.hpp"
#include "nmtools/testing/data/network/out_degree.hpp"
#include "nmtools/testing/doctest.hpp"

#define OUT_DEGREE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, out_degree, case_name); \
    using namespace args; \
    auto result = nmtools::network::out_degree(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::degrees) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

TEST_CASE("out_degeree(case1)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case1, list );
    OUT_DEGREE_SUBCASE(case1, list_a_sv );
    OUT_DEGREE_SUBCASE(case1, list_a_v );
    OUT_DEGREE_SUBCASE(case1, list_sv_sv );
    OUT_DEGREE_SUBCASE(case1, list_sv_v );
    OUT_DEGREE_SUBCASE(case1, list_v_sv );
    OUT_DEGREE_SUBCASE(case1, list_v_v );
}

TEST_CASE("out_degeree(case2)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case2, list );
    OUT_DEGREE_SUBCASE(case2, list_a_sv );
    OUT_DEGREE_SUBCASE(case2, list_a_v );
    OUT_DEGREE_SUBCASE(case2, list_sv_sv );
    OUT_DEGREE_SUBCASE(case2, list_sv_v );
    OUT_DEGREE_SUBCASE(case2, list_v_sv );
    OUT_DEGREE_SUBCASE(case2, list_v_v );
}

TEST_CASE("out_degeree(case3)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case3, list );
    OUT_DEGREE_SUBCASE(case3, list_a_sv );
    OUT_DEGREE_SUBCASE(case3, list_a_v );
    OUT_DEGREE_SUBCASE(case3, list_sv_sv );
    OUT_DEGREE_SUBCASE(case3, list_sv_v );
    OUT_DEGREE_SUBCASE(case3, list_v_sv );
    OUT_DEGREE_SUBCASE(case3, list_v_v );
}

TEST_CASE("out_degeree(case4)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case4, list );
    OUT_DEGREE_SUBCASE(case4, list_a_sv );
    OUT_DEGREE_SUBCASE(case4, list_a_v );
    OUT_DEGREE_SUBCASE(case4, list_sv_sv );
    OUT_DEGREE_SUBCASE(case4, list_sv_v );
    OUT_DEGREE_SUBCASE(case4, list_v_sv );
    OUT_DEGREE_SUBCASE(case4, list_v_v );
}

TEST_CASE("out_degeree(case5)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case5, list );
    OUT_DEGREE_SUBCASE(case5, list_a_sv );
    OUT_DEGREE_SUBCASE(case5, list_a_v );
    OUT_DEGREE_SUBCASE(case5, list_sv_sv );
    OUT_DEGREE_SUBCASE(case5, list_sv_v );
    OUT_DEGREE_SUBCASE(case5, list_v_sv );
    OUT_DEGREE_SUBCASE(case5, list_v_v );
}