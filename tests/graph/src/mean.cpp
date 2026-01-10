#include "nmtools/network/digraph.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using namespace nm::literals;
using Node = fn::Node<>;
using Kind = fn::Kind;
using Type = fn::Type;
using Layout = fn::Layout;

using nmtools_array, nmtools_tuple, nmtools::unwrap, nmtools::None;

TEST_CASE("get_computational_graph(mean)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();

    auto input = nm::random(array{2,3,2},nm::float32,gen);
    auto axis  = 1;
    auto res   = view::mean(input,axis);

    auto graph = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
    NMTOOLS_ASSERT_EQUAL( nm::meta::is_constant_adjacency_list_v<decltype(unwrap(graph).adjacency_list)>, true );


    constexpr auto graph_v = nm::meta::to_value_v<decltype(unwrap(graph))>;
    auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz_v );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph_v), true );
}

TEST_CASE("mean(case1)" * doctest::test_suite("computational_graph"))
{
    constexpr auto adjacency_list = nmtools_tuple{
        nmtools_tuple{2_ct},
        nmtools_tuple{3_ct},
        nmtools_tuple{4_ct},
        nmtools_tuple{5_ct},
        nmtools_tuple{5_ct},
        nmtools_tuple{},
    };
    constexpr auto node_ids = nmtools_tuple{0_ct,101_ct,102_ct,103_ct,104_ct,105_ct};
    constexpr auto node_attributes = nmtools_array{
        Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
        Node::buffer(None,Type::Float32),
        Node::compute(Kind::REDUCE,array{2,2},Type::Float32),
        Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
        Node::compute(Kind::INDEXING,array{2,2},Type::Float32),
        Node::compute(Kind::BINARY_UFUNC,array{2,2},Type::Float32),
    };

    constexpr auto graph = nk::digraph(adjacency_list,node_ids,node_attributes);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
}