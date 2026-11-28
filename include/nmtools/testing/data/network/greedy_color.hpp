#ifndef NMTOOLS_TESTING_DATA_NETWORK_GREEDY_COLOR_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_GREEDY_COLOR_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

// Greedy graph coloring with the DSATUR strategy (networkx
// greedy_color(G, strategy="DSATUR")). Expectations are colors indexed by node:
// every node gets the smallest non-negative integer unused by its already
// colored neighbors, in DSATUR order (first pick highest degree, then highest
// (saturation, degree), ties resolved by the lowest node index). Because of
// first fit the used colors are always {0 .. max}, so the frame size is
// max(color) + 1. A self loop never constrains a node's own color but counts
// twice in degree, which changes tie-breaks. Directed input is rejected with
// meta::Nothing at runtime and folds to a fail type when constant, instead of
// being silently mis-colored the way networkx does; see case12.
NMTOOLS_TESTING_DECLARE_CASE(network, greedy_color)
{
    using nmtools_array;
    using nmtools_tuple;

    using namespace literals;

    // path 0-1-2-3 ; nodes 1 and 2 tie on degree, nodes 0 and 3 on saturation
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto colors = nmtools_array{1, 0, 1, 0};
    }

    // triangle ; needs 3 colors
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{0_ct, 1_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto colors = nmtools_array{0, 1, 2};
    }

    // no edges ; every node gets color 0
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto colors = nmtools_array{0, 0, 0, 0};
    }

    // K4 ; needs 4 colors
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 3_ct},
            nmtools_tuple{0_ct, 2_ct, 3_ct},
            nmtools_tuple{0_ct, 1_ct, 3_ct},
            nmtools_tuple{0_ct, 1_ct, 2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto colors = nmtools_array{0, 1, 2, 3};
    }

    // star ; the center is colored first and forces color 1 on all leaves
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct, 3_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto colors = nmtools_array{0, 1, 1, 1};
    }

    // self loop raises node 0's degree to 3, so it is picked first
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto colors = nmtools_array{0, 1};
    }

    // self loops do not force distinct colors on different nodes
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto colors = nmtools_array{0, 0};
    }

    // odd cycle C5 ; needs 3 colors
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 4_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{1_ct, 3_ct},
            nmtools_tuple{2_ct, 4_ct},
            nmtools_tuple{3_ct, 0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto colors = nmtools_array{0, 1, 0, 1, 2};
    }

    // bipartite graph where DSATUR uses 2 colors and a static degree order 3
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{10_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{4_ct, 6_ct, 8_ct, 9_ct},
            nmtools_tuple{8_ct},
            nmtools_tuple{2_ct, 7_ct},
            nmtools_tuple{1_ct, 7_ct, 10_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{4_ct, 5_ct, 8_ct},
            nmtools_tuple{2_ct, 3_ct, 7_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct, 5_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto colors = nmtools_array{1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0};
    }

    // two disconnected edges ; every tie resolves to the lowest index
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{2_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto colors = nmtools_array{0, 1, 0, 1};
    }

    // empty graph ; no colors at all
    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline nmtools_array<int,0> colors {};
    }

    // directed cycle ; networkx would return {0:0, 1:1, 2:2} from successor
    // rows, which is not a coloring of any meaningful graph. Only the runtime
    // path is pinned here, the constant rejection is a static_assert in the
    // test source because a fail type cannot be compared as a value.
    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto colors = meta::Nothing;
    }

    // node 5 has degree 3 but saturation 0 while nodes 0, 3 and 4 already saw
    // a color ; priority is the (saturation, degree) tuple, so degree alone
    // must not let node 5 overtake them (found by fuzzing)
    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{0_ct, 5_ct},
            nmtools_tuple{0_ct, 3_ct, 4_ct},
            nmtools_tuple{2_ct, 5_ct},
            nmtools_tuple{2_ct, 5_ct},
            nmtools_tuple{1_ct, 3_ct, 4_ct}
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto colors = nmtools_array{1, 0, 0, 2, 2, 1};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_GREEDY_COLOR_HPP
