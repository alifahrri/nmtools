#include "nmtools/network/degree.hpp"
#include "nmtools/network/to_undirected.hpp"
#include "nmtools/testing/data/network/degree.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define DEGREE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, degree, case_name); \
    using namespace args; \
    auto result = nmtools::network::degree(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

#define CONSTEXPR_DEGREE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, degree, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::degree(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

// degree counts neighbours of the underlying undirected graph, so symmetrizing
// must not change it
#define DEGREE_UNDER_TO_UNDIRECTED_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, degree, case_name); \
    using namespace args; \
    auto result = nmtools::network::degree(nmtools::network::to_undirected(adj_list)); \
    NMTOOLS_ASSERT_EQUAL( result, expect::degrees ); \
}

TEST_CASE("degree(case1)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case1, list );
    DEGREE_SUBCASE( case1, list_a_sv );
    DEGREE_SUBCASE( case1, list_a_v );
    DEGREE_SUBCASE( case1, list_sv_sv );
    DEGREE_SUBCASE( case1, list_sv_v );
    DEGREE_SUBCASE( case1, list_v_sv );
    DEGREE_SUBCASE( case1, list_v_v );
}

TEST_CASE("constexpr_degree(case1)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case1, list );
    CONSTEXPR_DEGREE_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("degree(case2)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case2, list );
    DEGREE_SUBCASE( case2, list_a_sv );
    DEGREE_SUBCASE( case2, list_a_v );
    DEGREE_SUBCASE( case2, list_sv_sv );
    DEGREE_SUBCASE( case2, list_sv_v );
    DEGREE_SUBCASE( case2, list_v_sv );
    DEGREE_SUBCASE( case2, list_v_v );
}

TEST_CASE("constexpr_degree(case2)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case2, list );
    CONSTEXPR_DEGREE_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("degree(case3)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case3, list );
    DEGREE_SUBCASE( case3, list_a_sv );
    DEGREE_SUBCASE( case3, list_a_v );
    DEGREE_SUBCASE( case3, list_sv_sv );
    DEGREE_SUBCASE( case3, list_sv_v );
    DEGREE_SUBCASE( case3, list_v_sv );
    DEGREE_SUBCASE( case3, list_v_v );
}

TEST_CASE("constexpr_degree(case3)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case3, list );
    CONSTEXPR_DEGREE_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("degree(case4)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case4, list );
    DEGREE_SUBCASE( case4, list_a_sv );
    DEGREE_SUBCASE( case4, list_a_v );
    DEGREE_SUBCASE( case4, list_sv_sv );
    DEGREE_SUBCASE( case4, list_sv_v );
    DEGREE_SUBCASE( case4, list_v_sv );
    DEGREE_SUBCASE( case4, list_v_v );
}

TEST_CASE("constexpr_degree(case4)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case4, list );
    CONSTEXPR_DEGREE_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("degree(case5)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case5, list );
    DEGREE_SUBCASE( case5, list_a_sv );
    DEGREE_SUBCASE( case5, list_a_v );
    DEGREE_SUBCASE( case5, list_sv_sv );
    DEGREE_SUBCASE( case5, list_sv_v );
    DEGREE_SUBCASE( case5, list_v_sv );
    DEGREE_SUBCASE( case5, list_v_v );
}

TEST_CASE("constexpr_degree(case5)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case5, list );
    CONSTEXPR_DEGREE_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("degree(case6)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case6, list );
    DEGREE_SUBCASE( case6, list_a_sv );
    DEGREE_SUBCASE( case6, list_a_v );
    DEGREE_SUBCASE( case6, list_sv_sv );
    DEGREE_SUBCASE( case6, list_sv_v );
    DEGREE_SUBCASE( case6, list_v_sv );
    DEGREE_SUBCASE( case6, list_v_v );
}

TEST_CASE("constexpr_degree(case6)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case6, list );
    CONSTEXPR_DEGREE_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("degree(case7)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case7, list );
    DEGREE_SUBCASE( case7, list_a_sv );
    DEGREE_SUBCASE( case7, list_a_v );
    DEGREE_SUBCASE( case7, list_sv_sv );
    DEGREE_SUBCASE( case7, list_sv_v );
    DEGREE_SUBCASE( case7, list_v_sv );
    DEGREE_SUBCASE( case7, list_v_v );
}

TEST_CASE("constexpr_degree(case7)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case7, list );
    CONSTEXPR_DEGREE_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("degree(case8)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case8, list );
    DEGREE_SUBCASE( case8, list_a_sv );
    DEGREE_SUBCASE( case8, list_a_v );
    DEGREE_SUBCASE( case8, list_sv_sv );
    DEGREE_SUBCASE( case8, list_sv_v );
    DEGREE_SUBCASE( case8, list_v_sv );
    DEGREE_SUBCASE( case8, list_v_v );
}

TEST_CASE("constexpr_degree(case8)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case8, list );
    CONSTEXPR_DEGREE_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case8, list_sv_sv_ct );
}

TEST_CASE("degree(case9)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case9, list );
    DEGREE_SUBCASE( case9, list_a_sv );
    DEGREE_SUBCASE( case9, list_a_v );
    DEGREE_SUBCASE( case9, list_sv_sv );
    DEGREE_SUBCASE( case9, list_sv_v );
    DEGREE_SUBCASE( case9, list_v_sv );
    DEGREE_SUBCASE( case9, list_v_v );
}

TEST_CASE("constexpr_degree(case9)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case9, list );
    CONSTEXPR_DEGREE_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case9, list_sv_sv_ct );
}

TEST_CASE("degree(case10)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case10, list );
    DEGREE_SUBCASE( case10, list_a_sv );
    DEGREE_SUBCASE( case10, list_a_v );
    DEGREE_SUBCASE( case10, list_sv_sv );
    DEGREE_SUBCASE( case10, list_sv_v );
    DEGREE_SUBCASE( case10, list_v_sv );
    DEGREE_SUBCASE( case10, list_v_v );
}

TEST_CASE("constexpr_degree(case10)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case10, list );
    CONSTEXPR_DEGREE_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case10, list_sv_sv_ct );
}

// out of range node: only the runtime path is pinned, see the note in the header
TEST_CASE("degree(case11)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case11, list_a_sv );
    DEGREE_SUBCASE( case11, list_a_v );
    DEGREE_SUBCASE( case11, list_sv_sv );
    DEGREE_SUBCASE( case11, list_sv_v );
    DEGREE_SUBCASE( case11, list_v_sv );
    DEGREE_SUBCASE( case11, list_v_v );
}

TEST_CASE("degree(case12)" * doctest::test_suite("network::degree"))
{
    DEGREE_SUBCASE( case12, list );
    DEGREE_SUBCASE( case12, list_a_sv );
    DEGREE_SUBCASE( case12, list_a_v );
    DEGREE_SUBCASE( case12, list_sv_sv );
    DEGREE_SUBCASE( case12, list_sv_v );
    DEGREE_SUBCASE( case12, list_v_sv );
    DEGREE_SUBCASE( case12, list_v_v );
}

TEST_CASE("constexpr_degree(case12)" * doctest::test_suite("network::degree"))
{
    CONSTEXPR_DEGREE_SUBCASE( case12, list );
    CONSTEXPR_DEGREE_SUBCASE( case12, list_a_sv_ct );
    CONSTEXPR_DEGREE_SUBCASE( case12, list_sv_sv_ct );
}

TEST_CASE("degree_under_to_undirected" * doctest::test_suite("network::degree"))
{
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case1, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case2, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case3, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case4, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case5, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case6, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case7, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case8, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case9, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case10, list_a_sv );
    DEGREE_UNDER_TO_UNDIRECTED_SUBCASE( case12, list_a_sv );
}
