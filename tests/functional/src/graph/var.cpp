// #define NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE 4096
// #define NMTOOLS_ALIAS_DEFAULT_PRIME 1033

#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/var.hpp"
#include "nmtools/utility/has_value.hpp"
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

TEST_CASE("var(test1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    auto graph = unwrap(fn::get_compute_graph(c));

    // TODO: provide common function to get operands id
    auto divisor_id = 11_ct;

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,divisor}})
        .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id,0_ct}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(0_ct,c_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("var(test2)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);
    auto d = view::fabs(c);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);

    auto graph = unwrap(fn::get_compute_graph(d));

    // TODO: provide common function to get operands id
    auto divisor_id = 11_ct;

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,divisor}})
        .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id,0_ct}})
        .add_node(d_id,fn::node_t{fn::unary_ufunc[unwrap(d).attributes()],nmtools_tuple{c_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(0_ct,c_id)
        .add_edge(c_id,d_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}


TEST_CASE("var(test3)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);
    auto d = view::fabs(c);
    auto e = view::square(d);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);

    auto graph = unwrap(fn::get_compute_graph(e));

    // TODO: provide common function to get operands id
    auto divisor_id = 11_ct;

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,divisor}})
        .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id,0_ct}})
        .add_node(d_id,fn::node_t{fn::unary_ufunc[unwrap(d).attributes()],nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::unary_ufunc[unwrap(e).attributes()],nmtools_tuple{d_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(0_ct,c_id)
        .add_edge(c_id,d_id)
        .add_edge(d_id,e_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("var(test4)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);
    auto d = view::fabs(c);
    auto e = view::square(d);
    auto f = view::sum(e,axis);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);
    auto f_id = get_node_id(f);

    auto graph = unwrap(fn::get_compute_graph(f));

    // TODO: provide common function to get operands id
    auto divisor_id = 11_ct;

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,divisor}})
        .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id,0_ct}})
        .add_node(d_id,fn::node_t{fn::unary_ufunc[unwrap(d).attributes()],nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::unary_ufunc[unwrap(e).attributes()],nmtools_tuple{d_id}})
        .add_node(f_id,fn::node_t{fn::reduce[unwrap(f).attributes()],nmtools_tuple{e_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(0_ct,c_id)
        .add_edge(c_id,d_id)
        .add_edge(d_id,e_id)
        .add_edge(e_id,f_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}


TEST_CASE("var(test5)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);
    auto ddof    = 2;

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);
    auto d = view::fabs(c);
    auto e = view::square(d);
    auto f = view::sum(e,axis);
    auto g = view::divide(f,ddof);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);
    auto f_id = get_node_id(f);
    auto g_id = get_node_id(g);

    auto graph = unwrap(fn::get_compute_graph(g));

    // TODO: provide common function to get operands id
    auto divisor_id = 11_ct;
    auto ddof_id = meta::ct_v<decltype(f_id)::value+2>;

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,divisor}})
        .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id,0_ct}})
        .add_node(d_id,fn::node_t{fn::unary_ufunc[unwrap(d).attributes()],nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::unary_ufunc[unwrap(e).attributes()],nmtools_tuple{d_id}})
        .add_node(f_id,fn::node_t{fn::reduce[unwrap(f).attributes()],nmtools_tuple{e_id}})
        .add_node(ddof_id,ddof)
        .add_node(g_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(g).attributes()],nmtools_tuple{f_id,ddof_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(0_ct,c_id)
        .add_edge(c_id,d_id)
        .add_edge(d_id,e_id)
        .add_edge(e_id,f_id)
        .add_edge(f_id,g_id)
        .add_edge(ddof_id,g_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("var" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    CHECK( nm::has_value(lhs_array) );

    auto axis = 0;

    // TODO: support maybe type for var
    auto var = view::var(unwrap(lhs_array),axis);
    auto graph = fn::get_compute_graph(nm::unwrap(var));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}