#include "nmtools/array/functional/transform/unary_fusion.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/activations/relu.hpp"
#include "nmtools/array/functional/tile.hpp"
#include "nmtools/array/functional/transpose.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/functional/sum.hpp"
#include "nmtools/array/view/matmul.hpp"
#include "nmtools/array/view/softmax.hpp"
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

using nmtools_array, nmtools_tuple;

// matmul
TEST_CASE("find_unary_fusion(case1a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,8>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,8>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(6),
        make_vector(7),
        make_vector()
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{2,4};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case1b)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,8>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,7>{
        make_vector(2),
        make_vector(3),
        make_vector(5),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector()
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{3,4};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case1c)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,8>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,6>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(4),
        make_vector(5),
        make_vector()
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{4,5};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case2a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,6>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,6>{
        make_vector(1,2),
        make_vector(2),
        make_vector(3),
        make_vector(4,5),
        make_vector(5),
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{2,3};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case2b)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,6>;
    
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
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{-1,-1};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case3a)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,10>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,10>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(7),
        make_vector(9),
        make_vector(9),
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);

    auto expected = nmtools_tuple{4,5};

    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case3b)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,10>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,9>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(8),
        make_vector(8),
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);
    auto expected = nmtools_tuple{4,5};
    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case3c)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,10>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto list = array<vector,8>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(7),
        make_vector(7),
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);
    auto expected = nmtools_tuple{4,5};
    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("find_unary_fusion(case3d)" * doctest::test_suite("functional"))
{
    using vector = utl::static_vector<int,10>;

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
        make_vector(),
    };

    auto result = fn::find_unary_fusion(list);
    auto expected = nmtools_tuple{-1,-1};
    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("transform_unary_fusion(case1a)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape);
    auto rhs = na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape);

    [[maybe_unused]]
    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(75_ct,fn::tile[/*reps=*/array{1,3}])
        .add_node(769_ct,fn::transpose[/*axes=*/array{1,0}])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}])
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_edge(0_ct,75_ct)
        .add_edge(1_ct,769_ct)
        .add_edge(75_ct,765_ct)
        .add_edge(769_ct,447_ct)
        .add_edge(765_ct,722_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
    ;

    auto result = fn::transform_unary_fusion(graph);

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(769_ct,fn::transpose[/*axes=*/array{1,0}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}])
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,769_ct)
        .add_edge(769_ct,447_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
        .add_edge(765_ct,722_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );

    CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );

    NMTOOLS_ASSERT_EQUAL( result.nodes(769_ct), expected.nodes(769_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct), expected.nodes(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct), expected.nodes(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct), expected.nodes(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct), expected.nodes(765_ct) );

    NMTOOLS_ASSERT_EQUAL( result.out_edges(0_ct), expected.out_edges(0_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(1_ct), expected.out_edges(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(769_ct), expected.out_edges(769_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(447_ct), expected.out_edges(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(722_ct), expected.out_edges(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(635_ct), expected.out_edges(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(765_ct), expected.out_edges(765_ct) );

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case1b)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto matmul = view::matmulv2(lhs,rhs);
    auto graph = fn::get_compute_graph(nm::unwrap(matmul));

    auto result = fn::transform_unary_fusion(graph);

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(769_ct,fn::transpose[/*axes=*/array{1,0}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}])
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,769_ct)
        .add_edge(769_ct,447_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
        .add_edge(765_ct,722_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );
    #endif // __clang__

    CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );

    // translated to indexing fmap
    // NMTOOLS_ASSERT_EQUAL( result.nodes(769_ct).functor, expected.nodes(769_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct).functor, expected.nodes(447_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct).functor, expected.nodes(722_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct).functor, expected.nodes(635_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct).functor, expected.nodes(765_ct) );

    // error on gcc
    // TODO: count the number of functor instead
    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.out_edges(0_ct), expected.out_edges(0_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(1_ct), expected.out_edges(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(769_ct), expected.out_edges(769_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(447_ct), expected.out_edges(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(722_ct), expected.out_edges(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(635_ct), expected.out_edges(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(765_ct), expected.out_edges(765_ct) );
    #endif // __clang__

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case1c)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape);
    auto rhs = na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape);

    [[maybe_unused]]
    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(769_ct,fn::transpose[/*axes=*/array{1,0}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}])
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,769_ct)
        .add_edge(769_ct,447_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
        .add_edge(765_ct,722_ct)
    ;

    auto result = fn::transform_unary_fusion(graph);

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}] * fn::transpose[/*axes=*/array{1,0}])
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,447_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
        .add_edge(765_ct,722_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );

    CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );

    // NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct), expected.nodes(447_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct), expected.nodes(722_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct), expected.nodes(635_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct), expected.nodes(765_ct) );

    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.out_edges(0_ct), expected.out_edges(0_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(1_ct), expected.out_edges(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(447_ct), expected.out_edges(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(722_ct), expected.out_edges(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(635_ct), expected.out_edges(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(765_ct), expected.out_edges(765_ct) );
    #endif // __clang__

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case1d)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto matmul = view::matmulv2(lhs,rhs);
    auto graph = fn::get_compute_graph(nm::unwrap(matmul));

    auto result = fn::transform_unary_fusion(fn::transform_unary_fusion(graph));

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(722_ct,fn::multiply)
        .add_node(635_ct,fn::sum[/*axis=*/-1])
        .add_node(765_ct,fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}])
        .add_node(447_ct,fn::reshape[/*dst_shape=*/array{1,3,4}] * fn::transpose[/*axes=*/array{1,0}])
        .add_edge(0_ct,765_ct)
        .add_edge(1_ct,447_ct)
        .add_edge(447_ct,722_ct)
        .add_edge(722_ct,635_ct)
        .add_edge(765_ct,722_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );
    #endif // __clang__

    // CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    // CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );

    // NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct), expected.nodes(447_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct), expected.nodes(722_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct), expected.nodes(635_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct), expected.nodes(765_ct) );

    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.out_edges(0_ct), expected.out_edges(0_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(1_ct), expected.out_edges(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(447_ct), expected.out_edges(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(722_ct), expected.out_edges(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(635_ct), expected.out_edges(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(765_ct), expected.out_edges(765_ct) );
    #endif // __clang__

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case1e)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto matmul = view::matmulv2(lhs,rhs);
    auto graph = fn::get_compute_graph(nm::unwrap(matmul));

    auto result = fn::transform_unary_fusion(fn::transform_unary_fusion(fn::transform_unary_fusion(graph)));

    auto expected = utility::ct_digraph()
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

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );
    #endif // __clang__

    // CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    // CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );

    // NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct), expected.nodes(447_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct), expected.nodes(722_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct), expected.nodes(635_ct) );
    // NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct), expected.nodes(765_ct) );

    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.out_edges(0_ct), expected.out_edges(0_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(1_ct), expected.out_edges(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(447_ct), expected.out_edges(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(635_ct), expected.out_edges(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.out_edges(765_ct), expected.out_edges(765_ct) );
    #endif // __clang__

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case2a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = nm::unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto view = view::softmax(input,-1);

    auto graph = fn::get_compute_graph(nm::unwrap(view));

    auto result = fn::transform_unary_fusion(graph);

    auto fused = fn::subtract * fn::exp;
    auto expected = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(263_ct,fn::reduce_maximum[/*axis=*/0])
        .add_node(657_ct,fn::sum[/*axis=*/0])
        .add_node(198_ct,fn::divide)
        .add_node(619_ct,fused)
        .add_edges(0_ct,tuple{263_ct,619_ct})
        .add_edge(263_ct,619_ct)
        .add_edge(657_ct,198_ct)
        .add_edges(619_ct,tuple{657_ct,198_ct})
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    #ifdef __clang__
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );
    #endif // __clang__

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case3a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = nm::unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(428_ct,fn::subtract)
        .add_node(391_ct,fn::fabs)
        .add_node(591_ct,fn::square)
        .add_node(433_ct,fn::reduce_add[/*axis=*/0])
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_edges(0_ct,tuple{470_ct,428_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,428_ct)
        .add_edge(428_ct,391_ct)
        .add_edge(391_ct,591_ct)
        .add_edge(591_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
    ;

    auto result = fn::transform_unary_fusion(graph);

    auto fused = fn::subtract * fn::fabs;
    auto expected = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(591_ct,fn::square)
        .add_node(433_ct,fn::reduce_add[/*axis=*/0])
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_node(391_ct,fused)
        .add_edges(0_ct,tuple{470_ct,391_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,391_ct)
        .add_edge(591_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
        .add_edge(391_ct,591_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case3b)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = nm::unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(591_ct,fn::square)
        .add_node(433_ct,fn::reduce_add[/*axis=*/0])
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_node(391_ct,fn::subtract * fn::fabs)
        .add_edges(0_ct,tuple{470_ct,391_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,391_ct)
        .add_edge(591_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
        .add_edge(391_ct,591_ct)
    ;

    auto result = fn::transform_unary_fusion(graph);

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(433_ct,fn::reduce_add[/*axis=*/0])
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_node(591_ct,fn::square * fn::subtract * fn::fabs)
        .add_edges(0_ct,tuple{470_ct,591_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,591_ct)
        .add_edge(591_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(case3c)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = nm::unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(433_ct,fn::reduce_add[/*axis=*/0])
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_node(591_ct,fn::square * fn::subtract * fn::fabs)
        .add_edges(0_ct,tuple{470_ct,591_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,591_ct)
        .add_edge(591_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
    ;

    auto result = fn::transform_unary_fusion(graph);

    auto expected = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(472_ct,3)
        .add_node(470_ct,fn::reduce_add[/*axis=*/0])
        .add_node(51_ct,fn::divide)
        .add_node(435_ct,3)
        .add_node(1022_ct,fn::divide)
        .add_node(433_ct,fn::reduce_add[0] * fn::square * fn::subtract * fn::fabs)
        .add_edges(0_ct,tuple{470_ct,433_ct})
        .add_edge(472_ct,51_ct)
        .add_edge(470_ct,51_ct)
        .add_edge(51_ct,433_ct)
        .add_edge(433_ct,1022_ct)
        .add_edge(435_ct,1022_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( result.size(), expected.size() );
    NMTOOLS_ASSERT_EQUAL( result.nodes(), expected.nodes() );

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(expected,utils::Graphviz) );
}