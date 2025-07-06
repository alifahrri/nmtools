#ifndef NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp" // Assuming this is for graph data handling

NMTOOLS_TESTING_DECLARE_CASE(network, contracted_edge)
{
    // Bring types into scope
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    // Helper for re-indexing (conceptual, actual logic is in the function being tested)
    // auto remap_node = [](int node_idx, int v_removed_idx) {
    //     if (node_idx < v_removed_idx) return node_idx;
    //     if (node_idx > v_removed_idx) return node_idx - 1;
    //     return -1; // Should not happen for nodes that are kept
    // };

    //----------------------------------------------------
    // Test Case 1: Square Graph, contract (0,1), self_loops = true
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph: 0-1, 0-3, 1-2, 2-3 (A square)
        // 0: [1, 3]
        // 1: [0, 2]
        // 2: [1, 3]
        // 3: [0, 2]
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1}; // u=0 (kept), v=1 (removed)
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{10_ct,11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,4>{"n10","n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Original 0 -> New 0 (u_mapped)
        // Original 1 -> Removed (merged into New 0)
        // Original 2 -> New 1
        // Original 3 -> New 2
        // New 0 (from O0, O1): Neighbors of O0 (excl. O1): {O3}->{N2}. Neighbors of O1 (excl. O0): {O2}->{N1}. Edge (O1,O0) -> self-loop (N0,N0).
        //                     Result: {N0, N1, N2} -> {0,1,2}
        // New 1 (from O2): Neighbors of O2: {O1,O3}. (O2,O1)->(N1,N0). (O2,O3)->(N1,N2). Result: {N0,N2} -> {0,2}
        // New 2 (from O3): Neighbors of O3: {O0,O2}. (O3,O0)->(N2,N0). (O3,O2)->(N2,N1). Result: {N0,N1} -> {0,1}
        constexpr inline auto contracted_list = nmtools_tuple{
            array{0, 1, 2},    // New Node 0 (was Original 0)
            array{0, 2},       // New Node 1 (was Original 2)
            array{0, 1}        // New Node 2 (was Original 3)
        };
        constexpr inline auto dst_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
    }

    //----------------------------------------------------
    // Test Case 2: Square Graph, contract (0,1), self_loops = false
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1}; // u=0, v=1
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{10_ct,11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,4>{"n10","n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Same as case1, but self-loop (0,0) on New Node 0 is removed.
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1, 2},       // New Node 0 (was Original 0)
            array{0, 2},       // New Node 1 (was Original 2)
            array{0, 1}        // New Node 2 (was Original 3)
        };
        constexpr inline auto dst_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
    }

    //----------------------------------------------------
    // Test Case 3: Line Graph 0->1->2, contract (0,1), self_loops = true
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: 0 -> 1, 1 -> 2
        // 0: [1]
        // 1: [2]
        // 2: []
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{0, 1}; // u=0, v=1
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Original 0 -> New 0 (u_mapped)
        // Original 1 -> Removed
        // Original 2 -> New 1
        // New 0 (from O0, O1): O0 neigh: {O1} (contracted). O1 neigh: {O2}->{N1}. No (O1,O0) edge. Result: {N1} -> {1}
        // New 1 (from O2): O2 neigh: {}. Result: {}
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},          // New Node 0 (was Original 0)
            array<int,0>{}     // New Node 1 (was Original 2)
        };
        inline auto dst_node_ids = nmtools_tuple{12_ct,13_ct};
    }

    //----------------------------------------------------
    // Test Case 4: Line Graph 0->1<-2 (reversed middle edge), contract (1,0), self_loops = true
    // u_orig (1) > v_orig (0)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0 <- 1 -> 2  (0 is pointed to by 1, 1 points to 2)
        // 0: []
        // 1: [0, 2]
        // 2: []
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{1, 0}; // u=1 (kept), v=0 (removed)
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{1_ct,0_ct};
        constexpr inline auto self_loops_flag_ct  = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Original 0 -> Removed (merged into Original 1 / New 0)
        // Original 1 -> New 0 (u_mapped, since 1 > 0, new index is 1-1=0)
        // Original 2 -> New 1 (since 2 > 0, new index is 2-1=1)
        // New 0 (from O1, O0): O1 neigh: {O0,O2}. (O1,O0) contracted. (O1,O2)->(N0,N1).
        //                     O0 neigh: {}.
        //                     Is O1 in O0's original adj? No. Is O0 in O1's original adj? Yes, (1,0) is contracted.
        //                     This means (O0,O1) was an implicit edge for contraction.
        //                     The edge (1,0) is the one being contracted.
        //                     If (0,1) existed, it would make a self-loop. Here, no.
        //                     Let's trace: u=1, v=0.
        //                     Neighbors of u=1 (excluding v=0): {2}. Mapped: {idx_new(2,0)=1}. So, {1}.
        //                     Neighbors of v=0 (excluding u=1): {}. Mapped: {}.
        //                     Self-loop check: Is u (1) a neighbor of v (0)? No. Is v (0) a neighbor of u (1)? Yes.
        //                     The edge (1,0) is the one contracted. If there was another edge (0,1), it would form a self loop.
        //                     Since (0,1) is not an edge, no self-loop from this.
        //                     Result for New0: {1}
        // New 1 (from O2): O2 neigh: {}. Result: {}
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},          // New Node 0 (was Original 1)
            array<int,0>{}     // New Node 1 (was Original 2)
        };

        inline auto dst_node_ids = nmtools_tuple{11_ct,13_ct};
    }
    //----------------------------------------------------
    // Test Case 5: Test Case 4 with self_loops = false
    // (Result should be the same as no self-loop was formed)
    //----------------------------------------------------
     NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto edge_to_contract = array{1, 0}; // u=1 (kept), v=0 (removed)
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{1_ct,0_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{11_ct,12_ct,13_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12","n13"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto contracted_list = nmtools_tuple{
            array{1},
            array<int,0>{}
        };

        inline auto dst_node_ids = nmtools_tuple{11_ct,13_ct};
    }


    //----------------------------------------------------
    // Test Case 6: Graph that forms a self-loop from v's connection to u
    // 0 -> 1, 1 -> 0. Contract (0,1)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph: 0 -> 1, 1 -> 0
        // 0: [1]
        // 1: [0]
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1}; // u=0, v=1
        constexpr inline bool self_loops_flag = true;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct = 1_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{100_ct,200_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Original 0 -> New 0 (u_mapped)
        // Original 1 -> Removed
        // New 0 (from O0, O1): O0 neigh: {O1} (contracted). O1 neigh: {O0}. Edge (O1,O0) becomes self-loop (N0,N0).
        // Result: {N0} -> {0}
        constexpr inline auto contracted_list = nmtools_tuple{
            array{0}           // New Node 0 (was Original 0)
        };

        inline auto dst_node_ids = nmtools_tuple{200_ct};
    }

    //----------------------------------------------------
    // Test Case 7: Test Case 6 with self_loops = false
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto edge_to_contract = array{0, 1}; // u=0, v=1
        constexpr inline bool self_loops_flag = false;

        constexpr inline auto edge_to_contract_ct = nmtools_tuple{0_ct,1_ct};
        constexpr inline auto self_loops_flag_ct  = 0_ct;

        constexpr inline auto src_node_ids = nmtools_tuple{100_ct,200_ct};
        inline auto node_attributes = nmtools_array<nmtools_string,3>{"n11","n12"};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        // Self-loop (0,0) on New Node 0 is removed.
        constexpr inline auto contracted_list = nmtools_tuple{
            array<int,0>{}     // New Node 0 (was Original 0)
        };

        inline auto dst_node_ids = nmtools_tuple{200_ct};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_CONTRACTED_EDGE_HPP
