#ifndef NMTOOLS_TESTING_DATA_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, is_directed_acyclic_graph)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    //----------------------------------------------------
    // Test Case 1: Simple DAG (Linear Chain)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0 -> 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 2: Simple Cycle
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph: 0 -> 1 -> 2 -> 0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline bool result = false;
    }

    //----------------------------------------------------
    // Test Case 3: Graph with a Self-Loop
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1 -> 1 (self-loop)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{1_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline bool result = false;
    }

    //----------------------------------------------------
    // Test Case 4: Empty Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple<>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 5: Single Node Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 6: More Complex DAG (Diamond Shape)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph: 0 -> {1, 2}, 1 -> 3, 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 7: Disconnected Components (Both DAGs)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // Graph: 0 -> 1 and 2 -> 3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{},
            nmtools_tuple{3_ct},
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 8: Disconnected Components (One Cyclic)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        // Graph: 0 -> 1 and 2 -> 3 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple<>{},
            nmtools_tuple{3_ct},
            nmtools_tuple{2_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline bool result = false;
    }

    //----------------------------------------------------
    // Test Case 9: All Nodes Pointing to a Single Sink
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // Graph: 0->3, 1->3, 2->3
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline bool result = true;
    }
    
    //----------------------------------------------------
    // Test Case 10: One Source Pointing to All Other Nodes
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        // Graph: 0 -> {1, 2, 3}
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 3_ct},
            nmtools_tuple<>{},
            nmtools_tuple<>{},
            nmtools_tuple<>{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline bool result = true;
    }

    //----------------------------------------------------
    // Test Case 11: Graph with a Cycle Not Involving All Nodes
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        // Graph: 0 -> 1, 1 -> 2 -> 1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{1_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline bool result = false;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP
