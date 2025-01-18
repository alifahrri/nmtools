#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/softmin.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nm::literals;
using nm::None, nm::True, nm::unwrap;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

TEST_CASE("softmin(test1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = unwrap(na::reshape(lhs_buffer,lhs_shape));

    auto axis = 0;

    auto input = view::aliased(lhs_array);
    
    auto a = view::negative(input);
    auto b = view::reduce_maximum(a,axis,None,None,True);
    auto c = view::subtract(a,b);

    auto graph = fn::get_compute_graph(unwrap(c));

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::negative,nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::reduce_maximum[unwrap(b).attributes()],nmtools_tuple{a_id}})
        .add_node(c_id,fn::node_t{fn::subtract,nmtools_tuple{a_id,b_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(0_ct,b_id)
        .add_edge(b_id,c_id)
    ;

    CHECK_MESSAGE( nm::has_value(graph), utils::to_string(graph,utils::Graphviz));
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("softmin(test2)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = unwrap(na::reshape(lhs_buffer,lhs_shape));

    auto axis = 0;

    auto input = view::aliased(lhs_array);
    
    auto a = view::negative(input);
    auto b = view::reduce_maximum(a,axis,None,None,True);
    auto c = view::subtract(a,b);
    auto d = view::exp(c);

    auto graph = fn::get_compute_graph(unwrap(d));

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::negative,nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::reduce_maximum[unwrap(b).attributes()],nmtools_tuple{a_id}})
        .add_node(c_id,fn::node_t{fn::subtract,nmtools_tuple{a_id,b_id}})
        .add_node(d_id,fn::node_t{fn::exp,nmtools_tuple{c_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(0_ct,b_id)
        .add_edge(b_id,c_id)
        .add_edge(c_id,d_id)
    ;

    CHECK_MESSAGE( nm::has_value(graph), utils::to_string(graph,utils::Graphviz));
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("softmin(test3)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = unwrap(na::reshape(lhs_buffer,lhs_shape));

    auto axis = 0;

    auto input = view::aliased(lhs_array);
    
    auto a = view::negative(input);
    auto b = view::reduce_maximum(a,axis,None,None,True);
    auto c = view::subtract(a,b);
    auto d = view::exp(c);
    auto e = view::reduce_add(d,axis,None,None,True);

    auto graph = fn::get_compute_graph(unwrap(e));

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::negative,nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::reduce_maximum[unwrap(b).attributes()],nmtools_tuple{a_id}})
        .add_node(c_id,fn::node_t{fn::subtract,nmtools_tuple{a_id,b_id}})
        .add_node(d_id,fn::node_t{fn::exp,nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::reduce_add[unwrap(e).attributes()],nmtools_tuple{d_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(0_ct,b_id)
        .add_edge(b_id,c_id)
        .add_edge(c_id,d_id)
        .add_edge(d_id,e_id)
    ;

    CHECK_MESSAGE( nm::has_value(graph), utils::to_string(graph,utils::Graphviz));
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("softmin(test4)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = unwrap(na::reshape(lhs_buffer,lhs_shape));

    auto axis = 0;

    auto input = view::aliased(lhs_array);
    
    auto a = view::negative(input);
    auto b = view::reduce_maximum(a,axis,None,None,True);
    auto c = view::subtract(a,b);
    auto d = view::exp(c);
    auto e = view::reduce_add(d,axis,None,None,True);
    auto f = view::divide(e,d);

    auto graph = fn::get_compute_graph(unwrap(f));

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);
    auto f_id = get_node_id(f);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::negative,nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::reduce_maximum[unwrap(b).attributes()],nmtools_tuple{a_id}})
        .add_node(c_id,fn::node_t{fn::subtract,nmtools_tuple{a_id,b_id}})
        .add_node(d_id,fn::node_t{fn::exp,nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::reduce_add[unwrap(e).attributes()],nmtools_tuple{d_id}})
        .add_node(f_id,fn::node_t{fn::divide,nmtools_tuple{e_id,d_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(0_ct,b_id)
        .add_edge(b_id,c_id)
        .add_edge(c_id,d_id)
        .add_edge(d_id,e_id)
        .add_edge(e_id,f_id)
        .add_edge(d_id,f_id)
    ;

    CHECK_MESSAGE( nm::has_value(graph), utils::to_string(graph,utils::Graphviz));
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("softmin" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto softmax = view::softmin(lhs_array,axis);
    auto graph = nm::unwrap(fn::get_compute_graph(softmax));

    {
        auto a = view::negative(lhs_array);
        auto b = view::reduce_maximum(a,axis,None,None,True);
        auto c = view::subtract(a,b);
        auto d = view::exp(c);
        auto e = view::reduce_add(d,axis,None,None,True);
        auto f = view::divide(d,e);

        auto a_id = get_node_id(a);
        auto b_id = get_node_id(b);
        auto c_id = get_node_id(c);
        auto d_id = get_node_id(d);
        auto e_id = get_node_id(e);
        auto f_id = get_node_id(f);

        // TODO: make unwrap retrun reference avoid &*lhs_array, use &unwrap(lhs_array)
        auto expect = fn::compute_graph_t<>()
            .add_node(0_ct,&*lhs_array)
            .add_node(a_id,fn::node_t{fn::unary_ufunc[unwrap(a).attributes()],nmtools_tuple{0_ct}})
            .add_node(b_id,fn::node_t{fn::reduce[unwrap(b).attributes()],nmtools_tuple{a_id}})
            .add_node(c_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(c).attributes()],nmtools_tuple{a_id,b_id}})
            .add_node(d_id,fn::node_t{fn::unary_ufunc[unwrap(d).attributes()],nmtools_tuple{c_id}})
            .add_node(e_id,fn::node_t{fn::reduce[unwrap(e).attributes()],nmtools_tuple{d_id}})
            .add_node(f_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(f).attributes()],nmtools_tuple{e_id,d_id}})
            .add_edge(0_ct,a_id)
            .add_edge(a_id,b_id)
            .add_edge(b_id,c_id)
            .add_edge(a_id,c_id)
            .add_edge(c_id,d_id)
            .add_edge(d_id,e_id)
            .add_edge(e_id,f_id)
            .add_edge(d_id,f_id)
        ;

        // CHECK_MESSAGE( nm::has_value(graph), utils::to_string(graph,utils::Graphviz));
        NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
    }
}