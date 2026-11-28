#include "nmtools/network/to_undirected.hpp"
#include "nmtools/testing/data/network/to_undirected.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace
{
    // u is in adj[v] iff v is in adj[u]
    template <typename adjacency_list_t>
    bool is_symmetric(const adjacency_list_t& adj)
    {
        auto num_nodes = nmtools::len(adj);
        for (nm_size_t u=0; u<(nm_size_t)num_nodes; u++) {
            const auto& neighbors = nmtools::at(adj,u);
            for (nm_size_t j=0; j<(nm_size_t)nmtools::len(neighbors); j++) {
                auto v = (nm_size_t)nmtools::at(neighbors,j);
                if (v >= (nm_size_t)num_nodes) {
                    return false;
                }
                auto found = false;
                const auto& back = nmtools::at(adj,v);
                for (nm_size_t k=0; k<(nm_size_t)nmtools::len(back); k++) {
                    found |= ((nm_size_t)nmtools::at(back,k) == u);
                }
                if (!found) {
                    return false;
                }
            }
        }
        return true;
    }

    // every row strictly ascending: no duplicates, deterministic order
    template <typename adjacency_list_t>
    bool has_strictly_ascending_rows(const adjacency_list_t& adj)
    {
        auto num_nodes = nmtools::len(adj);
        for (nm_size_t u=0; u<(nm_size_t)num_nodes; u++) {
            const auto& neighbors = nmtools::at(adj,u);
            auto num_neighbors = (nm_size_t)nmtools::len(neighbors);
            for (nm_size_t j=1; j<num_neighbors; j++) {
                if (!((nm_size_t)nmtools::at(neighbors,j-1) < (nm_size_t)nmtools::at(neighbors,j))) {
                    return false;
                }
            }
        }
        return true;
    }
}

using nmtools::has_value, nmtools::unwrap;

#define TO_UNDIRECTED_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, to_undirected, case_name); \
    using namespace args; \
    auto result = nmtools::network::to_undirected(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::undirected ); \
}

#define CONSTEXPR_TO_UNDIRECTED_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, to_undirected, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::network::to_undirected(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::undirected ); \
}

// NOTE: the invariants are checked on runtime containers only, constant ones
// cannot be indexed with a runtime index
#define TO_UNDIRECTED_INVARIANTS_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, to_undirected, case_name); \
    using namespace args; \
    auto result = nmtools::network::to_undirected(adj_list); \
    REQUIRE_MESSAGE( has_value(result), "expected an adjacency list instead of Nothing" ); \
    auto undirected = unwrap(result); \
    CHECK_MESSAGE( is_symmetric(undirected), "adjacency list is not symmetric" ); \
    CHECK_MESSAGE( has_strictly_ascending_rows(undirected), "rows are not strictly ascending" ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::len(undirected), nmtools::len(adj_list) ); \
}

// symmetrizing twice must be a fixed point
#define TO_UNDIRECTED_IDEMPOTENT_SUBCASE(case_name, adj_list) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(network, to_undirected, case_name); \
    using namespace args; \
    auto once = nmtools::network::to_undirected(adj_list); \
    auto twice = nmtools::network::to_undirected(once); \
    NMTOOLS_ASSERT_EQUAL( twice, expect::undirected ); \
}

TEST_CASE("to_undirected(case1)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case1, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case1, list_a_v );
    TO_UNDIRECTED_SUBCASE( case1, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case1, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case1, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case1, list_v_v );

    TO_UNDIRECTED_SUBCASE( case1, list );
}

TEST_CASE("constexpr_to_undirected(case1)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case1, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case1, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case1, list );
}

TEST_CASE("to_undirected(case2)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case2, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case2, list_a_v );
    TO_UNDIRECTED_SUBCASE( case2, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case2, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case2, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case2, list_v_v );

    TO_UNDIRECTED_SUBCASE( case2, list );
}

TEST_CASE("constexpr_to_undirected(case2)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case2, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case2, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case2, list );
}

TEST_CASE("to_undirected(case3)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case3, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case3, list_a_v );
    TO_UNDIRECTED_SUBCASE( case3, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case3, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case3, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case3, list_v_v );

    TO_UNDIRECTED_SUBCASE( case3, list );
}

TEST_CASE("constexpr_to_undirected(case3)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case3, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case3, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case3, list );
}

TEST_CASE("to_undirected(case4)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case4, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case4, list_a_v );
    TO_UNDIRECTED_SUBCASE( case4, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case4, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case4, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case4, list_v_v );

    TO_UNDIRECTED_SUBCASE( case4, list );
}

TEST_CASE("constexpr_to_undirected(case4)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case4, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case4, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case4, list );
}

TEST_CASE("to_undirected(case5)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case5, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case5, list_a_v );
    TO_UNDIRECTED_SUBCASE( case5, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case5, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case5, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case5, list_v_v );

    TO_UNDIRECTED_SUBCASE( case5, list );
}

TEST_CASE("constexpr_to_undirected(case5)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case5, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case5, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case5, list );
}

TEST_CASE("to_undirected(case6)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case6, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case6, list_a_v );
    TO_UNDIRECTED_SUBCASE( case6, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case6, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case6, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case6, list_v_v );

    TO_UNDIRECTED_SUBCASE( case6, list );
}

TEST_CASE("constexpr_to_undirected(case6)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case6, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case6, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case6, list );
}

TEST_CASE("to_undirected(case7)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case7, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case7, list_a_v );
    TO_UNDIRECTED_SUBCASE( case7, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case7, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case7, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case7, list_v_v );

    TO_UNDIRECTED_SUBCASE( case7, list );
}

TEST_CASE("constexpr_to_undirected(case7)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case7, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case7, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case7, list );
}

// out of range node: only the runtime path is pinned, see the note in the data header
TEST_CASE("to_undirected(case8)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case8, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case8, list_a_v );
    TO_UNDIRECTED_SUBCASE( case8, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case8, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case8, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case8, list_v_v );
}

TEST_CASE("to_undirected(case9)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case9, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case9, list_a_v );
    TO_UNDIRECTED_SUBCASE( case9, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case9, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case9, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case9, list_v_v );

    TO_UNDIRECTED_SUBCASE( case9, list );
}

TEST_CASE("constexpr_to_undirected(case9)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case9, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case9, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case9, list );
}

TEST_CASE("to_undirected(case10)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case10, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case10, list_a_v );
    TO_UNDIRECTED_SUBCASE( case10, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case10, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case10, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case10, list_v_v );

    TO_UNDIRECTED_SUBCASE( case10, list );
}

TEST_CASE("constexpr_to_undirected(case10)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case10, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case10, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case10, list );
}

TEST_CASE("to_undirected(case11)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case11, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case11, list_a_v );
    TO_UNDIRECTED_SUBCASE( case11, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case11, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case11, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case11, list_v_v );

    TO_UNDIRECTED_SUBCASE( case11, list );
}

TEST_CASE("constexpr_to_undirected(case11)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case11, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case11, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case11, list );
}

TEST_CASE("to_undirected(case12)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case12, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case12, list_a_v );
    TO_UNDIRECTED_SUBCASE( case12, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case12, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case12, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case12, list_v_v );

    TO_UNDIRECTED_SUBCASE( case12, list );
}

TEST_CASE("constexpr_to_undirected(case12)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case12, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case12, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case12, list );
}

TEST_CASE("to_undirected(case13)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case13, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case13, list_a_v );
    TO_UNDIRECTED_SUBCASE( case13, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case13, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case13, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case13, list_v_v );

    TO_UNDIRECTED_SUBCASE( case13, list );
}

TEST_CASE("constexpr_to_undirected(case13)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case13, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case13, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case13, list );
}

TEST_CASE("to_undirected(case14)" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_SUBCASE( case14, list_a_sv );
    TO_UNDIRECTED_SUBCASE( case14, list_a_v );
    TO_UNDIRECTED_SUBCASE( case14, list_sv_sv );
    TO_UNDIRECTED_SUBCASE( case14, list_sv_v );
    TO_UNDIRECTED_SUBCASE( case14, list_v_sv );
    TO_UNDIRECTED_SUBCASE( case14, list_v_v );

    TO_UNDIRECTED_SUBCASE( case14, list );
}

TEST_CASE("constexpr_to_undirected(case14)" * doctest::test_suite("network::to_undirected"))
{
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case14, list_a_sv_ct );
    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case14, list_sv_sv_ct );

    CONSTEXPR_TO_UNDIRECTED_SUBCASE( case14, list );
}

TEST_CASE("to_undirected_invariants" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case1, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case2, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case3, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case4, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case5, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case6, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case7, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case9, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case10, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case11, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case12, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case13, list_a_sv );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case14, list_a_sv );

    TO_UNDIRECTED_INVARIANTS_SUBCASE( case1, list_v_v );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case6, list_v_v );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case13, list_v_v );
    TO_UNDIRECTED_INVARIANTS_SUBCASE( case14, list_v_v );
}

TEST_CASE("to_undirected_idempotent" * doctest::test_suite("network::to_undirected"))
{
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case1, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case2, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case3, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case4, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case5, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case6, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case7, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case9, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case10, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case11, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case12, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case13, list_a_sv );
    TO_UNDIRECTED_IDEMPOTENT_SUBCASE( case14, list_a_sv );
}
