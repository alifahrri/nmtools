#ifndef NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, out_degree)
{
    using nmtools_array;
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            array{2},
            array{3},
            array{4},
            array{4},
            array<int,0>(),
        };

        constexpr inline auto node_attributes = array{0,10,20,30,40};
        constexpr inline auto node_attributes_ct = nmtools_tuple{0_ct,10_ct,20_ct,30_ct,40_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto degrees = array{1,1,1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline auto list = nmtools_tuple{
            array{2,1},
            array{2},
            array{3,4},
            array{5},
            array{5},
            array<int,0>(),
        };

        constexpr inline auto node_attributes = array{0,10,20,30,40,50};
        constexpr inline auto node_attributes_ct = nmtools_tuple{0_ct,10_ct,20_ct,30_ct,40_ct,50_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto degrees = array{2,1,2,1,1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline auto list = nmtools_tuple{
            array<int,0>(),
        };

        constexpr inline auto node_attributes = array{0};
        constexpr inline auto node_attributes_ct = nmtools_tuple{0_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto degrees = array{0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1},
            array<int,0>(),
            array{0,3},
            array<int,0>(),
        };

        constexpr inline auto node_attributes = array{0,10,20,30};
        constexpr inline auto node_attributes_ct = nmtools_tuple{0_ct,10_ct,20_ct,30_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto degrees = array{1,0,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline auto list = nmtools_tuple{
            array{1,2,3},
            array<int,0>(),
            array{4},
            array{0,5},
            array{5,6},
            array<int,0>(),
            array{6},
        };

        constexpr inline auto node_attributes = array{0,10,20,30,40,50,60};
        constexpr inline auto node_attributes_ct = nmtools_tuple{0_ct,10_ct,20_ct,30_ct,40_ct,50_ct,60_ct};

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto degrees = array{3,0,1,2,2,0,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP
