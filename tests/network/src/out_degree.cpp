#include "nmtools/network/digraph.hpp"
#include "nmtools/network/out_degree.hpp"
#include "nmtools/testing/data/network/out_degree.hpp"
#include "nmtools/context/default.hpp"
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

TEST_CASE("out_degree(case1)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case1, list );
    OUT_DEGREE_SUBCASE(case1, list_a_sv );
    OUT_DEGREE_SUBCASE(case1, list_a_v );
    OUT_DEGREE_SUBCASE(case1, list_sv_sv );
    OUT_DEGREE_SUBCASE(case1, list_sv_v );
    OUT_DEGREE_SUBCASE(case1, list_v_sv );
    OUT_DEGREE_SUBCASE(case1, list_v_v );
}

TEST_CASE("out_degree(case2)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case2, list );
    OUT_DEGREE_SUBCASE(case2, list_a_sv );
    OUT_DEGREE_SUBCASE(case2, list_a_v );
    OUT_DEGREE_SUBCASE(case2, list_sv_sv );
    OUT_DEGREE_SUBCASE(case2, list_sv_v );
    OUT_DEGREE_SUBCASE(case2, list_v_sv );
    OUT_DEGREE_SUBCASE(case2, list_v_v );
}

TEST_CASE("out_degree(case3)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case3, list );
    OUT_DEGREE_SUBCASE(case3, list_a_sv );
    OUT_DEGREE_SUBCASE(case3, list_a_v );
    OUT_DEGREE_SUBCASE(case3, list_sv_sv );
    OUT_DEGREE_SUBCASE(case3, list_sv_v );
    OUT_DEGREE_SUBCASE(case3, list_v_sv );
    OUT_DEGREE_SUBCASE(case3, list_v_v );
}

TEST_CASE("out_degree(case4)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case4, list );
    OUT_DEGREE_SUBCASE(case4, list_a_sv );
    OUT_DEGREE_SUBCASE(case4, list_a_v );
    OUT_DEGREE_SUBCASE(case4, list_sv_sv );
    OUT_DEGREE_SUBCASE(case4, list_sv_v );
    OUT_DEGREE_SUBCASE(case4, list_v_sv );
    OUT_DEGREE_SUBCASE(case4, list_v_v );
}

TEST_CASE("out_degree(case5)" * doctest::test_suite("network::out_degree"))
{
    OUT_DEGREE_SUBCASE(case5, list );
    OUT_DEGREE_SUBCASE(case5, list_a_sv );
    OUT_DEGREE_SUBCASE(case5, list_a_v );
    OUT_DEGREE_SUBCASE(case5, list_sv_sv );
    OUT_DEGREE_SUBCASE(case5, list_sv_v );
    OUT_DEGREE_SUBCASE(case5, list_v_sv );
    OUT_DEGREE_SUBCASE(case5, list_v_v );
}

TEST_CASE("digraph.out_degree(case1)" * doctest::test_suite("network"))
{
    NMTOOLS_TESTING_USE_CASE(network, out_degree, case1);
    using namespace args;
    auto g = nmtools::network::digraph(list,nmtools::None,node_attributes);
    const auto pairs = g.out_degree();
    NMTOOLS_ASSERT_EQUAL( pairs.size(), 5 );

    // static_assert( !nmtools::is_reference_v<decltype(pairs)::first_type> );
    // static_assert( !nmtools::is_reference_v<decltype(pairs)::second_type> );
    NMTOOLS_ASSERT_EQUAL( pairs.second, expect::degrees );
}