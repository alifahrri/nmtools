#include "nmtools/network/digraph.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/pad.hpp"
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

TEST_CASE("get_computational_graph(pad)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    int pad_width[3][2] = {
        {0,1},
        {2,3},
        {4,5},
    };

    auto res = view::pad(a,pad_width);

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

TEST_CASE("pad(case1)" * doctest::test_suite("computational_graph"))
{
    constexpr auto adjacency_list = nmtools_tuple{
        nmtools_tuple{2_ct},
        nmtools_tuple{2_ct},
        nmtools_tuple{},
    };
    constexpr auto node_ids = nmtools_tuple{1_ct,2_ct,3_ct};
    constexpr auto node_attributes = nmtools_array{
        Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
        Node::buffer(nm::None,Type::Float32),
        Node::compute(Kind::INDEXING,array{3,8,11},Type::Float32),
    };
    constexpr auto graph = nk::digraph(adjacency_list,node_ids,node_attributes);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
}

TEST_CASE("pad(case2)" * doctest::test_suite("computational_graph"))
{
    auto adjacency_list = nmtools_tuple{
        array{2},
        array{2},
        array<int,0>{},
    };
    auto node_ids = array{1,2,3};
    auto node_attributes = nmtools_array{
        Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
        Node::buffer(nm::None,Type::Float32),
        Node::compute(Kind::INDEXING,array{3,8,11},Type::Float32),
    };
    auto graph = nk::digraph(adjacency_list,node_ids,node_attributes);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    // TODO: fix compile error
    // NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
}

TEST_CASE("pad(case3)" * doctest::test_suite("computational_graph"))
{
    using adjacency_list_t = nmtools_array<nmtools_static_vector<nm_index_t,2>,3>;
    auto adjacency_list = adjacency_list_t{};

    adjacency_list[0].resize(1);
    adjacency_list[1].resize(1);

    adjacency_list[0][0] = 2;
    adjacency_list[1][0] = 2;

    auto node_ids = array{1,2,3};
    auto node_attributes = nmtools_array{
        Node::buffer(array{2,3,2},Type::Float32,Layout::RowMajor),
        Node::buffer(nm::None,Type::Float32),
        Node::compute(Kind::INDEXING,array{3,8,11},Type::Float32),
    };
    auto graph = nk::digraph(adjacency_list,node_ids,node_attributes);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
}