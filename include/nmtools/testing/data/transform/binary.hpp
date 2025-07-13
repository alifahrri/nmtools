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
}

#endif // NMTOOLS_TESTING_DATA_TRANSFORM_BINARY_HPP