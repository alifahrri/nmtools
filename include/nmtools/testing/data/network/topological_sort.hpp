#ifndef NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_SORT_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_SORT_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, topological_sort)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using nmtools_either; // Assuming either might be used for success/failure
    using nmtools_list;   // Or list for the result

    // Note: The exact expected type for 'sorted_nodes' (e.g., array, list, or
    // an optional/either type to handle cycles) depends on the function's signature.
    // Here, we'll assume it returns an 'array'. An empty array will signify
    // that no topological sort exists (e.g., due to a cycle).

    //----------------------------------------------------
    // Test Case 1: Simple Linear DAG
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array<int,0>(),    // Node 2 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Expected sort: [0, 1, 2]
        constexpr inline auto sorted_nodes = array{0, 1, 2};
    }

    //----------------------------------------------------
    // Test Case 2: DAG with Multiple Valid Sorts
    // (The specific output depends on the algorithm's determinism)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> 2, 1 -> 2, 0 -> 3, 1 -> 3
        // Possible sorts: [0, 1, 2, 3], [1, 0, 2, 3], [0, 1, 3, 2], [1, 0, 3, 2]
        // (if processing nodes 0 then 1 for sources)
        constexpr inline auto list = nmtools_tuple{
            array{2, 3},       // Node 0 neighbors
            array{2, 3},       // Node 1 neighbors
            array<int,0>(),    // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // A common deterministic output (e.g., Kahn's algorithm processing lower index nodes first)
        constexpr inline auto sorted_nodes = array{0, 1, 2, 3};
        // Alternative if node 1 was processed first: array{1, 0, 2, 3}
        // Alternative if dependency 3 was processed before 2: array{0, 1, 3, 2}
    }

    //----------------------------------------------------
    // Test Case 3: Graph with a Cycle
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1, 1 -> 2, 2 -> 0 (cycle)
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array{0},          // Node 2 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // No topological sort possible due to cycle
        constexpr inline auto sorted_nodes = meta::Nothing;
    }

    //----------------------------------------------------
    // Test Case 4: Empty Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple<>{}; // Empty adjacency list
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Sort of an empty graph is an empty list.
        constexpr inline array<int,0> sorted_nodes {};
    }

    //----------------------------------------------------
    // Test Case 5: DAG with Disconnected Components
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: 0 -> 1,  2 -> 3
        // Nodes 0,1 form one component; 2,3 form another.
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // One possible deterministic sort: [0, 2, 1, 3] (processing 0 then 2 as initial sources)
        // Another: [2, 0, 1, 3] (processing 2 then 0 as initial sources)
        // Assuming nodes are processed in increasing order for initial sources:
        constexpr inline auto sorted_nodes = array{0, 2, 1, 3};
    }

    //----------------------------------------------------
    // Test Case 6: Single Node Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            array<int,0>(),    // Node 0 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto sorted_nodes = array{0};
    }

    //----------------------------------------------------
    // Test Case 7: More Complex DAG
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph:
        // 0 -> 1, 0 -> 2
        // 1 -> 3
        // 2 -> 3, 2 -> 4
        // 3 -> 5
        // 4 -> 5
        constexpr inline auto list = nmtools_tuple{
            array{1, 2},       // Node 0 neighbors
            array{3},          // Node 1 neighbors
            array{3, 4},       // Node 2 neighbors
            array{5},          // Node 3 neighbors
            array{5},          // Node 4 neighbors
            array<int,0>(),    // Node 5 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // One possible deterministic sort (e.g. Kahn's processing lower index first among available)
        // Initial: 0
        // Q: [0], In-degrees: [0:0, 1:1, 2:1, 3:2, 4:1, 5:2]
        // Pop 0. Q: [], Sort: [0]. Neighbors of 0 are 1,2. Dec in-degree of 1,2.
        // In-degrees: [0:-, 1:0, 2:0, 3:2, 4:1, 5:2]. Add 1,2 to Q.
        // Q: [1,2]
        // Pop 1. Q: [2], Sort: [0,1]. Neighbors of 1 is 3. Dec in-degree of 3.
        // In-degrees: [0:-, 1:-, 2:0, 3:1, 4:1, 5:2].
        // Pop 2. Q: [], Sort: [0,1,2]. Neighbors of 2 are 3,4. Dec in-degree of 3,4.
        // In-degrees: [0:-, 1:-, 2:-, 3:0, 4:0, 5:2]. Add 3,4 to Q.
        // Q: [3,4]
        // Pop 3. Q: [4], Sort: [0,1,2,3]. Neighbors of 3 is 5. Dec in-degree of 5.
        // In-degrees: [0:-, 1:-, 2:-, 3:-, 4:0, 5:1].
        // Pop 4. Q: [], Sort: [0,1,2,3,4]. Neighbors of 4 is 5. Dec in-degree of 5.
        // In-degrees: [0:-, 1:-, 2:-, 3:-, 4:-, 5:0]. Add 5 to Q.
        // Q: [5]
        // Pop 5. Q: [], Sort: [0,1,2,3,4,5].
        constexpr inline auto sorted_nodes = array{0, 1, 2, 3, 4, 5};
    }

    //----------------------------------------------------
    // Test Case 8: Graph with a Self-Loop (Cycle)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Graph: 0 -> 1, 1 -> 1 (self-loop)
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array{1},          // Node 1 neighbors (points to itself)
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        // No topological sort possible due to self-loop.
        constexpr inline auto sorted_nodes = meta::Nothing;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_TOPOLOGICAL_SORT_HPP