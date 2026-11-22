#ifndef NMTOOLS_TESTING_DATA_NETWORK_BFS_EDGES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_BFS_EDGES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Mirrors nx.bfs_edges (reverse=False/True): (discoverer, discovered) pairs
// in BFS discovery order, Nothing when source is out of range.
// Expectations cross-checked against networkx 3.7 (exact sequence).
NMTOOLS_TESTING_DECLARE_CASE(network, bfs_edges)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    using pair_t = nmtools_array<int, 2>;

    // 0->2, 1->2, 3->2 ; fan-in at sink 2
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
            nmtools_tuple{2_ct}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto forward_flag = false;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline nmtools_array<pair_t,0> edges {};
        constexpr inline auto redges = nmtools_array{
            pair_t{2, 0},
            pair_t{2, 1},
            pair_t{2, 3}
        };
    }

    // 0->1->2 ; reverse layers (2,1),(1,0)
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 2;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 2_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline nmtools_array<pair_t,0> edges {};
        constexpr inline auto redges = nmtools_array{
            pair_t{2, 1},
            pair_t{1, 0}
        };
    }

    // 0->1, 0->2 ; forward star from the root
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto edges = nmtools_array{
            pair_t{0, 1},
            pair_t{0, 2}
        };
        constexpr inline nmtools_array<pair_t,0> redges {};
    }

    // 0->1, 1->2, 1->0, 2->0 ; cycle through source, succ row order {2,0}
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct, 0_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto edges = nmtools_array{
            pair_t{0, 1},
            pair_t{1, 2}
        };
        constexpr inline auto redges = nmtools_array{
            pair_t{0, 1},
            pair_t{0, 2}
        };
    }

    // diamond + cycle ; reverse BFS from sink 4
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
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 4_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline nmtools_array<pair_t,0> edges {};
        constexpr inline auto redges = nmtools_array{
            pair_t{4, 2},
            pair_t{4, 3},
            pair_t{2, 0},
            pair_t{3, 1}
        };
    }

    // diamond + cycle ; forward BFS from root 0
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 4_ct},
            nmtools_tuple{0_ct, 4_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200,300,400,500};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct,500_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto edges = nmtools_array{
            pair_t{0, 1},
            pair_t{0, 2},
            pair_t{1, 3},
            pair_t{2, 4}
        };
        constexpr inline auto redges = nmtools_array{
            pair_t{0, 3},
            pair_t{3, 1},
            pair_t{3, 2}
        };
    }

    // 0->0 self-loop on source (2 rows: cast flattens single-row lists)
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 0;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto node_idx_ct = 0_ct;
        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline nmtools_array<pair_t,0> edges {};
        constexpr inline nmtools_array<pair_t,0> redges {};
    }

    // source out of range -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_idx = 5;
        constexpr inline auto reverse_flag = true;
        constexpr inline auto src_node_ids = nmtools_array{100,200};

        inline auto src_node_ids_ct = nmtools_tuple{100_ct,200_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto edges = meta::Nothing;
        constexpr inline auto redges = meta::Nothing;
    }

    // empty graph -> Nothing
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline auto node_idx = 0;
        constexpr inline auto reverse_flag = true;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto edges = meta::Nothing;
        constexpr inline auto redges = meta::Nothing;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_BFS_EDGES_HPP
