#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("cse(case1)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs,rhs);

    auto graph = fn::get_computational_graph(res);
    constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;

    auto subgraph = fn::cse(graph_v);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );

    // no duplicates in this graph, so cse must keep every node
    CHECK( nm_size_t(nm::len(subgraph.nodes())) == nm_size_t(nm::len(graph_v.nodes())) );
}

// aliased operand: the tree capture duplicates the shared cos subtree
// (sequential ids), gvn must recognize both copies as equal, and cse
// must merge them back into a single node
TEST_CASE("cse(case2)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = array{3,4};
    auto a = nm::random(a_shape,dtype,gen);

    auto t   = view::cos(a);
    auto res = view::add(t,t);

    auto tree = fn::get_computational_tree(res);
    constexpr auto tree_v = nm::to_value_v<decltype(unwrap(tree))>;

    auto src_graphviz = utils::to_string(tree_v,utils::Graphviz);
    CHECK_MESSAGE( true, src_graphviz );

    auto id_values = fn::gvn(tree_v);

    auto keys = tree_v.nodes();
    auto n = nm_size_t(nm::len(keys));

    // count distinct hashes; duplicated subtree means fewer hashes than nodes
    nm_size_t distinct = 0;
    for (nm_size_t i=0; i<n; i++) {
        bool seen = false;
        for (nm_size_t j=0; j<i; j++) {
            if (id_values.at(nm::at(keys,j)) == id_values.at(nm::at(keys,i))) {
                seen = true;
                break;
            }
        }
        if (!seen) { distinct++; }
    }
    CHECK( distinct < n );

    auto subgraph = fn::cse(tree_v);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
    CHECK( nm_size_t(nm::len(subgraph.nodes())) < n );
}

TEST_CASE("cse(case3)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = tuple{3_ct,4_ct};
    auto rhs_shape = tuple{4_ct};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs,rhs);

    auto graph = fn::get_computational_graph(res);

    auto subgraph = fn::cse(graph);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(subgraph.adjacency_list)>, true );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );

    // no duplicates in this graph, so cse must keep every node
    CHECK( nm_size_t(nm::len(subgraph.nodes())) == nm_size_t(nm::len(graph.nodes())) );
}

TEST_CASE("cse(case4)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};
    auto a = nm::random(a_shape,dtype,gen);

    auto t   = view::cos(a);
    auto res = view::add(t,t);

    auto tree = fn::get_computational_tree(res);

    auto subgraph = fn::cse(tree);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(subgraph.adjacency_list)>, true );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

// softmax with compile-time shape, runtime axis, value based
TEST_CASE("cse(case7)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};
    auto a = nm::random(a_shape,dtype,gen);

    nm_index_t axis = 1;
    auto res = view::softmax(a,axis);

    auto tree = fn::get_computational_tree(res);
    constexpr auto tree_v = nm::to_value_v<decltype(unwrap(tree))>;

    auto src_graphviz = utils::to_string(tree_v,utils::Graphviz);
    CHECK_MESSAGE( true, src_graphviz );

    auto subgraph = fn::cse(tree_v);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

// softmax with compile-time shape, runtime axis, static type based
TEST_CASE("cse(case8)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};
    auto a = nm::random(a_shape,dtype,gen);

    nm_index_t axis = 1;
    auto res = view::softmax(a,axis);

    // NOTE: softmax with runtime axis produces maybe views: static shape
    // resolution of the runtime-axis reduce fails, hence broadcast_arrays
    // (hence subtract/exp/reduce_add/divide) wrap in maybe, so the tree is
    // maybe-wrapped too (but has a value).
    auto tree = fn::get_computational_tree(res);

    auto subgraph = fn::cse(unwrap(tree));

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(subgraph.adjacency_list)>, true );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}
TEST_CASE("cse(case5)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};
    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::softmax(a,1_ct);

    auto tree = fn::get_computational_tree(res);
    constexpr auto tree_v = nm::to_value_v<decltype(unwrap(tree))>;

    auto src_graphviz = utils::to_string(tree_v,utils::Graphviz);
    CHECK_MESSAGE( true, src_graphviz );

    auto subgraph = fn::cse(tree_v);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

// softmax with compile-time shape & axis, static type based
TEST_CASE("cse(case6)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};
    auto a = nm::random(a_shape,dtype,gen);

    auto res = view::softmax(a,1_ct);

    auto tree = fn::get_computational_tree(res);

    auto subgraph = fn::cse(tree);

    auto graphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );

    NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(subgraph.adjacency_list)>, true );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}