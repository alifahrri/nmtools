#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/ufuncs/maximum.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/exp.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nm::literals;

TEST_CASE("softmax" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    
    auto lhs = view::alias(lhs_array,0_ct);

    auto a = nm::unwrap(view::reduce_maximum(lhs,axis));
    auto b = view::subtract(a,lhs);
    auto c = view::exp(b);
    auto d = nm::unwrap(view::reduce_add(c,axis));
    auto e = view::divide(d,c);

    auto graph = nm::unwrap(fn::get_compute_graph(e));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{fn::reduce_maximum[a.axis][nm::None][a.initial][a.keepdims],nmtools_tuple{0_ct}})
        .add_node(3_ct,fn::node_t{fn::subtract,nmtools_tuple{1_ct,0_ct}})
        .add_node(4_ct,fn::node_t{fn::exp,nmtools_tuple{3_ct}})
        .add_node(5_ct,fn::node_t{fn::reduce_add[d.axis][nm::None][d.initial][d.keepdims],nmtools_tuple{4_ct}})
        .add_node(7_ct,fn::node_t{fn::divide,nmtools_tuple{5_ct,4_ct}})
        .add_edge(0_ct,1_ct)
        .add_edge(0_ct,3_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(3_ct,4_ct)
        .add_edge(4_ct,5_ct)
        .add_edge(4_ct,7_ct)
        .add_edge(5_ct,7_ct)
    ;
    
    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}