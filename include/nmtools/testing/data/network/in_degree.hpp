#ifndef NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, in_degree)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;

    //----------------------------------------------------
    // Test Case 1: Simple Linear Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 1 -> 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
        };
        // In-degrees:
        // Node 0: 0 (nothing points to 0)
        // Node 1: 1 (0 points to 1)
        // Node 2: 1 (1 points to 2)
        // Node 3: 1 (2 points to 3)
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
            array{2},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
        };
        // In-degrees:
        // Node 0: 0
        // Node 1: 0
        // Node 2: 2 (from 0 and 1)
        // Node 3: 1 (from 2)
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
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
            array<int,0>(),    // Node 4 neighbors (isolated)
        };
        // In-degrees:
        // Node 0: 0
        // Node 1: 1 (from 0)
        // Node 2: 0
        // Node 3: 1 (from 2)
        // Node 4: 0
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
            array{1},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array{0},          // Node 2 neighbors
            array{1},          // Node 3 neighbors
        };
        // In-degrees:
        // Node 0: 1 (from 2)
        // Node 1: 2 (from 0 and 3)
        // Node 2: 1 (from 1)
        // Node 3: 0
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
            array{1,2},        // Node 0 neighbors
            array{3},          // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array{4},          // Node 3 neighbors
            array{0,1},        // Node 4 neighbors
        };
        // In-degrees:
        // Node 0: 1 (from 4)
        // Node 1: 2 (from 0 and 4)
        // Node 2: 1 (from 0)
        // Node 3: 2 (from 1 and 2)
        // Node 4: 1 (from 3)
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto degrees = array{1, 2, 1, 2, 1}; // Expected in-degrees for nodes 0, 1, 2, 3, 4
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP