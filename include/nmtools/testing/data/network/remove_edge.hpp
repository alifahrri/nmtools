#ifndef NMTOOLS_TESTING_DATA_NETWORK_REMOVE_EDGE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_REMOVE_EDGE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, remove_edge)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    //====================================================================
    // DiGraph Behavior Test Cases (multi = false or not provided)
    //====================================================================

    //----------------------------------------------------
    // Test Case 1: Simple Edge Removal
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Initial Graph: 0 -> {1, 2}, 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Expected Graph: 0 -> {2}, 1 -> 2
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 2: Attempt to Remove a Non-Existent Edge
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Initial Graph: 0 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{}
        };
        // Remove edge: 1 -> 0 (does not exist)
        constexpr inline int u = 1;
        constexpr inline int v = 0;

        constexpr inline auto u_ct = 1_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Expected Graph: No change
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 3: Remove a Self-Loop
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Initial Graph: 0 -> {0, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 0
        constexpr inline int u = 0;
        constexpr inline int v = 0;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Expected Graph: 0 -> {1}
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }

    //====================================================================
    // MultiDiGraph Behavior Test Cases (multi = true)
    //====================================================================

    //----------------------------------------------------
    // Test Case 4: Remove One of Two Parallel Edges
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Initial Graph: 0 -> {1, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;
        // Specify multi-graph behavior
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Expected: One instance of edge 0->1 is removed
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 5: Remove One of Multiple Parallel Edges Among Others
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Initial Graph: 0 -> {1, 2, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 1_ct},
            nmtools_tuple<>{},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;
        // Specify multi-graph behavior
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    //----------------------------------------------------
    // Test Case 6: Remove One of Two Parallel Self-Loops
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Initial Graph: 0 -> {0, 0, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 0_ct, 1_ct},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 0
        constexpr inline int u = 0;
        constexpr inline int v = 0;
        // Specify multi-graph behavior
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 0_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expected: One self-loop is removed
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{0, 1},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Initial Graph: 0 -> {1, 2, 1}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 1_ct},
            nmtools_tuple<>{},
            nmtools_tuple<>{}
        };
        // Remove edge: 0 -> 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;
        // Specify multi-graph behavior
        constexpr inline bool multi = true;
        constexpr inline auto key = 0;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;
        constexpr inline auto multi_ct = True;
        constexpr inline auto key_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{2,1},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_REMOVE_EDGE_HPP
