#ifndef NMTOOLS_TESTING_DATA_NETWORK_INTERVAL_GRAPH_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_INTERVAL_GRAPH_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

// Live interval graph of half-open intervals [start[i], end[i]): node i is
// adjacent to node j (i < j) iff max(start[i], start[j]) < min(end[i], end[j]),
// so touching endpoints do not interfere and a zero length interval is always
// isolated. The result keeps one row per interval, rows ascending and
// symmetric, i.e. the input of greedy_color. Equivalent to networkx with
// closed intervals: nx.interval_graph([(start[i], end[i] - 1), ...]). An
// interval with start > end is invalid: meta::Nothing at runtime, a fail type
// when constant (see case14 and the static_assert in the test source).
NMTOOLS_TESTING_DECLARE_CASE(network, interval_graph)
{
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    // disjoint intervals ; no edges
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int32_t start[2] = {0, 5};
        inline int32_t end[2]   = {2, 7};

        inline auto start_ct = nmtools_tuple{0_ct, 5_ct};
        inline auto end_ct   = nmtools_tuple{2_ct, 7_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // overlap ; one edge
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int32_t start[2] = {0, 1};
        inline int32_t end[2]   = {3, 4};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct};
        inline auto end_ct   = nmtools_tuple{3_ct, 4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0}
        };
    }

    // touching endpoints ; half-open, so no edge
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int32_t start[2] = {0, 1};
        inline int32_t end[2]   = {1, 2};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct};
        inline auto end_ct   = nmtools_tuple{1_ct, 2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // nested intervals ; one edge
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int32_t start[2] = {0, 2};
        inline int32_t end[2]   = {6, 3};

        inline auto start_ct = nmtools_tuple{0_ct, 2_ct};
        inline auto end_ct   = nmtools_tuple{6_ct, 3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0}
        };
    }

    // K3 clique ; every pair interferes, so greedy_color needs 3 slots
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int32_t start[3] = {0, 1, 2};
        inline int32_t end[3]   = {3, 4, 5};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct, 2_ct};
        inline auto end_ct   = nmtools_tuple{3_ct, 4_ct, 5_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{0, 2},
            nmtools_array{0, 1}
        };
    }

    // K4 clique ; every row lists the other three nodes
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int32_t start[4] = {0, 1, 2, 3};
        inline int32_t end[4]   = {4, 5, 6, 7};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct, 2_ct, 3_ct};
        inline auto end_ct   = nmtools_tuple{4_ct, 5_ct, 6_ct, 7_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1, 2, 3},
            nmtools_array{0, 2, 3},
            nmtools_array{0, 1, 3},
            nmtools_array{0, 1, 2}
        };
    }

    // mixed 4 nodes ; edges 0-1, 0-3, 1-3, 2-3
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int32_t start[4] = {0, 1, 4, 2};
        inline int32_t end[4]   = {3, 4, 6, 5};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct, 4_ct, 2_ct};
        inline auto end_ct   = nmtools_tuple{3_ct, 4_ct, 6_ct, 5_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1, 3},
            nmtools_array{0, 3},
            nmtools_array{3},
            nmtools_array{0, 1, 2}
        };
    }

    // zero length interval next to a non-empty one ; isolated
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int32_t start[2] = {2, 2};
        inline int32_t end[2]   = {2, 3};

        inline auto start_ct = nmtools_tuple{2_ct, 2_ct};
        inline auto end_ct   = nmtools_tuple{2_ct, 3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // zero length interval inside a longer one ; still isolated
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int32_t start[2] = {2, 0};
        inline int32_t end[2]   = {2, 4};

        inline auto start_ct = nmtools_tuple{2_ct, 0_ct};
        inline auto end_ct   = nmtools_tuple{2_ct, 4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // identical ranges ; interfere like any other overlap
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int32_t start[2] = {0, 0};
        inline int32_t end[2]   = {4, 4};

        inline auto start_ct = nmtools_tuple{0_ct, 0_ct};
        inline auto end_ct   = nmtools_tuple{4_ct, 4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0}
        };
    }

    // unsorted starts ; the scan must not assume ascending input
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int32_t start[2] = {3, 1};
        inline int32_t end[2]   = {6, 4};

        inline auto start_ct = nmtools_tuple{3_ct, 1_ct};
        inline auto end_ct   = nmtools_tuple{6_ct, 4_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{0}
        };
    }

    // chain of touching intervals ; no edges at all
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int32_t start[3] = {0, 1, 2};
        inline int32_t end[3]   = {1, 2, 3};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct, 2_ct};
        inline auto end_ct   = nmtools_tuple{1_ct, 2_ct, 3_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // no intervals ; empty adjacency list (a program with nothing spilled)
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline nmtools_array<int32_t,0> start {};
        inline nmtools_array<int32_t,0> end   {};

        inline auto start_ct = nmtools_tuple{};
        inline auto end_ct   = nmtools_tuple{};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto adj = nmtools_tuple{};
    }

    // start > end ; only the runtime path is pinned here, the constant
    // rejection is a static_assert in the test source (case14)
    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int32_t start[2] = {0, 4};
        inline int32_t end[2]   = {3, 2};

        inline auto start_ct = nmtools_tuple{0_ct, 4_ct};
        inline auto end_ct   = nmtools_tuple{3_ct, 2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline auto adj = meta::Nothing;
    }

    // 5 nodes ; two overlapping clusters, colors {0, 2, 1, 2, 0}
    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int32_t start[5] = {0, 1, 1, 3, 5};
        inline int32_t end[5]   = {4, 2, 4, 6, 7};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct, 1_ct, 3_ct, 5_ct};
        inline auto end_ct   = nmtools_tuple{4_ct, 2_ct, 4_ct, 6_ct, 7_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array{1, 2, 3},
            nmtools_array{0, 2},
            nmtools_array{0, 1, 3},
            nmtools_array{0, 2, 4},
            nmtools_array{3}
        };
    }

    // single interval ; one empty row
    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int32_t start[1] = {0};
        inline int32_t end[1]   = {5};

        inline auto start_ct = nmtools_tuple{0_ct};
        inline auto end_ct   = nmtools_tuple{5_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{}
        };
    }

    // duplicate empty intervals ; zero length never interferes
    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int32_t start[2] = {1, 1};
        inline int32_t end[2]   = {1, 1};

        inline auto start_ct = nmtools_tuple{1_ct, 1_ct};
        inline auto end_ct   = nmtools_tuple{1_ct, 1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        constexpr inline auto adj = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    // mismatched lengths ; invalid just like an inverted interval (case14),
    // so meta::Nothing at runtime ; the constant rejection is a static_assert
    // in the test source. the overlapping entries are individually valid to
    // pin that only the length mismatch is reported
    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int32_t start[2] = {0, 1};
        inline int32_t end[3]   = {3, 4, 5};

        inline auto start_ct = nmtools_tuple{0_ct, 1_ct};
        inline auto end_ct   = nmtools_tuple{3_ct, 4_ct, 5_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(start)
        NMTOOLS_CAST_INDEX_ARRAYS(end)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        constexpr inline auto adj = meta::Nothing;
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_INTERVAL_GRAPH_HPP
