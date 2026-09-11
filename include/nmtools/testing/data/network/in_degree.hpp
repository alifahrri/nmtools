#ifndef NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, in_degree)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto degrees = array{0, 1, 1, 1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto degrees = array{0, 0, 2, 1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
            nmtools_tuple{3_ct},
            nmtools_tuple{},
            nmtools_tuple{},
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto degrees = array{0, 1, 0, 1, 0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{0_ct},
            nmtools_tuple{1_ct},
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto degrees = array{1, 2, 1, 0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct,2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{0_ct,1_ct},
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto degrees = array{1, 2, 1, 2, 1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline auto list = nmtools_tuple{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline array<int,0> degrees {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto list = nmtools_tuple<nmtools_tuple<>>{};
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto degrees = array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{0_ct, 1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        constexpr inline auto degrees = array{1, 1, 1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{},
            nmtools_tuple{}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline auto degrees = array{0, 0, 0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline auto list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct},
            nmtools_tuple{0_ct, 2_ct},
            nmtools_tuple{0_ct, 1_ct}
        };
        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline auto degrees = array{2, 2, 2};
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_IN_DEGREE_HPP
