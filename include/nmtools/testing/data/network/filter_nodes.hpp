#ifndef NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_HPP
#define NMTOOLS_TESTING_DATA_NETWORK_FILTER_NODES_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/utility.hpp"

NMTOOLS_TESTING_DECLARE_CASE(network, filter_nodes)
{
    template <nm_size_t I>
    struct data
    {
        using value_t = meta::ct<I>;
        using tag_t = nmtools_string;

        tag_t tag;
        value_t value = {};
    };

    using nmtools_array;
    using nmtools_list;
    using nmtools_tuple;

    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int node_attributes[4] = {100, 200, 300, 400};
        inline int src_node_ids[4] = {10, 20, 30, 40};
        inline int dst_node_ids[2] = {20, 40};

        inline auto node_attributes_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};
        inline auto src_node_ids_ct = nmtools_tuple{10_ct,20_ct,30_ct,40_ct};
        inline auto dst_node_ids_ct = nmtools_tuple{20_ct,40_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int expected[2] = {200, 400};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int node_attributes[4] = {100, 200, 300, 400};
        inline int src_node_ids[4] = {10, 20, 30, 40};
        inline int dst_node_ids[2] = {40, 10};

        inline auto node_attributes_ct = nmtools_tuple{100_ct,200_ct,300_ct,400_ct};
        inline auto src_node_ids_ct = nmtools_tuple{10_ct,20_ct,30_ct,40_ct};
        inline auto dst_node_ids_ct = nmtools_tuple{40_ct,10_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int expected[2] = {400, 100};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline nmtools_string node_attributes[3] = {"apple", "banana", "cherry"};
        inline auto node_attributes_a = nmtools_array<nmtools_string,3>{"apple", "banana", "cherry"};
        inline auto node_attributes_v = nmtools_list<nmtools_string>{"apple", "banana", "cherry"};
        inline int src_node_ids[3] = {5, 8, 2};
        inline int dst_node_ids[2] = {2, 5};

        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto expected = nmtools_array<nmtools_string,2>{"cherry", "apple"};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int node_attributes[3] = {1, 2, 3};
        inline int src_node_ids[3] = {10, 20, 30};
        inline int dst_node_ids[2] = {99, 98};

        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline auto expected = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int node_attributes[3] = {1, 2, 3};
        inline int src_node_ids[3] = {10, 20, 30};
        inline nmtools_array<int,0> dst_node_ids {};

        NMTOOLS_CAST_INDEX_ARRAYS(node_attributes)
        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline nmtools_array<int,0> expected {};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline nmtools_string node_attributes[4] = {"first_A", "B", "C", "second_A"};
        inline auto node_attributes_a = nmtools_array<nmtools_string,4>{"first_A", "B", "C", "second_A"};
        inline auto node_attributes_v = nmtools_list<nmtools_string>{"first_A", "B", "C", "second_A"};
        inline int src_node_ids[4] = {1, 2, 3, 1};
        inline int dst_node_ids[1] = {1};

        NMTOOLS_CAST_INDEX_ARRAYS(src_node_ids)
        NMTOOLS_CAST_INDEX_ARRAYS(dst_node_ids)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline nmtools_string expected[1] = {"first_A"};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline auto node_attributes = nmtools_tuple{
            data<100>{"one hundred"},
            data<200>{"two hundred"},
            data<300>{"three hundred"},
            data<400>{"four hundred"},
        };

        inline auto src_node_ids_ct = nmtools_tuple{10_ct,20_ct,30_ct,40_ct};
        inline auto dst_node_ids_ct = nmtools_tuple{40_ct,10_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline auto expected = nmtools_tuple{
            data<400>{"four hundred"},
            data<100>{"one hundred"},
        };
    }

} // NMTOOLS_TESTING_DECLARE_CASE

#endif // NMTOOLS_TESTING_DATA_ARRAY_FILTER_NODES_HPP
