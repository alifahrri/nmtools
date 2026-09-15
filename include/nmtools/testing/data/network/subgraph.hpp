#ifndef NMTOOLS_TESTING_DATA_NETWORK_SUBGRAPH_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_SUBGRAPH_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, subgraph)
{
    using nmtools_array;
    using nmtools_tuple;
    using utl::static_string;
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int nodes[2] = {0, 2};
        constexpr inline auto nodes_ct = nmtools_tuple{0_ct, 2_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three")};

        constexpr inline auto keep_nodes = nmtools_tuple{101_ct,303_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids  = nmtools_tuple{101_ct,303_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("one"),static_string("three")};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int nodes[3] = {1, 2, 3};
        constexpr inline auto nodes_ct = nmtools_tuple{1_ct, 2_ct, 3_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct,404_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three"),static_string("four")};

        constexpr inline auto keep_nodes = nmtools_tuple{202_ct,303_ct,404_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids  = nmtools_tuple{202_ct,303_ct,404_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("two"),static_string("three"),static_string("four")};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int nodes[2] = {0, 1};
        constexpr inline auto nodes_ct = nmtools_tuple{0_ct, 1_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three")};

        constexpr inline auto keep_nodes = nmtools_tuple{101_ct,202_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("one"),static_string("two")};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline int nodes[2] = {0, 2};
        constexpr inline auto nodes_ct = nmtools_tuple{0_ct, 2_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three")};

        constexpr inline auto keep_nodes = nmtools_tuple{101_ct,303_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
        constexpr inline auto node_ids  = nmtools_tuple{101_ct,303_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("one"),static_string("three")};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};

        constexpr inline auto nodes = nmtools_array<int,0>{};
        constexpr inline auto nodes_ct = nmtools_tuple{};

        constexpr inline auto node_ids  = nmtools_tuple{};
        constexpr inline auto node_data = nmtools_array<int,0>{};

        constexpr inline auto keep_nodes = nmtools_tuple{};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result = nmtools_tuple{};
        constexpr inline auto node_ids  = nmtools_tuple{};
        constexpr inline auto node_data = nmtools_tuple{};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 1_ct},
            nmtools_tuple{2_ct, 2_ct},
            nmtools_tuple{}
        };
        constexpr inline int nodes[2] = {0, 2};
        constexpr inline auto nodes_ct = nmtools_tuple{0_ct, 2_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three")};

        constexpr inline auto keep_nodes = nmtools_tuple{101_ct,303_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids  = nmtools_tuple{101_ct,303_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("one"),static_string("three")};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline int nodes[2] = {0, 1};
        constexpr inline auto nodes_ct = nmtools_tuple{0_ct, 1_ct};

        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct,303_ct};
        constexpr inline auto node_data = nmtools_array{static_string("one"),static_string("two"),static_string("three")};

        constexpr inline auto keep_nodes = nmtools_tuple{101_ct,202_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(nodes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids  = nmtools_tuple{101_ct,202_ct};
        constexpr inline auto node_data = nmtools_tuple{static_string("one"),static_string("two")};
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_SUBGRAPH_HPP
