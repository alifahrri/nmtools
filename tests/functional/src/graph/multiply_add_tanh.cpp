#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nmtools::literals;

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::add(a,rhs_array);
    auto c = view::tanh(b);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(2_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(3_ct,&rhs_array)
        .add_node(4_ct,fn::node_t{fn::add,nmtools_tuple{2_ct,3_ct}})
        .add_node(5_ct,fn::node_t{fn::tanh,nmtools_tuple{4_ct}})
        .add_edge(0_ct,2_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(2_ct,4_ct)
        .add_edge(3_ct,4_ct)
        .add_edge(4_ct,5_ct)
    ;

    // TODO: handle maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto rhs = view::alias(rhs_array,1_ct);
    auto a = view::multiply(lhs_array,rhs);
    auto b = view::add(a,rhs);
    auto c = view::tanh(b);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(3_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(5_ct,fn::node_t{fn::add,nmtools_tuple{2_ct,1_ct}})
        .add_node(6_ct,fn::node_t{fn::tanh,nmtools_tuple{5_ct}})
        .add_edge(0_ct,3_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(1_ct,5_ct)
        .add_edge(3_ct,5_ct)
        .add_edge(5_ct,6_ct)
    ;

    // TODO: handle maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto lhs = view::alias(lhs_array,0_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,rhs);
    auto c = view::tanh(b);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(3_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(5_ct,fn::node_t{fn::add,nmtools_tuple{2_ct,1_ct}})
        .add_node(6_ct,fn::node_t{fn::tanh,nmtools_tuple{5_ct}})
        .add_edge(0_ct,3_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(1_ct,5_ct)
        .add_edge(3_ct,5_ct)
        .add_edge(5_ct,6_ct)
    ;

    // TODO: handle maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto lhs = view::alias(lhs_array,3_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,rhs);
    auto c = view::tanh(b);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(3_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(5_ct,fn::node_t{fn::multiply,nmtools_tuple{3_ct,1_ct}})
        .add_node(7_ct,fn::node_t{fn::add,nmtools_tuple{2_ct,1_ct}})
        .add_node(8_ct,fn::node_t{fn::tanh,nmtools_tuple{7_ct}})
        .add_edge(3_ct,5_ct)
        .add_edge(1_ct,5_ct)
        .add_edge(1_ct,7_ct)
        .add_edge(5_ct,7_ct)
        .add_edge(7_ct,8_ct)
    ;

    
        // TODO: handle maybe type// CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}