#include "nmtools/network/is_undirected.hpp"
#include "nmtools/network/to_undirected.hpp"
#include "nmtools/testing/data/network/is_undirected.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace
{
    // to_undirected reports invalid graphs with meta::Nothing
    template <typename result_t>
    auto to_adjacency_list(const result_t& result)
    {
        if constexpr (nmtools::meta::is_maybe_v<result_t>) {
            return nmtools::unwrap(result);
        } else {
            return result;
        }
    }
}

#define IS_UNDIRECTED_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_undirected, case_name); \
    using namespace args; \
    auto result = nmtools::network::is_undirected(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONSTEXPR_IS_UNDIRECTED_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_undirected, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::is_undirected(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

// symmetrizing any valid graph must produce an undirected one
#define IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, is_undirected, case_name); \
    using namespace args; \
    auto undirected = to_adjacency_list(nmtools::network::to_undirected(adj_list)); \
    auto result = nmtools::network::is_undirected(undirected); \
    NMTOOLS_ASSERT_EQUAL( result, true ); \
}

TEST_CASE("is_undirected(case1)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case1, list );
    IS_UNDIRECTED_SUBCASE( case1, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case1, list_a_v );
    IS_UNDIRECTED_SUBCASE( case1, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case1, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case1, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case1, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case1)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case1, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case2)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case2, list );
    IS_UNDIRECTED_SUBCASE( case2, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case2, list_a_v );
    IS_UNDIRECTED_SUBCASE( case2, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case2, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case2, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case2, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case2)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case2, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case3)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case3, list );
    IS_UNDIRECTED_SUBCASE( case3, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case3, list_a_v );
    IS_UNDIRECTED_SUBCASE( case3, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case3, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case3, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case3, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case3)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case3, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case4)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case4, list );
    IS_UNDIRECTED_SUBCASE( case4, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case4, list_a_v );
    IS_UNDIRECTED_SUBCASE( case4, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case4, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case4, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case4, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case4)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case4, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case5)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case5, list );
    IS_UNDIRECTED_SUBCASE( case5, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case5, list_a_v );
    IS_UNDIRECTED_SUBCASE( case5, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case5, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case5, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case5, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case5)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case5, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case6)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case6, list );
    IS_UNDIRECTED_SUBCASE( case6, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case6, list_a_v );
    IS_UNDIRECTED_SUBCASE( case6, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case6, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case6, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case6, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case6)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case6, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case7)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case7, list );
    IS_UNDIRECTED_SUBCASE( case7, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case7, list_a_v );
    IS_UNDIRECTED_SUBCASE( case7, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case7, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case7, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case7, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case7)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case7, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case8)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case8, list );
    IS_UNDIRECTED_SUBCASE( case8, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case8, list_a_v );
    IS_UNDIRECTED_SUBCASE( case8, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case8, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case8, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case8, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case8)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case8, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case8, list_sv_sv_ct );
}

// dangling target ; reported as false on every path
TEST_CASE("is_undirected(case9)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case9, list );
    IS_UNDIRECTED_SUBCASE( case9, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case9, list_a_v );
    IS_UNDIRECTED_SUBCASE( case9, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case9, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case9, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case9, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case9)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case9, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case9, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case10)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case10, list );
    IS_UNDIRECTED_SUBCASE( case10, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case10, list_a_v );
    IS_UNDIRECTED_SUBCASE( case10, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case10, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case10, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case10, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case10)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case10, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case10, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case11)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case11, list );
    IS_UNDIRECTED_SUBCASE( case11, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case11, list_a_v );
    IS_UNDIRECTED_SUBCASE( case11, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case11, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case11, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case11, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case11)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case11, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case11, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case11, list_sv_sv_ct );
}

TEST_CASE("is_undirected(case12)" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_SUBCASE( case12, list );
    IS_UNDIRECTED_SUBCASE( case12, list_a_sv );
    IS_UNDIRECTED_SUBCASE( case12, list_a_v );
    IS_UNDIRECTED_SUBCASE( case12, list_sv_sv );
    IS_UNDIRECTED_SUBCASE( case12, list_sv_v );
    IS_UNDIRECTED_SUBCASE( case12, list_v_sv );
    IS_UNDIRECTED_SUBCASE( case12, list_v_v );
}

TEST_CASE("constexpr_is_undirected(case12)" * doctest::test_suite("network::is_undirected"))
{
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case12, list );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case12, list_a_sv_ct );
    CONSTEXPR_IS_UNDIRECTED_SUBCASE( case12, list_sv_sv_ct );
}

TEST_CASE("is_undirected_after_to_undirected" * doctest::test_suite("network::is_undirected"))
{
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case1, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case2, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case3, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case4, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case5, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case6, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case7, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case8, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case10, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case11, list_a_sv );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case12, list_a_sv );

    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case2, list_v_v );
    IS_UNDIRECTED_AFTER_TO_UNDIRECTED_SUBCASE( case4, list_v_v );
}
