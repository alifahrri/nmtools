#include "nmtools/runtime/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/gvn.hpp"
#include "nmtools/core/transform/cse.hpp"
#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/batch_norm.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/array/bilinear.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/index/hash.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/core/transform/filter_buffer.hpp"
#include "nmtools/core/transform/filter_compute.hpp"

namespace nm    = nmtools;
namespace nk    = nmtools::network;
namespace fn    = nmtools::functional;
namespace nrt   = nmtools::runtime;
namespace view  = nmtools::view;
namespace utils = nmtools::utils;

using nmtools_array, nm::unwrap;
using namespace nmtools::literals;

TEST_CASE("get_computational_graph(broadcast_to)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto inp_shape = array{4};
    auto dst_shape = array{3,4};

    nrt::ndarray input = nm::random(inp_shape,dtype,gen);

    auto input_f32   = *input.data<float>();
    auto buffer_node = fn::node(input_f32);
    CHECK( nm::is_pointer_v<decltype(buffer_node.input)> );
    CHECK( nm::is_shared_ptr_v<decltype(buffer_node.input)> );
    CHECK( nm::is_same_v<decltype(buffer_node.input),std::shared_ptr<nmtools_list<float>>> );

    auto vinput = input.view(dtype);
    auto res = view::broadcast_to(vinput,dst_shape);

    /*********************************************************************** */

    CHECK( nm::is_pointer_v<decltype(vinput.array)> );
    CHECK( nm::is_shared_ptr_v<decltype(vinput.array)> );

    auto vbuffer = fn::node(vinput.array);
    CHECK( nm::is_pointer_v<decltype(vbuffer.input)> );
    CHECK( nm::is_shared_ptr_v<decltype(vbuffer.input)> );

    auto vnode = nrt::to_value(vbuffer);
    CHECK( vnode.input_.get_if<std::shared_ptr<nmtools_list<float>>>() );
    CHECK_MESSAGE( true, vnode.attributes()["input_type"].string );

    /*********************************************************************** */

    {
        auto graph = nrt::to_value(unwrap(fn::get_computational_tree(vinput)));
        CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );

        auto buffer_nodes  = fn::filter_buffer(graph);
        CHECK( nm::type(graph) == nrt::DType::Float32 );
        CHECK( buffer_nodes.size() == 1 );
        auto buffer = graph.nodes(buffer_nodes.at(0));
        CHECK(  buffer.input_.get_if<std::shared_ptr<nmtools_list<float>>>() );
    }

    /*********************************************************************** */

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    NMTOOLS_ASSERT_EQUAL( nm::shape(graph), dst_shape );

    /*********************************************************************** */

    auto buffer_nodes  = fn::filter_buffer(graph);
    auto compute_nodes = fn::filter_compute(graph);
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( buffer_nodes.size() == 1 );
    CHECK( compute_nodes.size() == 2 ); // reshape + broadcast

    auto buffer = graph.nodes(buffer_nodes.at(0));
    CHECK( buffer.is_buffer() );
    CHECK( buffer.dtype() == nrt::DType::Float32 );

    CHECK(  buffer.input_.get_if<std::shared_ptr<nmtools_list<float>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<double>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<int8_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<int16_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<int32_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<int64_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<uint8_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<uint16_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<uint32_t>>>() );
    CHECK( !buffer.input_.get_if<std::shared_ptr<nmtools_list<uint64_t>>>() );
    CHECK_MESSAGE( true, buffer.attributes()["input_type"].string );

    NMTOOLS_ASSERT_EQUAL( buffer.shape(), nmtools_array{4} );
    
    /*********************************************************************** */

    // reshape & broadcast_to
    auto c0 = graph.nodes(compute_nodes.at(0));
    auto c1 = graph.nodes(compute_nodes.at(1));
    auto c0_hash = fn::hash(c0);
    auto c1_hash = fn::hash(c1);
    CHECK( c0_hash != 0 );
    CHECK( c1_hash != 0 );
    CHECK( c0_hash != c1_hash );

    auto b0 = graph.nodes(buffer_nodes.at(0));
    auto b0_hash = fn::hash(b0);
    CHECK( b0_hash != 0 );

    /*********************************************************************** */

    auto gvn = fn::gvn(graph);

    auto m_b0_hash = gvn.at(buffer_nodes.at(0));
    CHECK( m_b0_hash != 0 );
    CHECK( m_b0_hash == b0_hash );

    auto m_c0_hash = gvn.at(compute_nodes.at(0));
    auto m_c1_hash = gvn.at(compute_nodes.at(1));
    CHECK( m_c0_hash != 0 );
    CHECK( m_c1_hash != 0 );
    CHECK( m_c0_hash != m_c1_hash );
    CHECK( m_c0_hash != c0_hash );
    CHECK( m_c1_hash != c1_hash );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

TEST_CASE("get_computational_graph(cos)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a_shape = array{3,4};

    /*********************************************************************** */

    nrt::ndarray a = nm::random(a_shape,dtype,gen);

    auto res = view::cos(a.view(dtype));

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    /*********************************************************************** */

    auto keys = graph.nodes();
    [[maybe_unused]]
    auto cos  = graph.nodes(nm::at(keys,0_ct));
    CHECK_MESSAGE( true, cos.to_string().at(0) );
    CHECK_MESSAGE( true, cos.to_string().at(1) );
    CHECK( cos.is_compute() );
    CHECK( cos.kind() == fn::Kind::UNARY_UFUNC );
    CHECK( cos.attributes_.count("op") );

    NMTOOLS_ASSERT_EQUAL( nm::shape(graph), a_shape );

    /*********************************************************************** */

    auto buffer_nodes  = fn::filter_buffer(graph);
    auto compute_nodes = fn::filter_compute(graph);
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( buffer_nodes.size() == 1 );
    CHECK( compute_nodes.size() == 2 ); // reshape + cos

    /*********************************************************************** */

    // reshape & cos
    auto c0 = graph.nodes(compute_nodes.at(0));
    auto c1 = graph.nodes(compute_nodes.at(1));
    auto c0_hash = fn::hash(c0);
    auto c1_hash = fn::hash(c1);
    CHECK( c0_hash != 0 );
    CHECK( c1_hash != 0 );
    CHECK( c0_hash != c1_hash );

    auto b0 = graph.nodes(buffer_nodes.at(0));
    auto b0_hash = fn::hash(b0);
    CHECK( b0_hash != 0 );
}

TEST_CASE("get_computational_graph(add)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4};

    /*********************************************************************** */

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs.view(dtype), rhs.view(dtype));

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    /*********************************************************************** */

    auto graphviz = utils::to_string(graph,utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    NMTOOLS_ASSERT_EQUAL( nm::shape(graph), lhs_shape );
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( fn::filter_buffer(graph).size() == 2 );

    /*********************************************************************** */

    auto buffer_nodes  = fn::filter_buffer(graph);
    auto compute_nodes = fn::filter_compute(graph);
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( buffer_nodes.size() == 2 );
    CHECK( compute_nodes.size() == 5 ); // 2 reshape 2 broadcast 1 add

    /*********************************************************************** */

    auto c0 = graph.nodes(compute_nodes.at(0));
    auto c1 = graph.nodes(compute_nodes.at(1));
    auto c0_hash = fn::hash(c0);
    auto c1_hash = fn::hash(c1);
    CHECK( c0_hash != 0 );
    CHECK( c1_hash != 0 );
    CHECK( c0_hash != c1_hash );

    auto b0 = graph.nodes(buffer_nodes.at(0));
    auto b1 = graph.nodes(buffer_nodes.at(1));
    auto b0_hash = fn::hash(b0);
    auto b1_hash = fn::hash(b1);
    CHECK( b0_hash != 0 );
    CHECK( b1_hash != 0 );
    CHECK( b0_hash != b1_hash );

    /*********************************************************************** */
    {
        using view_type = decltype(unwrap(view::add(nm::declval<nrt::ndarray>().view(dtype),nm::declval<nrt::ndarray>().view(dtype))));
        using tree_type = decltype(fn::get_computational_graph(nm::declval<view_type>()));
        constexpr auto ct_tree = nm::to_value_v<tree_type>;
        nrt::Graph g = ct_tree;
        NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(g), true );
    }
}

// same dtype & shape of lhs & rhs
TEST_CASE("get_computational_graph(add)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{3,4};

    /*********************************************************************** */

    nrt::ndarray lhs = nm::random(lhs_shape,dtype,gen);
    nrt::ndarray rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::add(lhs.view(dtype), rhs.view(dtype));

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    /*********************************************************************** */

    auto graphviz = utils::to_string(graph,utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    NMTOOLS_ASSERT_EQUAL( nm::shape(graph), lhs_shape );
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( fn::filter_buffer(graph).size() == 2 );

    /*********************************************************************** */

    auto buffer_nodes  = fn::filter_buffer(graph);
    auto compute_nodes = fn::filter_compute(graph);
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( buffer_nodes.size() == 2 );
    CHECK( compute_nodes.size() == 5 ); // 2 reshape 2 broadcast 1 add

    /*********************************************************************** */

    auto c0 = graph.nodes(compute_nodes.at(0));
    auto c1 = graph.nodes(compute_nodes.at(1));
    auto c0_hash = fn::hash(c0);
    auto c1_hash = fn::hash(c1);
    CHECK( c0_hash != 0 );
    CHECK( c1_hash != 0 );
    CHECK( c0_hash != c1_hash );

    auto b0 = graph.nodes(buffer_nodes.at(0));
    auto b1 = graph.nodes(buffer_nodes.at(1));
    auto b0_hash = fn::hash(b0);
    auto b1_hash = fn::hash(b1);
    CHECK( b0_hash != 0 );
    CHECK( b1_hash != 0 );
    CHECK( b0_hash != b1_hash );
}

TEST_CASE("get_computational_graph(softmax)" * doctest::test_suite("transform"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    nrt::ndarray input = nm::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res  = view::softmax(input.view(dtype),axis);

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );

    /*********************************************************************** */

    auto buffer_nodes  = fn::filter_buffer(graph);
    auto compute_nodes = fn::filter_compute(graph);
    CHECK( nm::type(graph) == nrt::DType::Float32 );
    CHECK( buffer_nodes.size() == 4 ); // 4 array input (of the same)
    CHECK( compute_nodes.size() == 18 );

    /*********************************************************************** */

    auto c0 = graph.nodes(compute_nodes.at(0));
    auto c1 = graph.nodes(compute_nodes.at(1));
    auto c0_hash = fn::hash(c0);
    auto c1_hash = fn::hash(c1);
    CHECK( c0_hash != 0 );
    CHECK( c1_hash != 0 );
    CHECK( c0_hash != c1_hash );

    auto b0 = graph.nodes(buffer_nodes.at(0));
    auto b1 = graph.nodes(buffer_nodes.at(1));
    auto b2 = graph.nodes(buffer_nodes.at(2));
    auto b3 = graph.nodes(buffer_nodes.at(3));
    auto b0_hash = fn::hash(b0);
    auto b1_hash = fn::hash(b1);
    auto b2_hash = fn::hash(b2);
    auto b3_hash = fn::hash(b3);
    CHECK( b0_hash != 0 );
    CHECK( b1_hash != 0 );
    CHECK( b2_hash != 0 );
    CHECK( b3_hash != 0 );
    // same input, same address
    CHECK( b0_hash == b1_hash );
    CHECK( b1_hash == b2_hash );
    CHECK( b2_hash == b3_hash );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

TEST_CASE("get_computational_graph(avg_pool2d)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    nrt::ndarray input = nm::random(array{1,1,7,7},dtype,gen);

    auto kernel_size = array{3,3};
    auto stride      = array{2,2};
    auto ceil_mode   = nm::False;

    auto res = view::avg_pool2d(input.view(dtype),kernel_size,stride,nm::None,nm::None,ceil_mode);

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

TEST_CASE("get_computational_graph(bilinear)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto a = nm::random(array{3,1,2,3},dtype,gen);
    auto b = nm::random(array{3,1,2,4},dtype,gen);
    auto weight = nm::random(array{2,3,4},dtype,gen);
    auto bias = nm::random(array{2},dtype,gen);

    auto res = view::bilinear(a,b,weight,bias);

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

TEST_CASE("get_computational_graph(batch_norm)" * doctest::test_suite("runtime"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    nrt::ndarray input  = nm::random(array{1,2,5,5},dtype,gen);
    nrt::ndarray mean   = nm::random(array{2},dtype,gen);
    nrt::ndarray var    = nm::random(array{2},dtype,gen);
    nrt::ndarray weight = nm::random(array{2},dtype,gen);
    nrt::ndarray bias   = nm::random(array{2},dtype,gen);

    auto res = view::batch_norm(input.view(dtype),mean.view(dtype),var.view(dtype),weight.view(dtype),bias.view(dtype));

    auto ct_graph = fn::get_computational_tree(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

TEST_CASE("get_computational_graph(var)" * doctest::test_suite("transform"))
{
    auto dtype = nm::float32;
    auto gen = nm::random_engine();

    nrt::ndarray input = nm::random(array{3,4},dtype,gen);
    auto axis = -1;
    auto res  = view::var(input.view(dtype),axis);

    auto graph = nrt::to_value(nm::unwrap(fn::get_computational_tree(res)));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );

    /*********************************************************************** */

    auto subgraph = fn::cse(graph);
    auto subgraphviz = utils::to_string(unwrap(subgraph),utils::Graphviz);

    CHECK( nm::is_same_v<decltype(subgraph),nrt::Graph> );
    CHECK_MESSAGE( true, subgraphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(subgraph), true );
}

#if 0
// TODO: fix variant handling
#if 0
TEST_CASE("get_computational_graph(matmul)" * doctest::test_suite("runtime"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::matmulv3(lhs,rhs);

    auto ct_graph = fn::get_computational_graph(res);
    auto graph = nrt::to_value(nm::unwrap(ct_graph));

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);
    CHECK( nm::is_same_v<decltype(graph),nrt::Graph> );
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );

    CHECK( nm::type(graph) == nrt::DType::Float32 );
}
#endif
#endif