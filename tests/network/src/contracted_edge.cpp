#include "nmtools/network/contracted_edge.hpp"
#include "nmtools/testing/data/network/contracted_edge.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONTRACTED_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, contracted_edge, case_name ); \
    using namespace args; \
    auto result = nmtools::network::contracted_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::contracted_list ); \
}

#define CONSTEXPR_CONTRACTED_EDGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( network, contracted_edge, case_name ); \
    using namespace args; \
    constexpr auto result = nmtools::network::contracted_edge( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::contracted_list ); \
}

TEST_CASE("contracted_edge(case1)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case1, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case1, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case1, list, edge_to_contract_ct, self_loops_flag_ct )
}

TEST_CASE("constexpr_contracted_edge(case1)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case1, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case1, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case2)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case2, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case2, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case2, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case2)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case2, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case2, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case3)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case3, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case3, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case3, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case3)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case3, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case3, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case4)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case4, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case4, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case4, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif 

TEST_CASE("constexpr_contracted_edge(case4)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case4, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case4, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case5)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case5, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case5, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case5, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case5)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case5, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case5, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

TEST_CASE("contracted_edge(case6)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case6, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case6, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case6, list, edge_to_contract_ct, self_loops_flag_ct )
}

TEST_CASE("constexpr_contracted_edge(case6)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case6, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case6, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}

#if 1
TEST_CASE("contracted_edge(case7)" * doctest::test_suite("network::contracted_edge"))
{
    CONTRACTED_EDGE_SUBCASE( case7, list_a_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_a_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_sv_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_sv_v, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_v_sv, edge_to_contract, self_loops_flag )
    CONTRACTED_EDGE_SUBCASE( case7, list_v_v, edge_to_contract, self_loops_flag )

    CONTRACTED_EDGE_SUBCASE( case7, list, edge_to_contract_ct, self_loops_flag_ct )
}
#endif

TEST_CASE("constexpr_contracted_edge(case7)" * doctest::test_suite("network::contracted_edge"))
{
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case7, list_a_sv_ct, edge_to_contract, self_loops_flag )
    CONSTEXPR_CONTRACTED_EDGE_SUBCASE( case7, list_sv_sv_ct, edge_to_contract, self_loops_flag )
}