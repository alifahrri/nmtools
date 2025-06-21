#include "nmtools/network/digraph.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace fn = nm::functional;
namespace meta = nm::meta;
namespace network = nm::network;
namespace utils = nm::utils;

using nmtools_array, nm::unwrap;
using namespace nmtools::literals;

TEST_CASE("expression_tree(reshape1)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto input = unwrap(na::random(src_shape,dtype,gen));

    auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{}
    };
    auto node_ids = nmtools_tuple{0_ct,928_ct};
    auto nodes = nmtools_tuple{&input,fn::reshape[dst_shape]};
    [[maybe_unused]]
    auto digraph = network::digraph(adjacency_list,node_ids,nodes);

    NMTOOLS_ASSERT_EQUAL( digraph.nodes(), node_ids );

    const auto& node_0 = digraph.nodes(0_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_0)>,
        meta::remove_cvref_t<decltype(nm::get<0>(nodes))>> );
    const auto& node_1 = digraph.nodes(928_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_1)>,
        meta::remove_cvref_t<decltype(nm::get<1>(nodes))>> );

    auto out_edges = digraph.out_edges();
    NMTOOLS_ASSERT_EQUAL( nm::len(out_edges), 1 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape2)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{}
    };
    auto node_ids = nmtools_tuple{0_ct,928_ct};
    auto reshape_node = fn::compute_node(functor,nmtools_tuple{0_ct},nm::shape(view));
    auto nodes = nmtools_tuple{&input,reshape_node};
    [[maybe_unused]]
    auto digraph = network::digraph(adjacency_list,node_ids,nodes);

    NMTOOLS_ASSERT_EQUAL( digraph.nodes(), node_ids );

    const auto& node_0 = digraph.nodes(0_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_0)>,
        meta::remove_cvref_t<decltype(nm::get<0>(nodes))>> );
    const auto& node_1 = digraph.nodes(928_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_1)>,
        meta::remove_cvref_t<decltype(nm::get<1>(nodes))>> );

    auto out_edges = digraph.out_edges();
    NMTOOLS_ASSERT_EQUAL( nm::len(out_edges), 1 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape3)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{}
    };
    auto node_ids = nmtools_tuple{0_ct,928_ct};
    auto reshape_node = fn::compute_node(functor,nmtools_tuple{0_ct},nm::shape(view));
    auto buffer_node   = fn::buffer_node(input);
    auto nodes = nmtools_tuple{buffer_node,reshape_node};
    [[maybe_unused]]
    auto digraph = network::digraph(adjacency_list,node_ids,nodes);

    NMTOOLS_ASSERT_EQUAL( digraph.nodes(), node_ids );

    const auto& node_0 = digraph.nodes(0_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_0)>,
        meta::remove_cvref_t<decltype(nm::get<0>(nodes))>> );
    const auto& node_1 = digraph.nodes(928_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_1)>,
        meta::remove_cvref_t<decltype(nm::get<1>(nodes))>> );

    auto out_edges = digraph.out_edges();
    NMTOOLS_ASSERT_EQUAL( nm::len(out_edges), 1 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape4)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{}
    };
    auto node_ids = nmtools_tuple{0_ct,928_ct};
    auto reshape_node = fn::compute_node(unwrap(view));
    auto buffer_node   = fn::buffer_node(input);
    auto nodes = nmtools_tuple{buffer_node,reshape_node};
    [[maybe_unused]]
    auto digraph = network::digraph(adjacency_list,node_ids,nodes);

    NMTOOLS_ASSERT_EQUAL( digraph.nodes(), node_ids );

    const auto& node_0 = digraph.nodes(0_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_0)>,
        meta::remove_cvref_t<decltype(nm::get<0>(nodes))>> );
    const auto& node_1 = digraph.nodes(928_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_1)>,
        meta::remove_cvref_t<decltype(nm::get<1>(nodes))>> );

    auto out_edges = digraph.out_edges();
    NMTOOLS_ASSERT_EQUAL( nm::len(out_edges), 1 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape5)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto adjacency_list = nmtools_tuple{
        nmtools_tuple{1_ct},
        nmtools_tuple{}
    };
    auto node_ids = nmtools_tuple{0_ct,928_ct};
    auto reshape_node = fn::node(unwrap(view));
    auto buffer_node   = fn::node(input);
    auto nodes = nmtools_tuple{buffer_node,reshape_node};
    [[maybe_unused]]
    auto digraph = network::digraph(adjacency_list,node_ids,nodes);

    NMTOOLS_ASSERT_EQUAL( digraph.nodes(), node_ids );

    const auto& node_0 = digraph.nodes(0_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_0)>,
        meta::remove_cvref_t<decltype(nm::get<0>(nodes))>> );
    const auto& node_1 = digraph.nodes(928_ct);
    static_assert( meta::is_same_v<
        meta::remove_cvref_t<decltype(node_1)>,
        meta::remove_cvref_t<decltype(nm::get<1>(nodes))>> );

    auto out_edges = digraph.out_edges();
    NMTOOLS_ASSERT_EQUAL( nm::len(out_edges), 1 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape6)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    [[maybe_unused]]
    auto operands = unwrap(view).operands();
    NMTOOLS_ASSERT_EQUAL( nm::len(operands), 1 );

    using view_type = decltype(unwrap(view));

    constexpr auto operands_ids = decltype(unwrap(view))::operands_ids;
    [[maybe_unused]] auto compute_node = fn::node(view);
    auto node_id = view_type::id_type{};
    auto digraph = network::digraph(
        nmtools_tuple<nmtools_tuple<>>{}
        , nmtools_tuple{node_id}
        , nmtools_tuple{unwrap(compute_node)});
    const auto& operand0 = *nm::at(operands,meta::ct_v<0>);
    [[maybe_unused]] auto buffer_node = fn::node(operand0);
    auto operand0_id = nm::at(operands_ids,meta::ct_v<0>);
    auto m_digraph = digraph
        .add_node(operand0_id,buffer_node)
        .add_edge(operand0_id,node_id)
    ;

    NMTOOLS_ASSERT_EQUAL( m_digraph.has_node(node_id), 1 );
    NMTOOLS_ASSERT_EQUAL( m_digraph.has_node(operand0_id), 1 );

    NMTOOLS_ASSERT_EQUAL( m_digraph.get_index(node_id), 0 );

    [[maybe_unused]]
    auto graphviz = utils::to_string(m_digraph,utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape7)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto m_digraph = fn::get_computational_graph(view);

    auto graphviz = utils::to_string(unwrap(m_digraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}

TEST_CASE("expression_tree(reshape7)" * doctest::test_suite("network::digraph"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto functor = fn::reshape[dst_shape];
    auto input   = unwrap(na::random(src_shape,dtype,gen));
    auto view    = functor(input);

    auto m_digraph = fn::get_computational_graph(view);

    auto graphviz = utils::to_string(unwrap(m_digraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
}