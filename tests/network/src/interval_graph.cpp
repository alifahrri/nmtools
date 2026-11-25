#include "nmtools/network/interval_graph.hpp"
#include "nmtools/network/greedy_color.hpp"
#include "nmtools/network/is_undirected.hpp"
#include "nmtools/testing/data/network/interval_graph.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace
{
    using nmtools::at;
    using nmtools::len;

    // invalid intervals (start > end) are reported with meta::Nothing
    template <typename result_t>
    auto to_adjacency(const result_t& result)
    {
        if constexpr (nmtools::meta::is_maybe_v<result_t>) {
            return nmtools::unwrap(result);
        } else {
            return result;
        }
    }

    // rows must be strictly ascending, loop free, in range and symmetric:
    // i in row j exactly when j is in row i, so the result is a simple
    // undirected graph with one row per interval
    template <typename adjacency_t>
    auto is_simple_undirected(const adjacency_t& adj)
    {
        bool result = true;
        auto num_nodes = len(adj);
        for (nm_size_t i=0; result && i<(nm_size_t)num_nodes; i++) {
            auto row = at(adj,i);
            for (nm_size_t k=0; result && k<(nm_size_t)len(row); k++) {
                auto j = (nm_size_t)at(row,k);
                if ((j >= (nm_size_t)num_nodes) || (j == i)) {
                    result = false;
                } else if ((k > 0) && ((nm_size_t)at(row,k-1) >= j)) {
                    // not strictly ascending: duplicate or unsorted entry
                    result = false;
                } else {
                    auto back = at(adj,j);
                    nm_size_t count = 0;
                    for (nm_size_t m=0; m<(nm_size_t)len(back); m++) {
                        count += ((nm_size_t)at(back,m) == i);
                    }
                    result = (count == 1);
                }
            }
        }
        return result;
    }
}

#define INTERVAL_GRAPH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case_name); \
    using namespace args; \
    auto result = nmtools::network::interval_graph(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( to_adjacency(result), expect::adj ); \
}

#define CONSTEXPR_INTERVAL_GRAPH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::interval_graph(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::adj ); \
}

#define INTERVAL_GRAPH_INVALID_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case_name); \
    using namespace args; \
    auto result = nmtools::network::interval_graph(__VA_ARGS__); \
    CHECK( !nmtools::has_value(result) ); \
}

#define INTERVAL_GRAPH_INVARIANT_SUBCASE(case_name, start, end) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case_name); \
    using namespace args; \
    auto result = nmtools::network::interval_graph(start, end); \
    REQUIRE( nmtools::has_value(result) ); \
    auto adj = nmtools::unwrap(result); \
    CHECK_MESSAGE( (nm_size_t)len(adj) == (nm_size_t)len(start), "node count changed" ); \
    CHECK_MESSAGE( is_simple_undirected(adj), "rows must be ascending, loop free and symmetric" ); \
    CHECK_MESSAGE( nmtools::network::is_undirected(adj), "interval graphs are undirected" ); \
}

TEST_CASE("interval_graph(case1)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case1, start, end );
    INTERVAL_GRAPH_SUBCASE( case1, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case1, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case1, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case1, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case1, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case1)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case1, start_ct, end_ct );
}

TEST_CASE("interval_graph(case2)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case2, start, end );
    INTERVAL_GRAPH_SUBCASE( case2, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case2, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case2, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case2, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case2, start_f, end_f );
    // demote only the constant side of the pair
    INTERVAL_GRAPH_SUBCASE( case2, start_ct, end_v );
    INTERVAL_GRAPH_SUBCASE( case2, start_sv, end_ct );
}

TEST_CASE("constexpr_interval_graph(case2)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case2, start_ct, end_ct );
}

TEST_CASE("interval_graph(case3)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case3, start, end );
    INTERVAL_GRAPH_SUBCASE( case3, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case3, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case3, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case3, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case3, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case3)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case3, start_ct, end_ct );
}

TEST_CASE("interval_graph(case4)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case4, start, end );
    INTERVAL_GRAPH_SUBCASE( case4, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case4, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case4, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case4, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case4, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case4)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case4, start_ct, end_ct );
}

TEST_CASE("interval_graph(case5)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case5, start, end );
    INTERVAL_GRAPH_SUBCASE( case5, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case5, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case5, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case5, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case5, start_f, end_f );
    INTERVAL_GRAPH_SUBCASE( case5, start_ct, end_v );
    INTERVAL_GRAPH_SUBCASE( case5, start_h, end_ct );
}

TEST_CASE("constexpr_interval_graph(case5)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case5, start_ct, end_ct );
}

TEST_CASE("interval_graph(case6)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case6, start, end );
    INTERVAL_GRAPH_SUBCASE( case6, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case6, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case6, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case6, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case6, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case6)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case6, start_ct, end_ct );
}

TEST_CASE("interval_graph(case7)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case7, start, end );
    INTERVAL_GRAPH_SUBCASE( case7, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case7, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case7, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case7, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case7, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case7)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case7, start_ct, end_ct );
}

TEST_CASE("interval_graph(case8)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case8, start, end );
    INTERVAL_GRAPH_SUBCASE( case8, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case8, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case8, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case8, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case8, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case8)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case8, start_ct, end_ct );
}

TEST_CASE("interval_graph(case9)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case9, start, end );
    INTERVAL_GRAPH_SUBCASE( case9, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case9, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case9, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case9, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case9, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case9)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case9, start_ct, end_ct );
}

TEST_CASE("interval_graph(case10)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case10, start, end );
    INTERVAL_GRAPH_SUBCASE( case10, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case10, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case10, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case10, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case10, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case10)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case10, start_ct, end_ct );
}

TEST_CASE("interval_graph(case11)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case11, start, end );
    INTERVAL_GRAPH_SUBCASE( case11, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case11, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case11, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case11, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case11, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case11)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case11, start_ct, end_ct );
}

TEST_CASE("interval_graph(case12)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case12, start, end );
    INTERVAL_GRAPH_SUBCASE( case12, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case12, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case12, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case12, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case12, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case12)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case12, start_ct, end_ct );
}

TEST_CASE("interval_graph(case13)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case13, start, end );
}

TEST_CASE("constexpr_interval_graph(case13)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case13, start_ct, end_ct );
}

// start > end: only the runtime path is pinned, see the note in the header
TEST_CASE("interval_graph(case14)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start, end );
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_a, end_a );
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_sv, end_sv );
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_v, end_v );
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_h, end_h );
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_f, end_f );
    // validity is checked after demoting, so a constant side is fine
    INTERVAL_GRAPH_INVALID_SUBCASE( case14, start_ct, end_v );
}

// a constant invalid interval must fold to a fail type instead of a value
TEST_CASE("interval_graph_rejects_constant_invalid_interval" * doctest::test_suite("network::interval_graph"))
{
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case14);
    using namespace args;
    static_assert(nmtools::meta::is_fail_v<decltype(nmtools::network::interval_graph(start_ct, end_ct))>
        ,"constant start > end must be rejected with a fail type");
    CHECK( true );
}

// len(start) != len(end): reported like an inverted interval, Nothing at
// runtime, whatever the container or which side is longer
TEST_CASE("interval_graph(case18)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start, end );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_a, end_a );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_sv, end_sv );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_v, end_v );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_h, end_h );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_f, end_f );
    // swapped: now start is the longer one
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, end, start );
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, end_v, start_v );
    // a demoted constant side mismatches too
    INTERVAL_GRAPH_INVALID_SUBCASE( case18, start_ct, end_v );
}

// a constant length mismatch must fold to a fail type instead of a value
TEST_CASE("interval_graph_rejects_constant_mismatched_lengths" * doctest::test_suite("network::interval_graph"))
{
    NMTOOLS_TESTING_USE_CASE(network, interval_graph, case18);
    using namespace args;
    static_assert(nmtools::meta::is_fail_v<decltype(nmtools::network::interval_graph(start_ct, end_ct))>
        ,"constant length mismatch must be rejected with a fail type");
    CHECK( true );
}

TEST_CASE("interval_graph(case15)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case15, start, end );
    INTERVAL_GRAPH_SUBCASE( case15, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case15, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case15, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case15, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case15, start_f, end_f );
    INTERVAL_GRAPH_SUBCASE( case15, start_ct, end_v );
    INTERVAL_GRAPH_SUBCASE( case15, start_f, end_ct );
}

TEST_CASE("constexpr_interval_graph(case15)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case15, start_ct, end_ct );
}

TEST_CASE("interval_graph(case16)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case16, start, end );
    INTERVAL_GRAPH_SUBCASE( case16, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case16, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case16, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case16, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case16, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case16)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case16, start_ct, end_ct );
}

TEST_CASE("interval_graph(case17)" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_SUBCASE( case17, start, end );
    INTERVAL_GRAPH_SUBCASE( case17, start_a, end_a );
    INTERVAL_GRAPH_SUBCASE( case17, start_sv, end_sv );
    INTERVAL_GRAPH_SUBCASE( case17, start_v, end_v );
    INTERVAL_GRAPH_SUBCASE( case17, start_h, end_h );
    INTERVAL_GRAPH_SUBCASE( case17, start_f, end_f );
}

TEST_CASE("constexpr_interval_graph(case17)" * doctest::test_suite("network::interval_graph"))
{
    CONSTEXPR_INTERVAL_GRAPH_SUBCASE( case17, start_ct, end_ct );
}

TEST_CASE("interval_graph_invariants" * doctest::test_suite("network::interval_graph"))
{
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case1, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case2, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case3, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case4, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case5, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case6, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case7, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case8, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case9, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case10, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case11, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case12, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case13, start, end );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case15, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case16, start_a, end_a );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case17, start_a, end_a );

    INTERVAL_GRAPH_INVARIANT_SUBCASE( case7, start_v, end_v );
    INTERVAL_GRAPH_INVARIANT_SUBCASE( case15, start_v, end_v );
}

// the interval graph is the interference graph of the slot allocator, so
// greedy_color must color it directly ; expectations from
// nx.greedy_color(nx.interval_graph(...), "DSATUR")
TEST_CASE("interval_graph_coloring_composition" * doctest::test_suite("network::interval_graph"))
{
    SUBCASE("case1")
    {
        NMTOOLS_TESTING_USE_CASE(network, interval_graph, case1);
        using namespace args;
        auto colors = nmtools::network::greedy_color(nmtools::network::interval_graph(start_a, end_a));
        REQUIRE( nmtools::has_value(colors) );
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(colors), (nmtools_array{0, 0}) );
    }
    SUBCASE("case5")
    {
        NMTOOLS_TESTING_USE_CASE(network, interval_graph, case5);
        using namespace args;
        auto colors = nmtools::network::greedy_color(nmtools::network::interval_graph(start_a, end_a));
        REQUIRE( nmtools::has_value(colors) );
        // K3 clique: three distinct slots
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(colors), (nmtools_array{0, 1, 2}) );
    }
    SUBCASE("case7")
    {
        NMTOOLS_TESTING_USE_CASE(network, interval_graph, case7);
        using namespace args;
        auto colors = nmtools::network::greedy_color(nmtools::network::interval_graph(start_a, end_a));
        REQUIRE( nmtools::has_value(colors) );
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(colors), (nmtools_array{1, 2, 1, 0}) );
    }
    SUBCASE("case15")
    {
        NMTOOLS_TESTING_USE_CASE(network, interval_graph, case15);
        using namespace args;
        auto colors = nmtools::network::greedy_color(nmtools::network::interval_graph(start_a, end_a));
        REQUIRE( nmtools::has_value(colors) );
        NMTOOLS_ASSERT_EQUAL( nmtools::unwrap(colors), (nmtools_array{0, 2, 1, 2, 0}) );
    }
}
