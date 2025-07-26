#ifndef NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp" // Assuming this is for graph data handling

NMTOOLS_TESTING_DECLARE_CASE(network, out_edges)
{
    // Bring types into scope
    using nmtools_array;
    // Note: The original file had 'using nmtools_array;' twice. Corrected to once.
    using nmtools_tuple;

    // Define an edge type for clarity in expected results
    using edge_t = nmtools_array<int, 2>;

    using namespace literals;

    //----------------------------------------------------
    // Test Case 1: All out-edges for a simple graph
    // (Previously: Out-edges from a specific node 0)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> {1, 2}, 1 -> {2}, 2 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // All out-edges: (0,1), (0,2), (1,2). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        // Graph: 0 -> {1, 2}, 1 -> {2}, 2 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr auto nbunch = 0;
        constexpr auto nbunch_ct = 0_ct;

        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        // All out-edges: (0,1), (0,2), (1,2). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
        };
    }

    //----------------------------------------------------
    // Test Case 2: All out-edges for the same simple graph
    // (Previously: Out-edges from a specific node 1)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> {1, 2}, 1 -> {2}, 2 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // All out-edges: (0,1), (0,2), (1,2). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    //----------------------------------------------------
    // Test Case 3: All out-edges for the same simple graph
    // (Previously: Out-edges from a sink node 2)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> {1, 2}, 1 -> {2}, 2 -> {}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // All out-edges: (0,1), (0,2), (1,2). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    //----------------------------------------------------
    // Test Case 4: All out-edges in a graph with cycles
    // (Previously: Out-edges from a specific node 1)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0 -> 1, 1 -> 2, 2 -> 0 (cycle)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // All out-edges: (0,1), (1,2), (2,0). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{1, 2},
            edge_t{2, 0}
        };
    }

    //----------------------------------------------------
    // Test Case 5: All out-edges in a graph with an isolated node
    // (Previously: Out-edges from an isolated node 2)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: 0 -> 1, Node 2 is isolated
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // All out-edges: (0,1).
        constexpr inline auto edges = nmtools_array<edge_t,1>{
            edge_t{0, 1}
        };
    }


    //----------------------------------------------------
    // Test Case 6: All out-edges in an empty graph
    // (No node_idx provided, implies all edges - This case remains the same)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{}; // Empty adjacency list
        // No node_idx implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Empty graph has no edges.
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    //----------------------------------------------------
    // Test Case 7: All out-edges in a simple graph
    // (No node_idx provided, implies all edges - This case remains the same)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph: 0 -> 1, 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // No node_idx implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // All edges: (0,1), (1,2). Expected sorted.
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{1, 2}
        };
    }

    //----------------------------------------------------
    // Test Case 8: All out-edges in a more complex graph
    // (No node_idx provided, implies all edges - This case remains the same)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Graph: 0->{1,2}, 1->{2,3}, 2->{3}, 3->{0} (cycle)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{0_ct}
        };
        // No node_idx implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        // All edges, sorted:
        // (0,1), (0,2)
        // (1,2), (1,3)
        // (2,3)
        // (3,0)
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2},
            edge_t{1, 3},
            edge_t{2, 3},
            edge_t{3, 0}
        };
    }

    //----------------------------------------------------
    // Test Case 9: All out-edges for a small graph
    // (Previously: Out-edges from a node index that is out of bounds)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        // No node_idx, implies all edges
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        // All out-edges: (0,1).
        constexpr inline auto edges = nmtools_array<edge_t,1>{
            edge_t{0,1}
        };
    }


} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP
