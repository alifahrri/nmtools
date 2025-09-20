#ifndef NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, predecessors)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    // Note: The expected output type for 'preds' (e.g., array, list)
    // should match what your 'predecessors' function is designed to return.
    // We'll use nmtools_array for the expected values here, assuming it will be
    // compared against an array-like result.

    //----------------------------------------------------
    // Test Case 1: Node with Multiple Predecessors
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 2, 1 -> 2, 3 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{},              // Node 2 neighbors
            nmtools_tuple{2_ct}           // Node 3 neighbors
        };
        constexpr inline auto node_idx = 2; // Find predecessors of node 2
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Predecessors of node 2 are 0, 1, 3. Expected in sorted order.
        constexpr inline auto preds = nmtools_array{0, 1, 3};
    }

    //----------------------------------------------------
    // Test Case 2: Node with a Single Predecessor
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{}               // Node 2 neighbors
        };
        constexpr inline auto node_idx = 1; // Find predecessors of node 1
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 1_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Predecessor of node 1 is 0.
        constexpr inline auto preds = nmtools_array{0};
    }

    //----------------------------------------------------
    // Test Case 3: Node with No Predecessors (a source node)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1, 0 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},       // Node 0 neighbors
            nmtools_tuple{},    // Node 1 neighbors
            nmtools_tuple{}     // Node 2 neighbors
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Node 0 has no predecessors.
        constexpr inline nmtools_array<int,0> preds {}; // Empty array
    }

    //----------------------------------------------------
    // Test Case 4: Node in a Graph with Cycles
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0 -> 1, 1 -> 2, 2 -> 0 (cycle), 1 -> 0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct, 0_ct},       // Node 1 neighbors
            nmtools_tuple{0_ct}           // Node 2 neighbors
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Predecessors of node 0 are 1, 2. Expected in sorted order.
        constexpr inline auto preds = nmtools_array{1, 2};
    }

    //----------------------------------------------------
    // Test Case 5: More Complex Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph:
        // 0 -> 1, 0 -> 2
        // 1 -> 3
        // 2 -> 3, 2 -> 4
        // 3 -> 0, 3 -> 4
        // 4 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},       // Node 0 neighbors
            nmtools_tuple{3_ct},          // Node 1 neighbors
            nmtools_tuple{3_ct, 4_ct},       // Node 2 neighbors
            nmtools_tuple{0_ct, 4_ct},       // Node 3 neighbors
            nmtools_tuple{}     // Node 4 neighbors
        };
        constexpr inline auto node_idx = 4; // Find predecessors of node 4
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 4_ct; // Find predecessors of node 4
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Predecessors of node 4 are 2, 3. Expected in sorted order.
        constexpr inline auto preds = nmtools_array{2, 3};
    }

    //----------------------------------------------------
    // Test Case 6: Node not in graph (or out of bounds index)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          // Node 0 neighbors
            nmtools_tuple{}              // Node 1 neighbors
        };
        constexpr inline auto node_idx = 5; // Node 5 is not in this graph
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto node_idx_ct = 5_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expect an empty list if the node is not part of the graph.
        // The exact behavior (e.g. error, empty list) might depend on
        // the function's design for out-of-bounds/non-existent nodes.
        // Assuming empty list for this test.
        constexpr inline auto preds = meta::Nothing;
    }

    //----------------------------------------------------
    // Test Case 7: Empty Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{}; // Empty adjacency list
        constexpr inline auto node_idx = 0; // Node 0
        constexpr inline auto src_node_ids = nmtools_array{100};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Expect an empty list if the graph is empty.
        constexpr inline nmtools_array<int,0> preds {}; // Empty array
    }

    //----------------------------------------------------
    // Test Case 8: All Predecessors for Each Node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Graph:
        // 0 -> 1
        // 1 -> 2
        // 0 -> 2
        // 3 -> 0 (introduces another predecessor for node 0)
        // 3 -> 1 (introduces another predecessor for node 1)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},       // Node 0 neighbors (target for node 3)
            nmtools_tuple{2_ct},             // Node 1 neighbors (target for node 0, 3)
            nmtools_tuple{},                 // Node 2 neighbors (target for node 0, 1)
            nmtools_tuple{0_ct, 1_ct}        // Node 3 neighbors
        };
        // No node_idx, implies operation for all nodes.

        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};
        constexpr inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        // Expected predecessors for each node (0, 1, 2, 3), each sorted.
        // Node 0 predecessors: {3}
        // Node 1 predecessors: {0, 3}
        // Node 2 predecessors: {0, 1}
        // Node 3 predecessors: {}
        constexpr inline auto preds = nmtools_tuple{
            array{3},              // Predecessors of Node 0
            array{0, 3},           // Predecessors of Node 1
            array{0, 1},           // Predecessors of Node 2
            array<int,0>{}         // Predecessors of Node 3
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_PREDECESSORS_HPP
