#ifndef NMTOOLS_TESTING_DATA_NETWORK_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Number of distinct neighbours in the underlying undirected graph, matching
// nx.Graph(rows).degree. A self loop counts twice (networkx convention) and
// parallel entries collapse. Asymmetric input is measured on the underlying
// undirected graph too, so degree is invariant under to_undirected; use
// in_degree + out_degree for the networkx DiGraph.degree notion instead. A
// dangling target yields meta::Nothing (nx would create that node), pinned on
// the runtime path only, see the note in the to_undirected data header.
NMTOOLS_TESTING_DECLARE_CASE(network, degree)
{
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    // symmetric path ; endpoints 1, middle 2
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto degrees = nmtools_array{1, 2, 1};
    }

    // self loop counts twice
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto degrees = nmtools_array{2, 0};
    }

    // self loop plus a normal edge
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto degrees = nmtools_array{3, 1};
    }

    // isolated node has degree 0
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto degrees = nmtools_array{0, 1, 1};
    }

    // directed cycle ; underlying undirected degree
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto degrees = nmtools_array{2, 2, 2};
    }

    // one-way star ; needs the reverse direction of every edge
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
        constexpr inline auto degrees = nmtools_array{1, 3, 1, 1};
    }

    // parallel entries collapse into one neighbour
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto degrees = nmtools_array{1, 1};
    }

    // complete digraph ; 2 neighbours, not in_degree + out_degree = 4
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{0_ct, 1_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto degrees = nmtools_array{2, 2, 2};
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
        constexpr inline nmtools_array<int,0> degrees {};
    }

    // two self loops on separate nodes
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{},
            nmtools_tuple{2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto degrees = nmtools_array{2, 0, 2};
    }

    // node 5 doesn't exist
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto degrees = meta::Nothing;
    }

    // single reverse edge ; node 2 stays isolated
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto degrees = nmtools_array{1, 1, 0};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_DEGREE_HPP
