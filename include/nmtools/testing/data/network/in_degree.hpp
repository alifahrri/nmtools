#ifndef NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, in_degree)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    //----------------------------------------------------
    // Test Case 1: Simple Linear Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 1 -> 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{3_ct},          // Node 2 neighbors
            nmtools_tuple{},    // Node 3 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto degrees = array{0, 1, 1, 1}; // Expected in-degrees for nodes 0, 1, 2, 3
    }

    //----------------------------------------------------
    // Test Case 2: Node with Multiple Incoming Edges
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> 2, 1 -> 2, 2 -> 3, 3 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{3_ct},          // Node 2 neighbors
            nmtools_tuple{},    // Node 3 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto degrees = array{0, 0, 2, 1}; // Expected in-degrees for nodes 0, 1, 2, 3
    }

    //----------------------------------------------------
    // Test Case 3: Graph with Disconnected Nodes
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1, 2 -> 3, Node 4 is isolated
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct}, // Node 0 neighbors
            nmtools_tuple{},     // Node 1 neighbors
            nmtools_tuple{3_ct}, // Node 2 neighbors
            nmtools_tuple{},     // Node 3 neighbors
            nmtools_tuple{},     // Node 4 neighbors (isolated)
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto degrees = array{0, 1, 0, 1, 0}; // Expected in-degrees for nodes 0, 1, 2, 3, 4
    }

    //----------------------------------------------------
    // Test Case 4: Graph with a Cycle
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0 -> 1, 1 -> 2, 2 -> 0, 3 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},          // Node 0 neighbors
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{0_ct},          // Node 2 neighbors
            nmtools_tuple{1_ct},          // Node 3 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto degrees = array{1, 2, 1, 0}; // Expected in-degrees for nodes 0, 1, 2, 3
    }

    //----------------------------------------------------
    // Test Case 5: More Complex Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: 0->{1,2}, 1->{3}, 2->{3}, 3->{4}, 4->{0, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct,2_ct},        // Node 0 neighbors
            nmtools_tuple{3_ct},          // Node 1 neighbors
            nmtools_tuple{3_ct},          // Node 2 neighbors
            nmtools_tuple{4_ct},          // Node 3 neighbors
            nmtools_tuple{0_ct,1_ct},        // Node 4 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto degrees = array{1, 2, 1, 2, 1}; // Expected in-degrees for nodes 0, 1, 2, 3, 4
    }

    //----------------------------------------------------
    // Test Case 6: Empty Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple<>{}; // Empty adjacency list
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // In-degrees for an empty graph is an empty array.
        constexpr inline array<int,0> degrees {};
    }

    //----------------------------------------------------
    // Test Case 7: Single Node Graph (No Edges)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph: Node 0 exists, but has no outgoing (and thus no incoming from others) edges.
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // In-degree of Node 0 is 0.
        constexpr inline auto degrees = array{0};
    }

    //----------------------------------------------------
    // Test Case 8: Graph with a Self-Loop
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Graph: 0 -> 0 (self-loop), 0 -> 1, 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},       // Node 0 neighbors (includes self)
            nmtools_tuple{2_ct},          // Node 1 neighbors
            nmtools_tuple{}     // Node 2 neighbors
        };
        // In-degrees:
        // Node 0: 1 (from itself: 0->0)
        // Node 1: 1 (from 0: 0->1)
        // Node 2: 1 (from 1: 1->2)
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto degrees = array{1, 1, 1};
    }

    //----------------------------------------------------
    // Test Case 9: Graph with No Edges (Multiple Disconnected Nodes)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // Graph: Nodes 0, 1, 2 are all isolated (no edges at all)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},    // Node 0 neighbors
            nmtools_tuple{},    // Node 1 neighbors
            nmtools_tuple{}     // Node 2 neighbors
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        // In-degrees for all nodes are 0.
        constexpr inline auto degrees = array{0, 0, 0};
    }

    //----------------------------------------------------
    // Test Case 10: Complete Graph K3 (Directed)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        // Graph: 0->1, 0->2, 1->0, 1->2, 2->0, 2->1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},       // Node 0 neighbors
            nmtools_tuple{0_ct, 2_ct},       // Node 1 neighbors
            nmtools_tuple{0_ct, 1_ct}        // Node 2 neighbors
        };
        // In-degrees:
        // Node 0: from 1, 2 (count = 2)
        // Node 1: from 0, 2 (count = 2)
        // Node 2: from 0, 1 (count = 2)
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto degrees = array{2, 2, 2};
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP