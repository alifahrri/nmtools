#ifndef NMTOOLS_TESTING_DATA_TRANSFORM_BINARY_HPP
#define NMTOOLS_TESTING_DATA_TRANSFORM_BINARY_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/network_cast.hpp"
#include "nmtools/core/node.hpp"

NMTOOLS_TESTING_DECLARE_CASE(functional, transform_binary_fusion)
{
    using namespace literals;
    using Node = nmtools::functional::Node<>;
    using Kind = nmtools::functional::Kind;
    using Type = nmtools::functional::Type;
    using Layout = nmtools::functional::Layout;
    using Combinator = nmtools::functional::Combinator;

    using nmtools_array;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{3},
            nmtools_array{3},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,102_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::REDUCE,array{2,2},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{3},
            nmtools_array{3},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,102_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::REDUCE,array{2,2},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
        };

        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::REDUCE,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            ,
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
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

        constexpr inline auto n_repeats = -1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{2},
            nmtools_array{2},
            nmtools_array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,101_ct,105_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
            Node::buffer(None,Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::REDUCE,array{2,2},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            ,
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // add
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{4_ct},
            nmtools_tuple{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1_ct,1002_ct,1003_ct,1004_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{-1,-1},Type::Float32,Layout::RowMajor),
            Node::buffer(array{-1},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::INDEXING,array{-1,-1},Type::Float32),
            Node::compute(Kind::INDEXING,array{-1,-1},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{-1,-1},Type::Float32),
        };

        constexpr inline auto n_repeats = -1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            array{2},
            array{2},
            array<int,0>{},
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1_ct,1004_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{-1,-1},Type::Float32,Layout::RowMajor),
            Node::buffer(array{-1},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::BINARY_UFUNC,array{-1,-1},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{-1,-1},Type::Float32)
            * Node::combinator(Combinator::SWAP)
            * Node::compute(Kind::INDEXING,array{-1,-1},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3a)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case3a)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1,2},
            nmtools_array{2},
            nmtools_array{3},
            nmtools_array{4,5},
            nmtools_array{6},
            nmtools_array{7},
            nmtools_array{7},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1001_ct,4004_ct,5005_ct,6006_ct,7007_ct,8008_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b)
    {
        // softmax
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_tuple{1_ct,2_ct},
            nmtools_tuple{2_ct},
            nmtools_tuple{3_ct},
            nmtools_tuple{4_ct,5_ct},
            nmtools_tuple{6_ct},
            nmtools_tuple{7_ct},
            nmtools_tuple{7_ct},
            nmtools_tuple{}
        };
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
            Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,1001_ct,4004_ct,5005_ct,6006_ct,7007_ct,8008_ct,9009_ct};

        constexpr inline auto n_repeats = 2;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b)
    {
        constexpr inline auto adjacency_list = nmtools_tuple{
            nmtools_array{1},
            nmtools_array{2},
            nmtools_array{3,4},
            nmtools_array{4},
            nmtools_array<int,0>{}
        };
        constexpr inline auto node_ids = nmtools_tuple{0_ct,4004_ct,5005_ct,6006_ct,9009_ct};
        constexpr inline auto node_attributes = nmtools_array{
            Node::buffer(array{3,4},Type::Float32,Layout::RowMajor),
            Node::combinator(Combinator::DUP)
            | Node::compute(Kind::REDUCE,array{3,1},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::UNARY_UFUNC,array{3,4},Type::Float32),
            Node::compute(Kind::REDUCE,array{3,1},Type::Float32),
            Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::INDEXING,array{3,4},Type::Float32)
            | Node::combinator(Combinator::SWAP)
            | Node::compute(Kind::BINARY_UFUNC,array{3,4},Type::Float32),
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3c)
    {
        // softmax (fused unary)
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

        constexpr inline auto n_repeats = 1;

        NMTOOLS_CAST_NETWORK(adjacency_list)
        NMTOOLS_CONSTEXPR_CAST_NETWORK(adjacency_list)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3c)
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

#endif // NMTOOLS_TESTING_DATA_TRANSFORM_BINARY_HPP