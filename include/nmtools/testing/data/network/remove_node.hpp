#ifndef NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, remove_node)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int node_to_remove = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int node_to_remove = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        constexpr inline int node_to_remove = 0;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result = nmtools_tuple{};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{2_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline int node_to_remove = 1;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline int node_to_remove = 2;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }
} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_REMOVE_NODE_HPP
