#ifndef NMTOOLS_TESTING_DATA_NETWORK_IN_EDGES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_IN_EDGES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Mirrors nx.DiGraph.in_edges: (src,dst) pairs grouped by dst, dsts in nbunch
// order (all nodes ascending when nbunch is none), srcs ascending, keys
// ascending for multigraphs. Duplicate nbunch entries are visited once, plain
// digraphs collapse parallel rows into one edge, and out-of-range nbunch
// entries are skipped (nx raises instead). Expectations cross-checked against
// networkx 3.7.
NMTOOLS_TESTING_DECLARE_CASE(network, in_edges)
{
    using nmtools_array;
    using nmtools_tuple;

    using edge_t  = nmtools_array<int, 2>;
    using edge3_t = nmtools_array<int, 3>;

    using namespace literals;

    // 0->{1,2}, 1->{2} ; every in-edge
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto src_node_ids = nmtools_array{10,20,30};
        constexpr inline auto src_node_ids_ct = nmtools_tuple{10_ct,20_ct,30_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
        constexpr inline auto edges_ids = nmtools_array{
            edge_t{10, 20},
            edge_t{10, 30},
            edge_t{20, 30}
        };
    }

    // same graph, single nbunch (dst = 2)
    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = 2;
        constexpr inline auto nbunch_ct = 2_ct;
        constexpr inline auto src_node_ids = nmtools_array{10,20,30};
        constexpr inline auto src_node_ids_ct = nmtools_tuple{10_ct,20_ct,30_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 2},
            edge_t{1, 2}
        };
        constexpr inline auto edges_ids = nmtools_array{
            edge_t{10, 30},
            edge_t{20, 30}
        };
    }

    // same graph, nbunch = 0 ; node 0 has no in-edge
    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = 0;
        constexpr inline auto nbunch_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    // 0->{2}, 1->{0}, 2->{1} ; nbunch order is respected
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct}
        };
        constexpr inline auto nbunch = nmtools_array{2, 0};
        constexpr inline auto src_node_ids = nmtools_array{10,20,30};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 2},
            edge_t{1, 0}
        };
        constexpr inline auto edges_ids = nmtools_array{
            edge_t{10, 30},
            edge_t{20, 10}
        };
    }

    // same graph, reversed nbunch
    NMTOOLS_TESTING_DECLARE_ARGS(case2b)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct}
        };
        constexpr inline auto nbunch = nmtools_array{0, 2};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2b)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{1, 0},
            edge_t{0, 2}
        };
    }

    // duplicate nbunch entries are visited once
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = nmtools_array{2, 2};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    // parallel rows: plain digraph keeps one edge per (src,dst)
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{}
        };
        constexpr inline auto src_node_ids = nmtools_array{10,20};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline nmtools_array<edge_t,1> edges {
            edge_t{0, 1}
        };
        constexpr inline nmtools_array<edge_t,1> edges_ids {
            edge_t{10, 20}
        };
    }

    // multigraph: parallel rows become edges with ascending keys
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = nmtools_array{2, 0};
        constexpr inline auto multi = nmtools::True;
        constexpr inline auto src_node_ids = nmtools_array{10,20,30};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto edges = nmtools_array{
            edge3_t{0, 2, 0},
            edge3_t{0, 2, 1},
            edge3_t{1, 2, 0}
        };
        constexpr inline auto edges_ids = nmtools_array{
            edge3_t{10, 30, 0},
            edge3_t{10, 30, 1},
            edge3_t{20, 30, 0}
        };
    }

    // self-loops
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 0},
            edge_t{1, 1}
        };
    }

    // out-of-range nbunch is skipped
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = 5;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    // cycle 0->3->2->1->0 ; dst ascending, not src ascending
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{3_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{1, 0},
            edge_t{2, 1},
            edge_t{3, 2},
            edge_t{0, 3}
        };
    }

    // 3-cycle
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{2, 0},
            edge_t{0, 1},
            edge_t{1, 2}
        };
    }

    // empty nbunch
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = nmtools_array<int,0>{};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    // nbunch on a node without in-edges (isolated)
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    // digraph only: unknown node id (networkx raises) -> Nothing
    // NOTE: nbunch is a node id here, not an index
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline auto nbunch = 99;
        constexpr inline auto nbunch_bad = nmtools_array{99, 30};
        constexpr inline auto src_node_ids = nmtools_array{10,20,30};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto edges_ids = meta::Nothing;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_IN_EDGES_HPP
