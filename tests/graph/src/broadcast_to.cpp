#include "nmtools/network/digraph.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/broadcast_to.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nm::literals;
using Node = fn::Node<>;
using Kind = fn::Kind;
using Type = fn::Type;
using Layout = fn::Layout;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("get_computational_graph(broadcast_to)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto inp_shape = array{4};
    auto dst_shape = array{3,4};

    auto input = nm::random(inp_shape,dtype,gen);

    auto res = view::broadcast_to(input,dst_shape);

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

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("computational_graph"))
{
    constexpr auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{},
    };
    constexpr auto node_ids = nmtools_tuple{1_ct,100_ct};
    constexpr auto node_attributes = nmtools_array{
        Node::buffer(array{4},Type::Float32,Layout::RowMajor),
        Node::compute(Kind::INDEXING,array{3,4},Type::Float32),
    };

    auto graph = nk::digraph(adjacency_list,node_ids,node_attributes);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
}