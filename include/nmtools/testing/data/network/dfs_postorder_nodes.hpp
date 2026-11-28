#ifndef NMTOOLS_TESTING_DATA_NETWORK_DFS_POSTORDER_NODES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_DFS_POSTORDER_NODES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Mirrors nx.dfs_postorder_nodes (iterative DFS): children-before-parents, the
// seed included last in its tree, unreachable nodes absent, child order = row
// order. Multi-source is the stackifier forest: seeds in order, a tree whose
// root was already emitted is skipped. Nothing when a seed is invalid.
// Expectations cross-checked against networkx 3.7.
NMTOOLS_TESTING_DECLARE_CASE(network, dfs_postorder_nodes)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    // 0->1->2 ; chain, the source is last
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0};
    }

    // 0->{1,2,3} + isolated 4 ; row order, isolated node absent
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto postorder = nmtools_array{1, 2, 3, 0};
    }

    // 0->{2,1} ; child order is row order, not sorted
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct, 1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0};
    }

    // diamond ; 3 is discovered through 1, so 2's edge to 3 is a cross edge
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto postorder = nmtools_array{3, 1, 2, 0};
    }

    // 0->1->2->0 ; back edge to the source
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0};
    }

    // nested branches ; sibling subtrees interleave
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500,600};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct,600_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto postorder = nmtools_array{3, 4, 1, 5, 2, 0};
    }

    // 0->0 self-loop on source (2 rows: cast flattens single-row lists)
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto postorder = nmtools_array{0};
    }

    // source out of range -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 5;
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto node_idx_ct = 5_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto postorder = meta::Nothing;
    }

    // empty graph -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline auto node_idx = 0;
        constexpr inline auto node_idx_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto postorder = meta::Nothing;
    }

    // cross edge from a later sibling: 1 discovers 2 before 0 reaches it
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto postorder = nmtools_array{2, 3, 1, 0};
    }

    // multi-source ; two disconnected components
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{0, 3};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0, 4, 3};
    }

    // multi-source ; seed already emitted as part of the first tree -> skipped
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{0, 1};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0};
    }

    // multi-source ; descending seeds, later seed reaches an emitted node
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto source_nodes = nmtools_array{2, 0};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto postorder = nmtools_array{2, 1, 0};
    }

    // multi-source ; every node is a seed == nx source=None (whole graph)
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{0, 1, 2, 3};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline auto postorder = nmtools_array{3, 2, 0, 1};
    }

    // multi-source ; duplicate + descending seeds {4,3,4}
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{0_ct, 4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{4, 3, 4};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline auto postorder = nmtools_array{4, 1, 2, 0, 3};
    }

    // multi-source ; out-of-range seed -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{0, 5};
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        constexpr inline auto postorder = meta::Nothing;
    }

    // multi-source ; empty seed set
    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array<int,0>{};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        constexpr inline nmtools_array<int,0> postorder {};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_DFS_POSTORDER_NODES_HPP
