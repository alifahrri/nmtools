#ifndef NMTOOLS_TESTING_DATA_NETWORK_ANCESTORS_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_ANCESTORS_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Mirrors nx.ancestors (reverse BFS): unique ancestors sorted ascending, the
// seed(s) never reported, Nothing when a seed is invalid. A seed is `node_idx`
// or an element of `source_nodes` (multi-source); all seeds are excluded.
// Expectations cross-checked against networkx 3.7.
NMTOOLS_TESTING_DECLARE_CASE(network, ancestors)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    // 0->2, 1->2, 3->2 ; three direct predecessors
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{2_ct}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1, 3};
    }

    // 0->1->2 ; two-level reverse chain
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1};
    }

    // 0->1, 0->2 ; source has no predecessors
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
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
        constexpr inline nmtools_array<int,0> ancestors {};
    }

    // 0->1, 1->2, 1->0, 2->0 ; cycle through the source
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct, 0_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto ancestors = nmtools_array{1, 2};
    }

    // diamond + cycle ; multi-layer reverse BFS from sink 4
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{0_ct, 4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 4;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 4_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1, 2, 3};
    }

    // 0->0 self-loop on source (2 rows: cast flattens single-row lists)
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline nmtools_array<int,0> ancestors {};
    }

    // source out of range -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto ancestors = meta::Nothing;
    }

    // empty graph -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline auto node_idx = 0;
        constexpr inline auto node_idx_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto ancestors = meta::Nothing;
    }

    // multi-source {3,4} on the case5 graph
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{0_ct, 4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{3, 4};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1, 2};
    }

    // multi-source single-element seed == single-source result
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto source_nodes = nmtools_array{2};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1};
    }

    // multi-source ; two disconnected components
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{4_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{2, 4};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500,600};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct,600_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1, 3};
    }

    // multi-source ; seeds share one ancestor
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{1, 2};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto ancestors = nmtools_array{0};
    }

    // multi-source ; a seed is an ancestor of another seed
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{2, 3};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1};
    }

    // multi-source ; descending + duplicate seeds {4,3,4}
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline auto ancestors = nmtools_array{0, 1, 2};
    }

    // multi-source ; out-of-range seed -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline auto ancestors = meta::Nothing;
    }

    // multi-source ; all nodes are seeds
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto source_nodes = nmtools_array{0, 1, 2};
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        constexpr inline nmtools_array<int,0> ancestors {};
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
        constexpr inline nmtools_array<int,0> ancestors {};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_ANCESTORS_HPP
