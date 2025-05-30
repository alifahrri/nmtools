#ifndef NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, has_path)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using nmtools_static_vector;

    //----------------------------------------------------
    // Test Case 1: Simple Path Exists
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array{2},          // Node 1 neighbors
            array<int,0>(),    // Node 2 neighbors
        };

        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;
        // Path: 0 -> 1 -> 2

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline bool exists = true;
    }

    //----------------------------------------------------
    // Test Case 2: No Path Exists
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> 1,  2 -> 3 (disconnected from 0,1)
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
            array{3},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 3;
        // No path from 0 to 3

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline bool exists = false;
    }

    //----------------------------------------------------
    // Test Case 3: Path to Self
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 0;
        // A node is considered to have a path to itself.

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline bool exists = true;
    }

    //----------------------------------------------------
    // Test Case 4: Path in Disconnected Component
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0 -> 1, Node 2 is isolated
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
            array<int,0>(),    // Node 2 neighbors (isolated)
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;
        // No path from 0 to the isolated node 2

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline bool exists = false;
    }

    //----------------------------------------------------
    // Test Case 5: More Complex Graph - Path Exists
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: 0->{1,2}, 1->{3}, 2->{4}, 3->{}, 4->{0} (cycle)
        constexpr inline auto list = nmtools_tuple{
            array{1,2},        // Node 0 neighbors
            array{3},          // Node 1 neighbors
            array{4},          // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors
            array{0},          // Node 4 neighbors (creates cycle 0-2-4-0)
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 3;
        // Path: 0 -> 1 -> 3

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline bool exists = true;
    }

    //----------------------------------------------------
    // Test Case 6: More Complex Graph - No Path
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph: 0->{1}, 1->{0} (cycle), 2->{3}, 3->{2} (another cycle)
        constexpr inline auto list = nmtools_tuple{
            array{1},        // Node 0 neighbors
            array{0},        // Node 1 neighbors
            array{3},        // Node 2 neighbors
            array{2},        // Node 3 neighbors
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 2;
        // No path from component {0,1} to component {2,3}

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline bool exists = false;
    }

    //----------------------------------------------------
    // Test Case 7: Target node does not exist (implicitly)
    // (Assuming nodes are 0 to N-1 based on list size)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
        };
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 5; // Node 5 is out of bounds
        
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Behavior for out-of-bounds target might depend on implementation.
        // Assuming false if target is not a valid node index.
        constexpr inline bool exists = false;
    }

    //----------------------------------------------------
    // Test Case 8: Empty graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple<>{}; // Empty adjacency list
        constexpr inline auto source_node = 0;
        constexpr inline auto target_node = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline bool exists = false; // No nodes, so no path
    }


}

#endif // NMTOOLS_TESTING_DATA_NETWORK_HAS_PATH_HPP