#ifndef NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, out_degree)
{
    using nmtools_array;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline auto list = nmtools_tuple{
            array{2},
            array{3},
            array{4},
            array{4},
            array<int,0>(),
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
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

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto degrees = array{2,1,2,1,1,0};
    }
    

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph: Single node 0 with no outgoing edges
        constexpr inline auto list = nmtools_tuple{
            array<int,0>(),    // Node 0 neighbors
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto degrees = array{0}; // Out-degree for node 0
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph: 0->1, 1->{}, 2->{0,3}, 3->{}
        constexpr inline auto list = nmtools_tuple{
            array{1},          // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors (disconnected)
            array{0,3},        // Node 2 neighbors
            array<int,0>(),    // Node 3 neighbors (disconnected)
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto degrees = array{1,0,2,0}; // Out-degrees for nodes 0, 1, 2, 3
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph: Larger graph with varied degrees
        // 0->{1,2,3}, 1->{}, 2->{4}, 3->{0,5}, 4->{5,6}, 5->{}, 6->{6} (self-loop)
        constexpr inline auto list = nmtools_tuple{
            array{1,2,3},      // Node 0 neighbors
            array<int,0>(),    // Node 1 neighbors
            array{4},          // Node 2 neighbors
            array{0,5},        // Node 3 neighbors
            array{5,6},        // Node 4 neighbors
            array<int,0>(),    // Node 5 neighbors
            array{6},          // Node 6 neighbors (points to itself)
        };

        NMTOOLS_CAST_NETWORK(list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Out-degree is just the count of neighbors listed
        constexpr inline auto degrees = array{3,0,1,2,2,0,1}; // Out-degrees for nodes 0, 1, 2, 3, 4, 5, 6
    }
}

#endif // NMTOOLS_TESTING_DATA_NETWORK_OUT_DEGREE_HPP