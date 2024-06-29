#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
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
namespace utils = nmtools::utils;

using namespace nmtools::literals;
using nmtools::unwrap;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(0_ct,a_id)
        .add_edge(1_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto lhs = view::alias(lhs_array,10_ct);
    auto a = view::multiply(lhs,rhs_array);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(10_ct,&lhs_array)
        .add_node(12_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{10_ct,11_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(10_ct,a_id)
        .add_edge(12_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto rhs = view::alias(rhs_array,10_ct);
    auto a = view::multiply(lhs_array,rhs);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(11_ct,&lhs_array)
        .add_node(10_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{11_ct,10_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(10_ct,a_id)
        .add_edge(11_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}

TEST_CASE("multiply_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto lhs = view::alias(lhs_array,10_ct);
    auto rhs = view::alias(rhs_array,5_ct);
    auto a = view::multiply(lhs,rhs);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(10_ct,&lhs_array)
        .add_node(5_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{10_ct,5_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(10_ct,a_id)
        .add_edge(5_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}