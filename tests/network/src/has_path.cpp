#include "nmtools/network/has_path.hpp"
#include "nmtools/testing/data/network/has_path.hpp"
#include "nmtools/testing/doctest.hpp"

#define HAS_PATH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, has_path, case_name); \
    using namespace args; \
    auto result = nmtools::network::has_path(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::exists ); \
}

#define CONSTEXPR_HAS_PATH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, has_path, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::has_path(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::exists ); \
}

TEST_CASE("has_path(case1)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case1, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case1, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case1, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case1, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case1, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case1, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case1)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case1, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case1, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case2)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case2, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case2, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case2, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case2, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case2, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case2, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case2)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case2, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case2, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case3)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case3, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case3, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case3, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case3, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case3, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case3, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case3)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case3, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case3, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case4)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case4, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case4, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case4, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case4, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case4, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case4, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case4)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case4, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case4, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case5)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case5, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case5, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case5, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case5, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case5, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case5, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case5)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case5, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case5, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case6)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case6, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case6, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case6, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case6, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case6, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case6, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case6)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case6, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case6, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case7)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case7, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case7, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case7, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case7, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case7, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case7, list_v_v, source_node, target_node );
}

TEST_CASE("constexpr_has_path(case7)" * doctest::test_suite("network::has_path"))
{
    CONSTEXPR_HAS_PATH_SUBCASE( case7, list_a_sv_ct, source_node, target_node );
    CONSTEXPR_HAS_PATH_SUBCASE( case7, list_sv_sv_ct, source_node, target_node );
}

TEST_CASE("has_path(case8)" * doctest::test_suite("network::has_path"))
{
    HAS_PATH_SUBCASE( case8, list_a_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case8, list_a_v, source_node, target_node );
    HAS_PATH_SUBCASE( case8, list_sv_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case8, list_sv_v, source_node, target_node );
    HAS_PATH_SUBCASE( case8, list_v_sv, source_node, target_node );
    HAS_PATH_SUBCASE( case8, list_v_v, source_node, target_node );
}

// TEST_CASE("constexpr_has_path(case8)" * doctest::test_suite("network::has_path"))
// {
//     CONSTEXPR_HAS_PATH_SUBCASE( case8, list_a_sv_ct, source_node, target_node );
//     CONSTEXPR_HAS_PATH_SUBCASE( case8, list_sv_sv_ct, source_node, target_node );
// }