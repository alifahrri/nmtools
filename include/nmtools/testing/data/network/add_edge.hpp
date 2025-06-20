#ifndef NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, add_edge)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals; // For _ct suffix

    //----------------------------------------------------
    // Test Case 1: Simple Edge Addition
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Initial Graph: 0 -> 1, 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple<>{}
        };
        // Add edge: 0 -> 2
        constexpr inline int u = 0;
        constexpr inline int v = 2;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 2_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Expected Graph: 0 -> {1, 2}, 1 -> 2
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 2: Add an Edge from a Node with No Outgoing Edges
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Initial Graph: 0 -> 1, 2 is isolated
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{},
            nmtools_tuple<>{}
        };
        // Add edge: 2 -> 0
        constexpr inline int u = 2;
        constexpr inline int v = 0;
        
        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Expected Graph: 0 -> 1, 2 -> 0
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    //----------------------------------------------------
    // Test Case 3: Add a Duplicate Edge
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Initial Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Add edge: 0 -> 1 (already exists)
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Expected Graph: No change
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 4: Add a Self-Loop
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Initial Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Add edge: 1 -> 1
        constexpr inline int u = 1;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 1_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Expected Graph: 0 -> 1, 1 -> 1
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{1}
        };
    }

    //----------------------------------------------------
    // Test Case 5: Add an Edge to an Isolated Node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Initial Graph: 0 -> 1, node 2 is isolated
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{},
            nmtools_tuple<>{}
        };
        // Add edge: 2 -> 1
        constexpr inline int u = 2;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Expected Graph: 0 -> 1, 2 -> 1
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{1}
        };
    }

    //----------------------------------------------------
    // Test Case 6: Add Edge from a Non-Existent Source Node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Initial Graph has 2 nodes (0, 1). list.size() = 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Add edge from new node 2 to existing node 0
        // u = 2 is within list.size() + 2 constraint
        constexpr inline int u = 2;
        constexpr inline int v = 0;
        
        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expected graph has 3 nodes. Node 2 is added.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    //----------------------------------------------------
    // Test Case 7: Add Edge to a Non-Existent Target Node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Initial Graph has 2 nodes (0, 1). list.size() = 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Add edge from existing node 0 to new node 2
        // v = 2 is within list.size() + 2 constraint
        constexpr inline int u = 0;
        constexpr inline int v = 2;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 2_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Expected graph has 3 nodes. Node 2 is added.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 8: Add Edge where Both Nodes are New
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Initial Graph has 2 nodes (0, 1). list.size() = 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Add edge from new node 2 to new node 3
        // u=2, v=3 are within list.size() + 2 constraint
        constexpr inline int u = 2;
        constexpr inline int v = 3;

        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 3_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        // Expected graph has 4 nodes. Nodes 2 and 3 are added.
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{3},
            nmtools_array<int,0>{}
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP
