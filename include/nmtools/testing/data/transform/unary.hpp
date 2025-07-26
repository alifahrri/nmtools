#ifndef NMTOOLS_TESTING_DATA_TRANSFORM_UNARY_HPP
#define NMTOOLS_TESTING_DATA_TRANSFORM_UNARY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"
#include "nmtools/core/node.hpp"

NMTOOLS_TESTING_DECLARE_CASE(functional, transform_unary_fusion)
{
    using namespace literals;
    using Node = nmtools::functional::Node<>;
    using Kind = nmtools::functional::Kind;
    using Type = nmtools::functional::Type;
    using Layout = nmtools::functional::Layout;

    using nmtools_array;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        // pad
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{1_ct,2_ct,3_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::INDEXING,array{3,8,11},Type::Float32),
        };
        constexpr inline auto n_repeats = -1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{1_ct,2_ct,3_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::INDEXING,array{3,8,11},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // broadcast_to
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{1_ct,100_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
        };
        constexpr inline auto n_repeats = -1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{1_ct,100_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // max_pool2d
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1_ct,200_ct,300_ct,400_ct,500_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{1,1,7,7},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::INDEXING,array{1,1,7,7},Type::Float32),
            Node::compute(Kind::INDEXING,array{1,1,5,5,3,3},Type::Float32),
            Node::compute(Kind::INDEXING,array{1,1,3,3,3,3},Type::Float32),
            Node::compute(Kind::REDUCE,array{1,1,3,3},Type::Float32),
        };
        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array{3},
            nmtools_array{4},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1_ct,300_ct,400_ct,500_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{1,1,7,7},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::INDEXING,array{1,1,5,5,3,3},Type::Float32) * Node::compute(Kind::INDEXING,array{1,1,7,7},Type::Float32),
            Node::compute(Kind::INDEXING,array{1,1,3,3,3,3},Type::Float32),
            Node::compute(Kind::REDUCE,array{1,1,3,3},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // mean
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,102_ct,103_ct,104_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::REDUCE,array{2,2},Type::Float32),
            Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
            Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32),
        };

        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            array{2},
            array{3},
            array{4},
            array{4},
            array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,103_ct,104_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::compute(Kind::REDUCE,array{2,2},Type::Float32),
            Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        // trace
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{1_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,100_ct,200_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
            Node::compute(Kind::REDUCE,array{2},Type::Float32),
        };

        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,200_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::REDUCE,array{2},Type::Float32)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // softmax
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{1_ct,2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{6_ct,7_ct},
            nmtools_tuple{8_ct},
            nmtools_tuple{9_ct},
            nmtools_tuple{9_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1001_ct,2002_ct,3003_ct,4004_ct,5005_ct,6006_ct,7007_ct,8008_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };

        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{3},
            nmtools_array{3},
            nmtools_array{4},
            nmtools_array{5,6},
            nmtools_array{7},
            nmtools_array{8},
            nmtools_array{8},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,2002_ct,3003_ct,4004_ct,5005_ct,6006_ct,7007_ct,8008_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            * Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6b)
    {
        // softmax
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{1_ct,2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{5_ct},
            nmtools_tuple{6_ct,7_ct},
            nmtools_tuple{8_ct},
            nmtools_tuple{9_ct},
            nmtools_tuple{9_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1001_ct,2002_ct,3003_ct,4004_ct,5005_ct,6006_ct,7007_ct,8008_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };

        constexpr inline auto n_repeats = -1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6b)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{3},
            nmtools_array{3},
            nmtools_array{4,5},
            nmtools_array{6},
            nmtools_array{6},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,2002_ct,3003_ct,5005_ct,7007_ct,8008_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            * Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32)
            * Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            * Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_TRANSFORM_UNARY_HPP