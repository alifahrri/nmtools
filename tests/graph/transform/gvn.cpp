#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/gvn.hpp"
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

TEST_CASE("gvn(case1)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs,rhs);

    auto graph = fn::get_computational_tree(res);
    constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;
    CHECK_MESSAGE( true, utils::to_string(graph_v,utils::Graphviz) );

    auto id_values = fn::gvn(graph_v);

    CHECK( graph_v.nodes(2).attributes_.count("alias") );
    CHECK( graph_v.nodes(4).attributes_.count("alias") );
    CHECK( graph_v.nodes(2).attributes_.at("alias").integer != graph_v.nodes(4).attributes_.at("alias").integer );

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
            CHECK_MESSAGE( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)), i, j );
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

// aliased operands carry a compile-time id, which must participate in
// the buffer hash: two aliased nodes with distinct ids are distinct
// buffers and must not merge, while all aliases with the same id must
// merge. The five-node add tree refers to the buffer nodes by node ids
// 2 and 4 (0: add, 1/3: broadcast_to wrappers, 2/4: buffers).
TEST_CASE("gvn(case5)" * doctest::test_suite("transform"))
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

TEST_CASE("gvn(case6)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto shape  = nmtools_tuple{2_ct,3_ct,2_ct};
    auto lhs    = nm::random(shape,dtype,gen);
    auto rhs    = nm::random(shape,dtype,gen);
    auto [a,b]  = view::aliased(lhs,rhs);
    auto result = view::add(a,b);
    auto tree   = unwrap(fn::get_computational_tree(result));

    {
        auto id_values = fn::gvn(tree);
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_constant_map, decltype(id_values) );

        // everything in this graph is known at compile time,
        // so all values must be constant indices (fully computed
        // at compile time, no runtime slot)
        using id_values_t = decltype(id_values);
        using values_t = id_values_t::values_type;
        constexpr auto N = nm::len_v<values_t>;
        nm::template_for<N>([&](auto i){
            constexpr auto I = decltype(i)::value;
            using value_i = nm::at_t<values_t,I>;
            static_assert( nm::is_constant_index_v<value_i>
                , "expect all gvn values computed at compile time"
            );
        });

        CHECK( id_values.size() == 5 );
        CHECK_MESSAGE( true, utils::to_string(tree,utils::Graphviz) );

        const auto keys = tree.nodes();
        auto n = nm_size_t(nm::len(keys));

        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.count(id) > 0 );
            CHECK( id_values.at(id) != 0 );
        }

        // every node of this graph is structurally unique, so all
        // gvn hashes must be distinct
        for (nm_size_t i=0; i<n; i++) {
            for (nm_size_t j=i+1; j<n; j++) {
                CHECK( id_values.at(nm::at(keys,i)) != id_values.at(nm::at(keys,j)) );
            }
        }

        // deterministic across invocations
        auto again = fn::gvn(tree);
        for (nm_size_t i=0; i<n; i++) {
            auto id = nm::at(keys,i);
            CHECK( id_values.at(id) == again.at(id) );
        }

        // TODO: cse on the CT tree: cse's subgraph selection gathers runtime
        // indices over the CT adjacency, and its internal gvn result (a
        // constant_map) is not iterable yet, so cse runs on the value form.
        // no structurally duplicate node in this graph,
        // so cse must keep every node
        constexpr auto tree_v = nm::to_value_v<decltype(tree)>;
        auto subgraph = fn::cse(tree_v);
        CHECK( nm_size_t(nm::len(unwrap(subgraph).nodes())) == n );
    }
}
// mixed gvn: a graph mixing compile-time and runtime nodes.
// lhs has compile-time shape, rhs has runtime shape: the buffer nodes
// carry compile-time alias ids (2 and 4) so their hashes are computed
// at compile time, while the compute nodes broadcast a runtime-shaped
// operand (0: add, 1/3: broadcast_to wrappers) so their hashes are only
// known at runtime -- the resulting map has mixed value flavors.
TEST_CASE("gvn(case7)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = nmtools_tuple{2_ct,3_ct,2_ct};
    auto rhs_shape = nmtools_array{2,3,2};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);
    auto res = view::add(lhs,rhs);
    auto tree = unwrap(fn::get_computational_tree(res));

    {
        auto id_values = fn::gvn(tree);
        NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_constant_map, decltype(id_values) );

        // buffer nodes (compile-time alias id) must have compile-time
        // hash values; compute nodes over a runtime-shaped operand must
        // have runtime values
        using tree_t = decltype(tree);
        using node_ids_t = tree_t::node_ids_type;
        using id_values_t = decltype(id_values);
        using values_t = id_values_t::values_type;
        using node_attributes_t = tree_t::node_attributes_type;
        constexpr auto N = nm::len_v<values_t>;
        static_assert( N == 5 );
        nm::template_for<N>([&](auto i){
            constexpr auto I = decltype(i)::value;
            using value_i = nm::at_t<values_t,I>;
            using node_i  = nm::at_t<node_attributes_t,I>;
            constexpr auto is_buffer = nm::is_buffer_node_v<node_i>;
            static_assert( nm::is_constant_index_v<value_i> == is_buffer
                , "expect buffer nodes to be compile-time values and compute nodes to be runtime values"
            );
        });

        CHECK( id_values.size() == 5 );

        // the runtime loop must have filled every runtime slot,
        // and every id must be present with a nonzero hash
        nm::template_for<N>([&](auto i){
            constexpr auto I = decltype(i)::value;
            using node_id_t = nm::at_t<node_ids_t,I>;
            auto id = node_id_t::value;
            CHECK( id_values.count(id) > 0 );
            CHECK( id_values.at(id) != 0 );
        });

        // every node of this graph is structurally unique, so all
        // gvn hashes must be distinct
        nm::template_for<N>([&](auto i){
            constexpr auto I = decltype(i)::value;
            using node_id_i = nm::at_t<node_ids_t,I>;
            auto id_i = node_id_i::value;
            nm::template_for<N>([&](auto j){
                constexpr auto J = decltype(j)::value;
                if constexpr (I < J) {
                    using node_id_j = nm::at_t<node_ids_t,J>;
                    auto id_j = node_id_j::value;
                    CHECK( id_values.at(id_i) != id_values.at(id_j) );
                }
            });
        });

        // deterministic across invocations
        auto again = fn::gvn(tree);
        nm::template_for<N>([&](auto i){
            constexpr auto I = decltype(i)::value;
            using node_id_t = nm::at_t<node_ids_t,I>;
            auto id = node_id_t::value;
            CHECK( id_values.at(id) == again.at(id) );
        });
    }
}
