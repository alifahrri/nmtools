#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;

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

namespace utils = nmtools::utils;

using nmtools::unwrap;

TEST_CASE("multiply" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto a = view::multiply(lhs_array,rhs_array);

    auto node_id = get_node_id(a);

    auto graph = unwrap(fn::get_compute_graph(a));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(node_id,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_edge(0_ct,node_id)
        .add_edge(1_ct,node_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( unwrap(graph), expect );
}

TEST_CASE("multiply" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto lhs = view::alias(lhs_array,3_ct);
    auto a = view::multiply(lhs,rhs_array);

    auto node_id = get_node_id(a);

    auto graph = unwrap(fn::get_compute_graph(a));

    auto expect = fn::compute_graph_t<>()
        .add_node(3_ct,&lhs_array)
        .add_node(5_ct,&rhs_array)
        .add_node(node_id,fn::node_t{fn::multiply,nmtools_tuple{3_ct,5_ct}})
        .add_edge(3_ct,node_id)
        .add_edge(5_ct,node_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( unwrap(graph), expect );
}

TEST_CASE("multiply" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto rhs = view::alias(rhs_array,3_ct);
    auto a = view::multiply(lhs_array,rhs);

    auto node_id = get_node_id(a);

    auto graph = unwrap(fn::get_compute_graph(a));

    auto expect = fn::compute_graph_t<>()
        .add_node(4_ct,&lhs_array)
        .add_node(3_ct,&rhs_array)
        .add_node(node_id,fn::node_t{fn::multiply,nmtools_tuple{4_ct,3_ct}})
        .add_edge(4_ct,node_id)
        .add_edge(3_ct,node_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( unwrap(graph), expect );
}

TEST_CASE("multiply" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto rhs = view::alias(rhs_array,3_ct);
    auto lhs = view::alias(lhs_array,4_ct);
    auto a = view::multiply(lhs,rhs);

    auto node_id = get_node_id(a);

    auto graph = unwrap(fn::get_compute_graph(a));

    auto expect = fn::compute_graph_t<>()
        .add_node(4_ct,&lhs_array)
        .add_node(3_ct,&rhs_array)
        .add_node(node_id,fn::node_t{fn::multiply,nmtools_tuple{4_ct,3_ct}})
        .add_edge(4_ct,node_id)
        .add_edge(3_ct,node_id)
    ;

    // TODO: support comparison on maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( unwrap(graph), expect );
}