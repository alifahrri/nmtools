#ifndef NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, add_edge)
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
        constexpr inline int u = 0;
        constexpr inline int v = 2;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 2_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline int u = 2;
        constexpr inline int v = 0;
        
        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 0;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;

        constexpr inline auto multi = true;
        constexpr inline auto multi_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1,1},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 1;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 1_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{1}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline int u = 2;
        constexpr inline int v = 1;

        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 1_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{1}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 2;
        constexpr inline int v = 0;
        
        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 0_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 0;
        constexpr inline int v = 2;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 2_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 2},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 2;
        constexpr inline int v = 3;

        constexpr inline auto u_ct = 2_ct;
        constexpr inline auto v_ct = 3_ct;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{3},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{}
        };
        constexpr inline int u = 0;
        constexpr inline int v = 1;
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 1},
            nmtools_array<int,0>{}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<meta::ct<0>>>{};
        constexpr inline int u = 0;
        constexpr inline int v = 0;
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 0_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{0, 0}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        constexpr inline int u = 0;
        constexpr inline int v = 1;
        constexpr inline bool multi = true;

        constexpr inline auto u_ct = 0_ct;
        constexpr inline auto v_ct = 1_ct;
        constexpr inline auto multi_ct = True;

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        constexpr inline auto result = nmtools_tuple{
            nmtools_array{1, 2, 1},
            nmtools_array<int,0>{},
            nmtools_array<int,0>{}
        };
    }
} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_ADD_EDGE_HPP
