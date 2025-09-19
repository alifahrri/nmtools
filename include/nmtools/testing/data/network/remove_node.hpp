#ifndef NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, remove_node)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    //----------------------------------------------------
    // Test Case 1: Remove a middle node from a line graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Initial Graph: 0 -> 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // Remove node 1
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Expected Graph: Node 0, New Node 1 (was 2).
        // Edge 0->1 is removed. Edge 1->2 is removed. No edges left.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 2: Remove a source node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Initial Graph: 0->1, 0->2, 1->3, 2->3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        // Remove node 0
        constexpr inline int node_to_remove = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Expected Graph: New 0 (was 1), New 1 (was 2), New 2 (was 3)
        // Edge (1,3) becomes (0,2). Edge (2,3) becomes (1,2).
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{2}, // New node 0 (was 1)
            nmtools_array{2}, // New node 1 (was 2)
            nmtools_array<int,0>{}  // New node 2 (was 3)
        };
    }

    //----------------------------------------------------
    // Test Case 3: Remove a sink node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Initial Graph: 0->2, 1->2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // Remove node 2
        constexpr inline int node_to_remove = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Expected Graph: Nodes 0, 1.
        // Edges (0,2) and (1,2) are removed.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 4: Remove a node from a cycle
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Initial Graph: 0->1, 1->2, 2->0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        // Remove node 1
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Expected Graph: New 0 (was 0), New 1 (was 2).
        // Edge (2,0) becomes (1,0).
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    //----------------------------------------------------
    // Test Case 5: Remove the only node in a graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Initial Graph: 0
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        // Remove node 0
        constexpr inline int node_to_remove = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Expected Graph: Empty
        constexpr inline auto result = nmtools_tuple{};
    }

    //----------------------------------------------------
    // Test Case 6: Remove node from a MultiDiGraph structure
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Initial Graph: 0->1, 0->1, 1->2, 1->2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{2_ct, 2_ct},
            nmtools_tuple{}
        };
        // Remove node 1
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expected Graph: New 0 (was 0), New 1 (was 2).
        // All edges incident to original node 1 are removed.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 7: Remove a disconnected node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Initial Graph: 0->1, node 2 is isolated
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        // Remove node 2
        constexpr inline int node_to_remove = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Expected Graph: 0->1
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }
} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP
