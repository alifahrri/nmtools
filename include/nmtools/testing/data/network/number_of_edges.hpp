#ifndef NMTOOLS_TESTING_DATA_NETWORK_NUMBER_OF_EDGES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_NUMBER_OF_EDGES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"
#include "nmtools/literals.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, number_of_edges)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    //====================================================================
    // Total Number of Edges (No u, v specified)
    //====================================================================

    //----------------------------------------------------
    // Test Case 1: Total edges in a simple graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0->1, 1->2, 2->0. Total edges = 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto expected = 3;
    }

    //----------------------------------------------------
    // Test Case 2: Total edges in a MultiDiGraph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0->1, 0->1, 1->0. Total edges = 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto expected = 3;
    }

    //----------------------------------------------------
    // Test Case 3: Total edges in an empty graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto expected = 0;
    }

    //====================================================================
    // Number of Edges Between Specific Nodes u and v
    //====================================================================

    //----------------------------------------------------
    // Test Case 4: Edges between nodes in a DiGraph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0->1, 1->2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // Count edges from 0 to 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto expected = 1;
    }

    //----------------------------------------------------
    // Test Case 5: No edges between specified nodes
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: 0->1, 1->2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        // Count edges from 1 to 0 (which don't exist)
        constexpr inline int u = 1;
        constexpr inline int v = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto expected = 0;
    }

    //----------------------------------------------------
    // Test Case 6: Parallel edges between nodes in a MultiDiGraph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph: 0->1, 0->1, 1->0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{0_ct}
        };
        // Count edges from 0 to 1
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto expected = 2;
    }

    //----------------------------------------------------
    // Test Case 7: Number of self-loops
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph: 0->0, 0->0, 0->1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 0_ct, 1_ct},
            nmtools_tuple{}
        };
        // Count self-loops on node 0
        constexpr inline int u = 0;
        constexpr inline int v = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto expected = 2;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_NUMBER_OF_EDGES_HPP
