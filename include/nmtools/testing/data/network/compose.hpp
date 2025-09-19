#ifndef NMTOOLS_TESTING_DATA_NETWORK_COMPOSE_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_COMPOSE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, compose)
{
    using nmtools_array;
    using nmtools_tuple;
    using namespace nmtools::literals;

    //----------------------------------------------------
    // Test Case 1: No Overlapping Nodes (Disjoint Union)
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // Graph G: 10 -> 20
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{10_ct, 20_ct};

        // Graph H: 30 -> 40
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto h_map_id = nmtools_tuple{30_ct, 40_ct};

        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // Expected graph has nodes {10, 20, 30, 40}
        // New map (sorted): [10, 20, 30, 40] -> indices [0, 1, 2, 3]
        // Edge 10->20 becomes 0->1. Edge 30->40 becomes 2->3.
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
            nmtools_array{3},
            nmtools_array<int,0>{}
        };
        constexpr inline auto result_map_id = nmtools_array{10, 20, 30, 40};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

    //----------------------------------------------------
    // Test Case 2: One Overlapping Node
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // Graph G: 10 -> 20
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{10_ct, 20_ct};

        // Graph H: 20 -> 30
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto h_map_id = nmtools_tuple{20_ct, 30_ct};

        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // Expected graph has nodes {10, 20, 30}
        // New map (sorted): [10, 20, 30] -> indices [0, 1, 2]
        // Edge 10->20 becomes 0->1. Edge 20->30 becomes 1->2.
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
        constexpr inline auto result_map_id = nmtools_array{10, 20, 30};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

    //----------------------------------------------------
    // Test Case 3: Overlapping Nodes and Edges
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // Graph G: 10 -> 20
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{10_ct, 20_ct};

        // Graph H: 10 -> 20, 20 -> 30
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{}
        };
        constexpr inline auto h_map_id = nmtools_tuple{10_ct, 20_ct, 30_ct};

        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // Expected graph has nodes {10, 20, 30}
        // New map (sorted): [10, 20, 30] -> indices [0, 1, 2]
        // Edge 10->20 (from G and H) becomes 0->1. Edge 20->30 becomes 1->2.
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{2},
            nmtools_array<int,0>{}
        };
        constexpr inline auto result_map_id = nmtools_array{10, 20, 30};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

    //----------------------------------------------------
    // Test Case 4: Composing with an Empty Graph
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // Graph G: 1 -> 2
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{1_ct, 2_ct};

        // Graph H: Empty
        constexpr inline auto h_list = nmtools_tuple{};
        constexpr inline auto h_map_id = nmtools_array<int,0>{};

        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // Expected result is just Graph G
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{}
        };
        constexpr inline auto result_map_id = nmtools_array{1, 2};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

    //----------------------------------------------------
    // Test Case 5: More Complex Merge
    //----------------------------------------------------
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // Graph G: Nodes {1,2,3}, Edges 1->2, 1->3
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{1_ct, 2_ct, 3_ct};

        // Graph H: Nodes {3,4,5}, Edges 3->4, 4->5
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{}
        };
        constexpr inline auto h_map_id = nmtools_tuple{3_ct, 4_ct, 5_ct};

        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        // Expected graph has nodes {1,2,3,4,5}
        // New map: [1,2,3,4,5] -> indices [0,1,2,3,4]
        // G edge 1->2 becomes 0->1
        // G edge 1->3 becomes 0->2
        // H edge 3->4 becomes 2->3
        // H edge 4->5 becomes 3->4
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1, 2}, // Node 1 (new index 0)
            nmtools_array<int,0>{},        // Node 2 (new index 1)
            nmtools_array{3},      // Node 3 (new index 2)
            nmtools_array{4},      // Node 4 (new index 3)
            nmtools_array<int,0>{}         // Node 5 (new index 4)
        };
        constexpr inline auto result_map_id = nmtools_array{1, 2, 3, 4, 5};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

    template <nm_size_t I>
    struct data
    {
        using value_t = meta::ct<I>;
        using tag_t = nmtools_string;

        tag_t tag;
        value_t value = {};

        auto to_string() const noexcept
        {
            auto str = nmtools_string();

            str += tag;

            return str;
        }
    };

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Graph G: Nodes {1,2,3}, Edges 1->2, 1->3
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{1_ct, 2_ct}, nmtools_tuple{}, nmtools_tuple{}
        };
        constexpr inline auto g_map_id = nmtools_tuple{1_ct, 2_ct, 3_ct};
        inline auto g_attributes = nmtools_tuple{
            data<100>{"one hundred"},
            data<200>{"two hundred"},
            data<300>{"three hundred"},
        };

        // Graph H: Nodes {3,4,5}, Edges 3->4, 4->5
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{1_ct}, nmtools_tuple{2_ct}, nmtools_tuple{}
        };
        constexpr inline auto h_map_id = nmtools_tuple{3_ct, 4_ct, 5_ct};
        inline auto h_attributes = nmtools_tuple{
            data<300>{"three hundred"},
            data<400>{"four hundred"},
            data<500>{"five hundred"},
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expected graph has nodes {1,2,3,4,5}
        // New map: [1,2,3,4,5] -> indices [0,1,2,3,4]
        // G edge 1->2 becomes 0->1
        // G edge 1->3 becomes 0->2
        // H edge 3->4 becomes 2->3
        // H edge 4->5 becomes 3->4
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array{1, 2}, // Node 1 (new index 0)
            nmtools_array<int,0>{},        // Node 2 (new index 1)
            nmtools_array{3},      // Node 3 (new index 2)
            nmtools_array{4},      // Node 4 (new index 3)
            nmtools_array<int,0>{}         // Node 5 (new index 4)
        };
        constexpr inline auto result_map_id = nmtools_array{1, 2, 3, 4, 5};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
        inline auto node_attributes = nmtools_tuple{
            data<100>{"one hundred"},
            data<200>{"two hundred"},
            data<300>{"three hundred"},
            data<400>{"four hundred"},
            data<500>{"five hundred"},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline auto g_list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct},
            nmtools_tuple{0_ct},
        };
        constexpr inline auto g_map_id = nmtools_tuple{195_ct,692_ct,144_ct};
        constexpr inline auto h_list = nmtools_tuple{
            nmtools_tuple{},
            nmtools_tuple{0_ct},
        };
        constexpr inline auto h_map_id = nmtools_tuple{692_ct,0_ct};
        
        NMTOOLS_CAST_NETWORK(g_list)
        NMTOOLS_CAST_NETWORK(h_list)

        NMTOOLS_CONSTEXPR_CAST_NETWORK(g_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(h_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline auto result_list = nmtools_tuple{
            nmtools_array<int,0>{},
            nmtools_array{0},
            nmtools_array{0},
            nmtools_array{1},
        };
        constexpr inline auto result_map_id = nmtools_tuple{195_ct,692_ct,144_ct,0_ct};
        constexpr inline auto expected = nmtools_tuple{result_list, result_map_id};
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_NETWORK_COMPOSE_HPP