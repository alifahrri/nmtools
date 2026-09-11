#ifndef NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, out_edges)
{
    using nmtools_array;
    using nmtools_tuple;

    using edge_t = nmtools_array<int, 2>;

    using namespace literals;

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
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr auto nbunch = 0;
        constexpr auto nbunch_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{1, 2},
            edge_t{2, 0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto edges = nmtools_array<edge_t,1>{
            edge_t{0, 1}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline nmtools_array<edge_t,0> edges {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{1, 2}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{0_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto edges = nmtools_array{
            edge_t{0, 1},
            edge_t{0, 2},
            edge_t{1, 2},
            edge_t{1, 3},
            edge_t{2, 3},
            edge_t{3, 0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto edges = nmtools_array<edge_t,1>{
            edge_t{0,1}
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_OUT_EDGES_HPP
