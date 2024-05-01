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
namespace utils = nmtools::utils;

using namespace nmtools::literals;

// NOTE: accidentally correct results?
TEST_CASE("multiply_add_tanh_add(case1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::add(a,bias_array);
    auto c = view::tanh(b);
    auto d = view::add(lhs_array,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("multiply_add_tanh_add(case2)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,2_ct);

    auto a = view::multiply(lhs,rhs_array);
    auto b = view::add(a,bias_array);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// NOTE: the following is an example of composition that we can't capture correctly for now
TEST_CASE("multiply_add_tanh_add(case3)" * doctest::test_suite("functional::get_compute_graph") * doctest::may_fail())
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto rhs = view::alias(lhs_array,3_ct);

    auto a = view::multiply(lhs_array,rhs);
    auto b = view::add(a,bias_array);
    auto c = view::tanh(b);
    auto d = view::add(lhs_array,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( false, utils::to_string(graph,utils::Graphviz) );
}

// NOTE: accidental success?
TEST_CASE("multiply_add_tanh_add(case4)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto bias = view::alias(bias_array,4_ct);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs_array,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("multiply_add_tanh_add(case5)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,0_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto bias = view::alias(bias_array,2_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(2_ct,&bias_array)
        .add_node(3_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(5_ct,fn::node_t{fn::add,nmtools_tuple{3_ct,2_ct}})
        .add_node(6_ct,fn::node_t{fn::tanh,nmtools_tuple{5_ct}})
        .add_node(8_ct,fn::node_t{fn::add,nmtools_tuple{6_ct,0_ct}})
        .add_edge(0_ct,3_ct)
        .add_edge(0_ct,8_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(2_ct,5_ct)
        .add_edge(3_ct,5_ct)
        .add_edge(5_ct,6_ct)
        .add_edge(6_ct,8_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

// NOTE: error maybe because fn::multiply as id 3, but bias also id 3
// TODO: better error message / handling
#if 0
TEST_CASE("multiply_add_tanh_add(case6)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,0_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto bias = view::alias(bias_array,3_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}
#endif

TEST_CASE("multiply_add_tanh_add(case7)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,0_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto bias = view::alias(bias_array,4_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(4_ct,&bias_array)
        .add_node(3_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(6_ct,fn::node_t{fn::add,nmtools_tuple{3_ct,4_ct}})
        .add_node(7_ct,fn::node_t{fn::tanh,nmtools_tuple{6_ct}})
        .add_node(9_ct,fn::node_t{fn::add,nmtools_tuple{7_ct,0_ct}})
        .add_edge(0_ct,3_ct)
        .add_edge(0_ct,9_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(4_ct,6_ct)
        .add_edge(3_ct,6_ct)
        .add_edge(6_ct,7_ct)
        .add_edge(7_ct,9_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("multiply_add_tanh_add(case8)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,0_ct);
    auto rhs = view::alias(rhs_array,1_ct);
    auto bias = view::alias(bias_array,5_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,&rhs_array)
        .add_node(5_ct,&bias_array)
        .add_node(3_ct,fn::node_t{fn::multiply,nmtools_tuple{0_ct,1_ct}})
        .add_node(7_ct,fn::node_t{fn::add,nmtools_tuple{3_ct,5_ct}})
        .add_node(8_ct,fn::node_t{fn::tanh,nmtools_tuple{7_ct}})
        .add_node(10_ct,fn::node_t{fn::add,nmtools_tuple{8_ct,0_ct}})
        .add_edge(0_ct,3_ct)
        .add_edge(0_ct,10_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(5_ct,7_ct)
        .add_edge(3_ct,7_ct)
        .add_edge(7_ct,8_ct)
        .add_edge(8_ct,10_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}


// NOTE: maybe accidentally correct?
TEST_CASE("multiply_add_tanh_add(case9)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,1_ct);
    auto rhs = view::alias(rhs_array,2_ct);
    auto bias = view::alias(bias_array,3_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("multiply_add_tanh_add(case10)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,2_ct);
    auto rhs = view::alias(rhs_array,3_ct);
    auto bias = view::alias(bias_array,4_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(2_ct,&lhs_array)
        .add_node(3_ct,&rhs_array)
        .add_node(4_ct,&bias_array)
        .add_node(5_ct,fn::node_t{fn::multiply,nmtools_tuple{2_ct,3_ct}})
        .add_node(7_ct,fn::node_t{fn::add,nmtools_tuple{5_ct,4_ct}})
        .add_node(8_ct,fn::node_t{fn::tanh,nmtools_tuple{7_ct}})
        .add_node(10_ct,fn::node_t{fn::add,nmtools_tuple{8_ct,0_ct}})
        .add_edge(2_ct,5_ct)
        .add_edge(2_ct,10_ct)
        .add_edge(3_ct,5_ct)
        .add_edge(4_ct,7_ct)
        .add_edge(5_ct,7_ct)
        .add_edge(7_ct,8_ct)
        .add_edge(8_ct,10_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("multiply_add_tanh_add(case11)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);
    
    auto bias_shape  = nmtools_array{4};
    auto bias_buffer = na::arange(4);
    auto bias_array  = na::reshape(bias_buffer,bias_shape);

    auto lhs = view::alias(lhs_array,3_ct);
    auto rhs = view::alias(rhs_array,4_ct);
    auto bias = view::alias(bias_array,5_ct);

    auto a = view::multiply(lhs,rhs);
    auto b = view::add(a,bias);
    auto c = view::tanh(b);
    auto d = view::add(lhs,c);

    auto graph = nm::unwrap(fn::get_compute_graph(d));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(3_ct,&lhs_array)
        .add_node(4_ct,&rhs_array)
        .add_node(5_ct,&bias_array)
        .add_node(6_ct,fn::node_t{fn::multiply,nmtools_tuple{3_ct,4_ct}})
        .add_node(8_ct,fn::node_t{fn::add,nmtools_tuple{6_ct,5_ct}})
        .add_node(9_ct,fn::node_t{fn::tanh,nmtools_tuple{8_ct}})
        .add_node(11_ct,fn::node_t{fn::add,nmtools_tuple{9_ct,0_ct}})
        .add_edge(3_ct,6_ct)
        .add_edge(3_ct,11_ct)
        .add_edge(4_ct,6_ct)
        .add_edge(5_ct,8_ct)
        .add_edge(6_ct,8_ct)
        .add_edge(8_ct,9_ct)
        .add_edge(9_ct,11_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}