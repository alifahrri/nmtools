#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/reshape.hpp"
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
using nmtools::unwrap;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

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

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    // TODO: use the same function as decorator to get the operand ids
    auto rhs_id = meta::ct_v<decltype(a_id)::value+2>;

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(rhs_id,&rhs_array)
        .add_node(b_id,fn::node_t{fn::add,nmtools_tuple{a_id,rhs_id}})
        .add_node(c_id,fn::node_t{fn::tanh,nmtools_tuple{b_id}})
        .add_edge(0_ct,a_id)
        .add_edge(1_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(rhs_id,b_id)
        .add_edge(b_id,c_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
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

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(2_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{2_ct,1_ct}})
        .add_node(b_id,fn::node_t{fn::add,nmtools_tuple{a_id,1_ct}})
        .add_node(c_id,fn::node_t{fn::tanh,nmtools_tuple{b_id}})
        .add_edge(2_ct,a_id)
        .add_edge(1_ct,a_id)
        .add_edge(1_ct,b_id)
        .add_edge(a_id,b_id)
        .add_edge(b_id,c_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
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

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(b_id,fn::node_t{fn::add,nmtools_tuple{2_ct,1_ct}})
        .add_node(c_id,fn::node_t{fn::tanh,nmtools_tuple{5_ct}})
        .add_edge(0_ct,a_id)
        .add_edge(1_ct,a_id)
        .add_edge(1_ct,b_id)
        .add_edge(a_id,b_id)
        .add_edge(b_id,c_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
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

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    auto graph = nm::unwrap(fn::get_compute_graph(c));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(3_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(a_id,fn::node_t{fn::multiply,nmtools_tuple{3_ct,1_ct}})
        .add_node(b_id,fn::node_t{fn::add,nmtools_tuple{a_id,1_ct}})
        .add_node(c_id,fn::node_t{fn::tanh,nmtools_tuple{b_id}})
        .add_edge(3_ct,a_id)
        .add_edge(1_ct,a_id)
        .add_edge(1_ct,b_id)
        .add_edge(a_id,b_id)
        .add_edge(b_id,c_id)
    ;

    
    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}