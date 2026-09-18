#ifndef NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, filter_node_arity)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{};
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto result_nodes = array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result_nodes = array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto result_nodes = array{1, 2, 3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result_nodes = array{2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto result_nodes = array{0, 1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto result_nodes = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto result_nodes = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 1;
        constexpr inline auto arity_ct = 1_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto result_nodes = array{3, 5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct, 3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        constexpr inline auto result_nodes = array{2, 4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{6_ct},
            nmtools_tuple{},
            nmtools_tuple{6_ct}
        };
        constexpr inline int arity = 0;
        constexpr inline auto arity_ct = 0_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        constexpr inline auto result_nodes = array{0, 2, 4, 5, 7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{6_ct},
            nmtools_tuple{},
            nmtools_tuple{6_ct}
        };
        constexpr inline int arity = 2;
        constexpr inline auto arity_ct = 2_ct;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline auto result_nodes = array{6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{}
        };
        constexpr inline int arity = -1;
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline nmtools_array<int,0> result_nodes {};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_ARITY_HPP
