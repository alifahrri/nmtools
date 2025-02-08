#include "nmtools/core/transform/binary_fusion.hpp"
#include "nmtools/core/transform/unary_fusion.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/tile.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/stddev.hpp"
#include "nmtools/array/batch_norm.hpp"
#include "nmtools/array/group_norm.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

// matmul
TEST_CASE("find_binary_fusion(case1a)" * doctest::test_suite("transform"))
{
    using vector = utl::static_vector<int,5>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,5>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(4),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{2,3,4};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// softmax
TEST_CASE("find_binary_fusion(case2a)" * doctest::test_suite("transform"))
{
    using vector = utl::static_vector<int,5>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,5>{
        make_vector(1,2),
        make_vector(2),
        make_vector(3,4),
        make_vector(4),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{0,1,2};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// var
TEST_CASE("find_binary_fusion(case3a)" * doctest::test_suite("transform"))
{
    using vector = utl::static_vector<int,7>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,7>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(6),
        make_vector(6),
        make_vector()
    };

    auto result = fn::find_binary_fusion(list);

    // NOTE: the operand is unordered
    auto expected = nmtools_tuple{1,2,3};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

// matmul
TEST_CASE("transform_binary_fusion(case1a)" * doctest::test_suite("transform"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}] * fn::transpose[/*axes=*/array{1,0}])
        .add_node(635_ct,fn::sum[/*axis=*/-1] * fn::multiply)
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,447_ct)
        .add_edge(447_ct,635_ct)
        .add_edge(765_ct,635_ct)
    ;

    auto result = fn::transform_binary_fusion(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(softmax)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;
    auto input = na::random(array{3,4},dtype,gen);
    auto axis  = -1;

    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<-1>);

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(softmax-1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;
    auto input = na::random(array{3,4},dtype,gen);
    auto axis  = -1;

    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<1>);

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(softmax-2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;
    auto input = na::random(array{3,4},dtype,gen);
    auto axis  = -1;

    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto g2 = fn::transform_binary_fusion(g1,meta::ct_v<1>);
    auto g3 = fn::transform_binary_fusion(g2,meta::ct_v<1>);
    auto result = g3;

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// TODO: fix compile on gcc, complains about no matching constructor for ct_digraph
#ifdef __clang__
TEST_CASE("transform_binary_fusion(stddev)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{3,7},dtype,gen);

    auto res = view::stddev(a,-1);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<-1>);

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

TEST_CASE("transform_binary_fusion(batch_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<-1>);

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(group_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto num_groups = 5;
    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    // auto axis   = array{-3,-2,-1};
    auto res    = view::group_norm(input,num_groups,weight,bias);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<-1>);

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}