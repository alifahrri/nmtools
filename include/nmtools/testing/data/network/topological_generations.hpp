#ifndef NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_GENERATIONS_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_GENERATIONS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, topological_generations)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals; // For _ct suffix

    // Note: The expected result is a tuple of arrays, where each array
    // represents a generation and contains sorted node indices.
    // For cyclic graphs, an empty tuple is expected.

    // From test_01_empty_graph
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple<>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto generations = nmtools_tuple<>{};
    }

    // From test_02_single_node_graph
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto generations = nmtools_tuple<nmtools_tuple<meta::ct<0>>>{};
    }

    // From test_03_simple_linear_chain
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // 0 -> 1 -> 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}
        };
    }

    // From test_04_dag_multiple_sources
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // 0 -> 2, 1 -> 2, 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{3_ct}
        };
    }

    // From test_05_dag_multiple_sinks
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // 0 -> 1, 0 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple<>{}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct, 2_ct}
        };
    }

    // From test_06_dag_diamond_shape
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        //   0 -> {1,2}, 1 -> 3, 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{3_ct}, nmtools_tuple{3_ct}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct}, nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{3_ct}
        };
    }

    // From test_07_dag_disconnected_components
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // 0->1; 2->3; 4 (isolated)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple<>{}, nmtools_tuple{3_ct}, nmtools_tuple<>{}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 2_ct, 4_ct}, nmtools_tuple{1_ct, 3_ct}
        };
    }

    // From test_08_more_complex_dag_from_immersive_example1
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct, 3_ct},    // Node 0
            nmtools_tuple{3_ct, 4_ct},    // Node 1
            nmtools_tuple{5_ct},          // Node 2
            nmtools_tuple{5_ct, 6_ct},    // Node 3
            nmtools_tuple{6_ct, 7_ct},    // Node 4
            nmtools_tuple{8_ct},          // Node 5
            nmtools_tuple{8_ct, 9_ct},    // Node 6
            nmtools_tuple{9_ct},          // Node 7
            nmtools_tuple<>{},           // Node 8
            nmtools_tuple<>{}            // Node 9
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto generations = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct}, nmtools_tuple{2_ct, 3_ct, 4_ct}, nmtools_tuple{5_ct, 6_ct, 7_ct}, nmtools_tuple{8_ct, 9_ct}
        };
    }

    // From test_09_graph_with_simple_cycle
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // 0 -> 1 -> 2 -> 0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        // Cycle detected, no generations possible.
        constexpr inline auto generations = meta::Nothing;
    }

    // From test_10_graph_with_self_loop
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        // 0 -> 0
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<meta::ct<0>>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        // Cycle detected.
        constexpr inline auto generations = meta::Nothing;
    }

    // From test_11_graph_with_cycle_not_all_nodes_involved
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        // 0 -> 1, 1 -> 2, 2 -> 1 (cycle 1-2), 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{1_ct, 3_ct}, nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        // Cycle detected.
        constexpr inline auto generations = meta::Nothing;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_GENERATIONS_HPP