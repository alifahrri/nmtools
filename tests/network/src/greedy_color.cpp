#include "nmtools/network/greedy_color.hpp"
#include "nmtools/testing/data/network/greedy_color.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace
{
    using nmtools::at;
    using nmtools::len;

    // greedy_color reports directed input with meta::Nothing
    template <typename result_t>
    auto to_colors(const result_t& result)
    {
        if constexpr (nmtools::meta::is_maybe_v<result_t>) {
            return nmtools::unwrap(result);
        } else {
            return result;
        }
    }

    // adjacent nodes must not share a color ; self loops never constrain, as
    // networkx does not exclude a node's own color either
    template <typename adj_list_t, typename colors_t>
    auto is_valid_coloring(const adj_list_t& adj, const colors_t& colors)
    {
        bool result = (nm_size_t)len(adj) == (nm_size_t)len(colors);
        for (nm_size_t u=0; result && u<(nm_size_t)len(adj); u++) {
            auto neighbors = at(adj,u);
            for (nm_size_t j=0; result && j<(nm_size_t)len(neighbors); j++) {
                auto v = (nm_size_t)at(neighbors,j);
                if (v >= (nm_size_t)len(colors)) {
                    result = false;
                } else if (v != u) {
                    result = at(colors,u) != at(colors,v);
                }
            }
        }
        return result;
    }

    // first fit only assigns color c when 0 .. c-1 all appear among a node's
    // colored neighbors, so the set of used colors is always {0 .. max}
    template <typename colors_t>
    auto has_compact_colors(const colors_t& colors)
    {
        auto num_nodes = len(colors);
        for (nm_size_t c=0; c<(nm_size_t)num_nodes; c++) {
            bool found = false;
            for (nm_size_t i=0; !found && i<(nm_size_t)num_nodes; i++) {
                found = at(colors,i) == c;
            }
            if (!found) {
                // color c is unused, so no larger color may appear either
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    if ((nm_size_t)at(colors,i) > c) {
                        return false;
                    }
                }
                return true;
            }
        }
        return true;
    }
}

#define GREEDY_COLOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, greedy_color, case_name); \
    using namespace args; \
    auto result = nmtools::network::greedy_color(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::colors ); \
}

#define CONSTEXPR_GREEDY_COLOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, greedy_color, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::greedy_color(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::colors ); \
}

#define GREEDY_COLOR_INVARIANT_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, greedy_color, case_name); \
    using namespace args; \
    auto result = nmtools::network::greedy_color(adj_list); \
    CHECK( nmtools::has_value(result) ); \
    auto colors = to_colors(result); \
    CHECK_MESSAGE( is_valid_coloring(adj_list, colors), "adjacent nodes share a color" ); \
    CHECK_MESSAGE( has_compact_colors(colors), "used colors are not {0 .. max}" ); \
}

TEST_CASE("greedy_color(case1)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case1, list );
    GREEDY_COLOR_SUBCASE( case1, list_a_sv );
    GREEDY_COLOR_SUBCASE( case1, list_a_v );
    GREEDY_COLOR_SUBCASE( case1, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case1, list_sv_v );
    GREEDY_COLOR_SUBCASE( case1, list_v_sv );
    GREEDY_COLOR_SUBCASE( case1, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case1)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case1, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case1, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case2)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case2, list );
    GREEDY_COLOR_SUBCASE( case2, list_a_sv );
    GREEDY_COLOR_SUBCASE( case2, list_a_v );
    GREEDY_COLOR_SUBCASE( case2, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case2, list_sv_v );
    GREEDY_COLOR_SUBCASE( case2, list_v_sv );
    GREEDY_COLOR_SUBCASE( case2, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case2)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case2, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case2, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case3)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case3, list );
    GREEDY_COLOR_SUBCASE( case3, list_a_sv );
    GREEDY_COLOR_SUBCASE( case3, list_a_v );
    GREEDY_COLOR_SUBCASE( case3, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case3, list_sv_v );
    GREEDY_COLOR_SUBCASE( case3, list_v_sv );
    GREEDY_COLOR_SUBCASE( case3, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case3)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case3, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case3, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case4)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case4, list );
    GREEDY_COLOR_SUBCASE( case4, list_a_sv );
    GREEDY_COLOR_SUBCASE( case4, list_a_v );
    GREEDY_COLOR_SUBCASE( case4, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case4, list_sv_v );
    GREEDY_COLOR_SUBCASE( case4, list_v_sv );
    GREEDY_COLOR_SUBCASE( case4, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case4)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case4, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case4, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case5)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case5, list );
    GREEDY_COLOR_SUBCASE( case5, list_a_sv );
    GREEDY_COLOR_SUBCASE( case5, list_a_v );
    GREEDY_COLOR_SUBCASE( case5, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case5, list_sv_v );
    GREEDY_COLOR_SUBCASE( case5, list_v_sv );
    GREEDY_COLOR_SUBCASE( case5, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case5)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case5, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case5, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case6)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case6, list );
    GREEDY_COLOR_SUBCASE( case6, list_a_sv );
    GREEDY_COLOR_SUBCASE( case6, list_a_v );
    GREEDY_COLOR_SUBCASE( case6, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case6, list_sv_v );
    GREEDY_COLOR_SUBCASE( case6, list_v_sv );
    GREEDY_COLOR_SUBCASE( case6, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case6)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case6, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case6, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case7)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case7, list );
    GREEDY_COLOR_SUBCASE( case7, list_a_sv );
    GREEDY_COLOR_SUBCASE( case7, list_a_v );
    GREEDY_COLOR_SUBCASE( case7, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case7, list_sv_v );
    GREEDY_COLOR_SUBCASE( case7, list_v_sv );
    GREEDY_COLOR_SUBCASE( case7, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case7)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case7, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case7, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case8)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case8, list );
    GREEDY_COLOR_SUBCASE( case8, list_a_sv );
    GREEDY_COLOR_SUBCASE( case8, list_a_v );
    GREEDY_COLOR_SUBCASE( case8, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case8, list_sv_v );
    GREEDY_COLOR_SUBCASE( case8, list_v_sv );
    GREEDY_COLOR_SUBCASE( case8, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case8)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case8, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case8, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case8, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case9)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case9, list );
    GREEDY_COLOR_SUBCASE( case9, list_a_sv );
    GREEDY_COLOR_SUBCASE( case9, list_a_v );
    GREEDY_COLOR_SUBCASE( case9, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case9, list_sv_v );
    GREEDY_COLOR_SUBCASE( case9, list_v_sv );
    GREEDY_COLOR_SUBCASE( case9, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case9)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case9, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case9, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case10)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case10, list );
    GREEDY_COLOR_SUBCASE( case10, list_a_sv );
    GREEDY_COLOR_SUBCASE( case10, list_a_v );
    GREEDY_COLOR_SUBCASE( case10, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case10, list_sv_v );
    GREEDY_COLOR_SUBCASE( case10, list_v_sv );
    GREEDY_COLOR_SUBCASE( case10, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case10)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case10, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case10, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case11)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case11, list );
    GREEDY_COLOR_SUBCASE( case11, list_a_sv );
    GREEDY_COLOR_SUBCASE( case11, list_a_v );
    GREEDY_COLOR_SUBCASE( case11, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case11, list_sv_v );
    GREEDY_COLOR_SUBCASE( case11, list_v_sv );
    GREEDY_COLOR_SUBCASE( case11, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case11)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case11, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case11, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case11, list_sv_sv_ct );
}

TEST_CASE("greedy_color(case13)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case13, list );
    GREEDY_COLOR_SUBCASE( case13, list_a_sv );
    GREEDY_COLOR_SUBCASE( case13, list_a_v );
    GREEDY_COLOR_SUBCASE( case13, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case13, list_sv_v );
    GREEDY_COLOR_SUBCASE( case13, list_v_sv );
    GREEDY_COLOR_SUBCASE( case13, list_v_v );
}

TEST_CASE("constexpr_greedy_color(case13)" * doctest::test_suite("network::greedy_color"))
{
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case13, list );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case13, list_a_sv_ct );
    CONSTEXPR_GREEDY_COLOR_SUBCASE( case13, list_sv_sv_ct );
}

// directed input ; only the runtime path is pinned, see the note in the header
TEST_CASE("greedy_color(case12)" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_SUBCASE( case12, list_a_sv );
    GREEDY_COLOR_SUBCASE( case12, list_a_v );
    GREEDY_COLOR_SUBCASE( case12, list_sv_sv );
    GREEDY_COLOR_SUBCASE( case12, list_sv_v );
    GREEDY_COLOR_SUBCASE( case12, list_v_sv );
    GREEDY_COLOR_SUBCASE( case12, list_v_v );
}

// a constant directed graph must fold to a fail type instead of a value
TEST_CASE("greedy_color_rejects_constant_directed_graph" * doctest::test_suite("network::greedy_color"))
{
    NMTOOLS_TESTING_USE_CASE(network, greedy_color, case12);
    using namespace args;
    static_assert(nmtools::meta::is_fail_v<decltype(nmtools::network::greedy_color(list))>
        ,"directed input must be rejected with a fail type");
    CHECK( true );
}

TEST_CASE("greedy_color_invariants" * doctest::test_suite("network::greedy_color"))
{
    GREEDY_COLOR_INVARIANT_SUBCASE( case1, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case2, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case3, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case4, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case5, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case6, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case7, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case8, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case9, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case10, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case11, list_a_sv );
    GREEDY_COLOR_INVARIANT_SUBCASE( case13, list_a_sv );

    GREEDY_COLOR_INVARIANT_SUBCASE( case4, list_v_v );
    GREEDY_COLOR_INVARIANT_SUBCASE( case9, list_v_v );
}
