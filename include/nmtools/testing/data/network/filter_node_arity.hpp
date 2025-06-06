#ifndef NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp" // Assuming this is for graph data handling

NMTOOLS_TESTING_DECLARE_CASE(network, filter_node_arity)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals; // For _ct suffix

    //----------------------------------------------------
    // Test Case 1: Empty Graph, Arity 0 (from test_empty_graph)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple<>{};
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    //----------------------------------------------------
    // Test Case 2: Empty Graph, Arity 1 (from test_empty_graph)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple<>{};
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    //----------------------------------------------------
    // Test Case 3: Single Node No Edges, Arity 0 (from test_single_node_no_edges)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{
            // Node 0, in-degree 0
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Topo sort: [0]. Node 0 has in-degree 0.
        constexpr inline auto result_nodes = array{0};
    }

    //----------------------------------------------------
    // Test Case 4: Single Node No Edges, Arity 1 (from test_single_node_no_edges)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{
            // Node 0, in-degree 0
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    //----------------------------------------------------
    // Test Case 5: Simple Line Graph, Arity 0 (from test_simple_line_graph)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // 0 -> 1 -> 2 -> 3
        // In-degrees: 0:0, 1:1, 2:1, 3:1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Topo: [0,1,2,3]. Node 0 has in-degree 0.
        constexpr inline auto result_nodes = array{0};
    }

    //----------------------------------------------------
    // Test Case 6: Simple Line Graph, Arity 1 (from test_simple_line_graph)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Topo: [0,1,2,3]. Nodes 1,2,3 have in-degree 1.
        constexpr inline auto result_nodes = array{1, 2, 3};
    }

    //----------------------------------------------------
    // Test Case 7: Node with Multiple Predecessors, Arity 2 (from test_node_with_multiple_predecessors)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        // 0 -> 2, 1 -> 2 (Node 2 has in-degree 2)
        // 2 -> 3 (Node 3 has in-degree 1)
        // In-degrees: 0:0, 1:0, 2:2, 3:1
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Topo: [0,1,2,3]. Node 2 has in-degree 2.
        constexpr inline auto result_nodes = array{2};
    }
    
    //----------------------------------------------------
    // Test Case 8: Node with Multiple Predecessors, Arity 0
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        // Topo: [0,1,2,3]. Nodes 0,1 have in-degree 0.
        constexpr inline auto result_nodes = array{0, 1};
    }

    //----------------------------------------------------
    // Test Case 9: Graph with Cycle, Arity 1 (from test_graph_with_cycle_expects_error)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // 0 -> 1, 1 -> 2, 2 -> 0 (cycle)
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        // Cycle detected, topological sort not possible.
        constexpr inline auto result_nodes = meta::Nothing;
    }

    //----------------------------------------------------
    // Test Case 10: Graph with Self-Loop, Arity 1 (from test_graph_with_self_loop_expects_error)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        // 0 -> 0 (self-loop), 0 -> 1, 1 -> 2
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        // Cycle (self-loop) detected.
        constexpr inline auto result_nodes = meta::Nothing;
    }

    //----------------------------------------------------
    // Test Case 11: More Complex DAG, Arity 1 (from test_more_complex_dag)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        // In-degrees: 0:0, 1:0, 2:2, 3:1, 4:2, 5:1
        // Topo (deterministic Kahn's): [0, 1, 2, 3, 4, 5]
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{4_ct}, 
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        // Nodes with in-degree 1, in topological order [0,1,2,3,4,5] are 3 and 5.
        constexpr inline auto result_nodes = array{3, 5};
    }

    //----------------------------------------------------
    // Test Case 12: More Complex DAG, Arity 2 (from test_more_complex_dag)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{4_ct}, 
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        // Nodes with in-degree 2, in topological order [0,1,2,3,4,5] are 2 and 4.
        constexpr inline auto result_nodes = array{2, 4};
    }

    //----------------------------------------------------
    // Test Case 13: Disconnected DAG Components, Arity 0 (from test_disconnected_dag_components)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        // Topo (deterministic Kahn's): [0, 1, 2, 3, 4, 5, 7, 6]
        // In-degrees: 0:0, 1:1, 2:0, 3:1, 4:0, 5:0, 6:2, 7:0
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{6_ct},
            nmtools_tuple{},
            nmtools_tuple{6_ct}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        // Nodes with in-degree 0, in topological order [0,1,2,3,4,5,7,6] are 0,2,4,5,7.
        constexpr inline auto result_nodes = array{0, 2, 4, 5, 7};
    }

    //----------------------------------------------------
    // Test Case 14: Disconnected DAG Components, Arity 2 (from test_disconnected_dag_components)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{6_ct},
            nmtools_tuple{},
            nmtools_tuple{6_ct}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        // Node with in-degree 2 is 6. In topological order [0,1,2,3,4,5,7,6].
        constexpr inline auto result_nodes = array{6};
    }

    //----------------------------------------------------
    // Test Case 15: Negative Arity (from test_negative_arity)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = -1; // Negative arity
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP