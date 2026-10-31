#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/gvn.hpp"
#include "nmtools/core/transform/cse.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
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

// gvn and cse currently operate on runtime graphs (see tests/runtime);
// these cases feed them compile-time captured graphs materialized through
// to_value_v, which is the same network::digraph_t but built from
// constexpr evaluated captures

TEST_CASE("gvn(case1)" * doctest::test_suite("transform"))
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

    auto id_values = fn::gvn(graph_v);

    auto keys = graph_v.nodes();
    auto n = nm_size_t(nm::len(keys));

    for (nm_size_t i=0; i<n; i++) {
        auto id = nm::at(keys,i);
        CHECK( id_values.count(id) > 0 );
        CHECK( id_values.at(id) != 0 );
    }

    // every node of this graph is structurally unique,
    // so all gvn hashes must be distinct
    for (nm_size_t i=0; i<n; i++) {
        for (nm_size_t j=i+1; j<n; j++) {
            CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
        }
    }

    // deterministic across invocations
    auto again = fn::gvn(graph_v);
    for (nm_size_t i=0; i<n; i++) {
        auto id = nm::at(keys,i);
        CHECK( id_values.at(id) == again.at(id) );
    }
}

TEST_CASE("gvn(case2)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs,rhs);

    auto graph = fn::get_computational_tree(res);
    {
        constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;

        auto id_values = fn::gvn(graph_v);

        auto keys = graph_v.nodes();
        auto n = nm_size_t(nm::len(keys));

        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.count(id) > 0 );
            CHECK( id_values.at(id) != 0 );
        }

        // every node of this graph is structurally unique,
        // so all gvn hashes must be distinct
        for (nm_size_t i=0; i<n; i++) {
            for (nm_size_t j=i+1; j<n; j++) {
                CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
            }
        }

        // deterministic across invocations
        auto again = fn::gvn(graph_v);
        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.at(id) == again.at(id) );
        }
    }
    {
        auto id_values = fn::gvn(unwrap(graph));

        const auto keys = unwrap(graph).nodes();
        auto n = nm_size_t(nm::len(keys));

        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.count(id) > 0 );
            CHECK( id_values.at(id) != 0 );
        }

        // every node of this graph is structurally unique,
        // so all gvn hashes must be distinct
        for (nm_size_t i=0; i<n; i++) {
            for (nm_size_t j=i+1; j<n; j++) {
                CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
            }
        }

        // deterministic across invocations
        auto again = fn::gvn(unwrap(graph));
        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.at(id) == again.at(id) );
        }
    }
}

TEST_CASE("gvn(case3)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto [a,b] = view::aliased(lhs,rhs);

    auto res = view::add(a,b);

    auto graph = fn::get_computational_tree(res);
    {
        auto id_values = fn::gvn(unwrap(graph));

        CHECK( id_values.size() == 5 );
        CHECK_MESSAGE( true, utils::to_string(unwrap(graph),utils::Graphviz) );

        const auto keys = unwrap(graph).nodes();
        auto n = nm_size_t(nm::len(keys));

        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.count(id) > 0 );
            CHECK( id_values.at(id) != 0 );
        }

        // every node of this graph is structurally unique,
        // so all gvn hashes must be distinct
        for (nm_size_t i=0; i<n; i++) {
            for (nm_size_t j=i+1; j<n; j++) {
                CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
            }
        }

        // deterministic across invocations
        auto again = fn::gvn(unwrap(graph));
        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.at(id) == again.at(id) );
        }
    }
}

TEST_CASE("gvn(case4)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};

    auto inp = nm::random(lhs_shape,dtype,gen);
    auto a   = view::aliased(inp);
    auto res = view::add(a,a);

    auto graph = fn::get_computational_tree(res);
    {
        auto id_values = fn::gvn(unwrap(graph));

        CHECK( id_values.size() == 5 );
        CHECK_MESSAGE( true, utils::to_string(unwrap(graph),utils::Graphviz) );

        CHECK( id_values.at(2) == id_values.at(4) );
        CHECK( id_values.at(3) == id_values.at(1) );
        CHECK( id_values.at(0) != id_values.at(1) );
    }
}

TEST_CASE("cse(add)" * doctest::test_suite("transform"))
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
TEST_CASE("cse(add(cos,cos))" * doctest::test_suite("transform"))
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

// aliased operands carry a compile-time id, which must participate in
// the buffer hash: two aliased nodes with distinct ids are distinct
// buffers and must not merge, while all aliases with the same id must
// merge. The five-node add tree refers to the buffer nodes by node ids
// 2 and 4 (0: add, 1/3: broadcast_to wrappers, 2/4: buffers).
TEST_CASE("gvn(aliased inputs)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = tuple{3_ct,4_ct};

    auto lhs = nm::random(a_shape,dtype,gen);
    auto rhs = nm::random(a_shape,dtype,gen);

    {
        // distinct ids over distinct arrays: the two buffers must not
        // merge (node 2 wraps the lhs buffer, node 4 the rhs buffer),
        // transitively their broadcast wrappers (1 and 3) are distinct
        auto aliased_lhs = view::alias(lhs, 0_ct);
        auto aliased_rhs = view::alias(rhs, 1_ct);

        auto res  = view::add(aliased_lhs,aliased_rhs);

        constexpr auto tree_v = nm::to_value_v<decltype(unwrap(fn::get_computational_tree(res)))>;

        auto id_values = fn::gvn(tree_v);

        auto keys = tree_v.nodes();
        auto n = nm_size_t(nm::len(keys));

        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.count(id) > 0 );
        }

        // every node of this graph must be structurally unique, so all
        // gvn hashes must be distinct
        for (nm_size_t i=0; i<n; i++) {
            for (nm_size_t j=i+1; j<n; j++) {
                CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
            }
        }

        // cse must keep every node: no duplicates in this graph
        auto subgraph = fn::cse(tree_v);
        CHECK( nm_size_t(nm::len(unwrap(subgraph).nodes())) == n );
    }
    {
        // the same id means BOTH operands refer to the same buffer
        // (2 and 4): they must merge, cse must collapse the tree so a
        // single buffer feeds both broadcast nodes
        auto aliased_0 = view::alias(lhs, 0_ct);
        auto aliased_1 = view::alias(rhs, 0_ct);

        auto res  = view::add(aliased_0,aliased_1);

        constexpr auto tree_v = nm::to_value_v<decltype(unwrap(fn::get_computational_tree(res)))>;

        auto id_values = fn::gvn(tree_v);

        CHECK( id_values.at((nm_size_t)2) == id_values.at((nm_size_t)4) );

        auto subgraph = fn::cse(tree_v);
        CHECK( nm_size_t(nm::len(unwrap(subgraph).nodes())) < 5 );
    }
}
