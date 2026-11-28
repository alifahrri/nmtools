#ifndef NMTOOLS_TESTING_DATA_NETWORK_TO_UNDIRECTED_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_TO_UNDIRECTED_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Symmetrizes an adjacency list: u is in adj[v] iff v is in adj[u]. Neighbors are
// deduplicated and sorted ascending, self loops are kept, and the number of nodes
// is preserved. An edge targeting a node outside [0, num_nodes) yields meta::Nothing,
// where networkx would silently create that node. Expectations cross-checked
// against networkx 3.7 (nx.Graph + add_nodes_from(range(n)) + add_edge).
NMTOOLS_TESTING_DECLARE_CASE(network, to_undirected)
{
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    // 0->{1,2}, 1->{2} ; every missing direction gets added
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{0, 2},
            nmtools_array{0, 1}
        };
    }

    // directed 3-cycle ; not symmetric: each node gains the other direction
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
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
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{0, 2},
            nmtools_array{0, 1}
        };
    }

    // self loop stays in its own row
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{0, 1},
            nmtools_array{0}
        };
    }

    // parallel entries collapse into one edge
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0}
        };
    }

    // isolated nodes keep empty rows
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // star centered on node 1
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct, 2_ct, 3_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0, 2, 3},
            nmtools_array{1},
            nmtools_array{1}
        };
    }

    // in-edges become out-edges
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{0},
            nmtools_array{0}
        };
    }

    // node 5 doesn't exist ; networkx would create it. NOTE: only the runtime
    // path is pinned here, folding an invalid constant graph to meta::Nothing
    // is still an open decision
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto undirected = meta::Nothing;
    }

    // empty graph
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto undirected = nmtools_tuple{};
    }

    // no edges at all (a single-row graph can't be used here: cast flattens it)
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // complete digraph ; already symmetric
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{0_ct, 1_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{0, 2},
            nmtools_array{0, 1}
        };
    }

    // self loops on nodes without other edges
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{},
            nmtools_tuple{2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{0},
            nmtools_array<int,0>{},
            nmtools_array{2}
        };
    }

    // two parents sharing a child plus a tail (shape of stackifier conflicts)
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array{0, 1, 3},
            nmtools_array{2}
        };
    }

    // unsorted rows get sorted ascending
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{3_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct, 0_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline auto undirected = nmtools_tuple{
            nmtools_array{2, 3},
            nmtools_array{3},
            nmtools_array{0, 3},
            nmtools_array{0, 1, 2}
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_TO_UNDIRECTED_HPP
