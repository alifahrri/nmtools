#include "nmtools/network/predecessors.hpp"
#include "nmtools/testing/data/network/predecessors.hpp"
#include "nmtools/testing/doctest.hpp"

#define PREDECESSORS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, predecessors, case_name); \
    using namespace args; \
    auto result = nmtools::network::predecessors(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL(result, expect::preds ); \
}

TEST_CASE("predecessors(case1)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case1, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case1, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case1, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case1, list_v_v, node_idx );
}

TEST_CASE("predecessors(case2)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case2, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case2, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case2, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case2, list_v_v, node_idx );
}

TEST_CASE("predecessors(case3)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case3, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case3, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case3, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case3, list_v_v, node_idx );
}

TEST_CASE("predecessors(case4)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case4, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case4, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case4, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case4, list_v_v, node_idx );
}

TEST_CASE("predecessors(case5)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case5, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case5, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case5, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case5, list_v_v, node_idx );
}

TEST_CASE("predecessors(case6)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case6, list_a_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_a_v, node_idx );
    PREDECESSORS_SUBCASE( case6, list_sv_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_sv_v, node_idx );
    PREDECESSORS_SUBCASE( case6, list_v_sv, node_idx );
    PREDECESSORS_SUBCASE( case6, list_v_v, node_idx );
}

// TEST_CASE("predecessors(case7)" * doctest::test_suite("network::predecessors"))
// {
//     PREDECESSORS_SUBCASE( case7, list_a_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_a_v, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_sv_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_sv_v, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_v_sv, node_idx );
//     PREDECESSORS_SUBCASE( case7, list_v_v, node_idx );
// }

TEST_CASE("predecessors(case8)" * doctest::test_suite("network::predecessors"))
{
    PREDECESSORS_SUBCASE( case8, list_a_sv );
    PREDECESSORS_SUBCASE( case8, list_a_v );
    PREDECESSORS_SUBCASE( case8, list_sv_sv );
    PREDECESSORS_SUBCASE( case8, list_sv_v );
    PREDECESSORS_SUBCASE( case8, list_v_sv );
    PREDECESSORS_SUBCASE( case8, list_v_v );
}