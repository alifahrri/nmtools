#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nm::literals;
using nmtools::unwrap, nmtools::None, nmtools::True;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

TEST_CASE("softmax(test1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    
    auto lhs = view::alias(lhs_array,0_ct);

    auto a = nm::unwrap(view::reduce_maximum(lhs,axis,None,None,True));
    auto b = view::subtract(a,lhs);
    auto c = view::exp(b);
    auto d = nm::unwrap(view::reduce_add(c,axis,None,None,True));
    auto e = view::divide(c,d);

    auto graph = nm::unwrap(fn::get_compute_graph(e));

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);
    auto c_id = get_node_id(c);
    auto d_id = get_node_id(d);
    auto e_id = get_node_id(e);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&*lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,0_ct}})
        .add_node(c_id,fn::node_t{fn::unary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id}})
        .add_node(d_id,fn::node_t{fn::reduce[unwrap(d).attributes()],nmtools_tuple{c_id}})
        .add_node(e_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(e).attributes()],nmtools_tuple{d_id,c_id}})
        .add_edge(0_ct,a_id)
        .add_edge(0_ct,b_id)
        .add_edge(a_id,b_id)
        .add_edge(b_id,c_id)
        .add_edge(c_id,d_id)
        .add_edge(c_id,e_id)
        .add_edge(d_id,e_id)
    ;
    
    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("softmax" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    // TODO: support maybe type for softmax
    auto softmax = view::softmax(unwrap(lhs_array),axis);
    auto graph = nm::unwrap(fn::get_compute_graph(softmax));

    {
        auto a_input = view::aliased(lhs_array);
        auto a = view::reduce_maximum(a_input,axis,None,None,True);
        auto b = view::subtract(a_input,a);
        auto c = view::exp(b);
        auto d = view::reduce_add(c,axis,None,None,True);
        auto e = view::divide(c,d);

        auto a_id = get_node_id(a);
        auto b_id = get_node_id(b);
        auto c_id = get_node_id(c);
        auto d_id = get_node_id(d);
        auto e_id = get_node_id(e);

        auto expect = fn::compute_graph_t<>()
            .add_node(0_ct,&*lhs_array)
            .add_node(a_id,fn::node_t{fn::reduce[unwrap(a).attributes()],nmtools_tuple{0_ct}})
            .add_node(b_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(b).attributes()],nmtools_tuple{a_id,0_ct}})
            .add_node(c_id,fn::node_t{fn::unary_ufunc[unwrap(c).attributes()],nmtools_tuple{b_id}})
            .add_node(d_id,fn::node_t{fn::reduce[unwrap(d).attributes()],nmtools_tuple{c_id}})
            .add_node(e_id,fn::node_t{fn::broadcast_binary_ufunc[unwrap(e).attributes()],nmtools_tuple{d_id,c_id}})
            .add_edge(0_ct,a_id)
            .add_edge(0_ct,b_id)
            .add_edge(a_id,b_id)
            .add_edge(b_id,c_id)
            .add_edge(c_id,d_id)
            .add_edge(c_id,e_id)
            .add_edge(d_id,e_id)
        ;
        
        // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
        NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
    }
}