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
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

TEST_CASE("ct_digraph(relu)" * doctest::test_suite("ct_digraph"))
{
    auto array = nmtools_array{1,2,3,4};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&array)
        .add_node(1_ct,fn::relu)
        .add_edge(0_ct,1_ct)
        // .add_edge(0_ct,1_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 2 );
    CHECK( graph.nodes(0_ct) == &array );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(1_ct), fn::relu );

    auto out_edges = graph.out_edges(0_ct);
    CHECK( meta::len_v<decltype(out_edges)> == 1 );

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(relu)" * doctest::test_suite("ct_digraph"))
{
    auto array = nmtools_array{1,2,3,4};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&array)
        .add_node(1_ct,fn::relu)
        .add_edge(0_ct,1_ct)
        .add_edge(0_ct,1_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 2 );
    CHECK( graph.nodes(0_ct) == &array );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(1_ct), fn::relu );

    // make sure edges are not duplicated    
    auto out_edges = graph.out_edges(0_ct);
    CHECK( meta::len_v<decltype(out_edges)> == 1 );
    NMTOOLS_ASSERT_EQUAL( nmtools::at(out_edges,0_ct), 1_ct );

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(reduce_add_divide)" * doctest::test_suite("ct_digraph"))
{
    auto array   = nmtools_array{1,2,3,4};
    auto divisor = 4;

    auto graph = utility::ct_digraph()
        .add_node(meta::ct_v<0>,&array)
        .add_node(meta::ct_v<1>,divisor)
        .add_node(meta::ct_v<2>,fn::reduce_add)
        .add_node(meta::ct_v<3>,fn::divide)
        // NOTE: edge are not ordered
        .add_edge(meta::ct_v<0>,meta::ct_v<2>)
        .add_edge(meta::ct_v<1>,meta::ct_v<3>)
        .add_edge(meta::ct_v<2>,meta::ct_v<3>)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 4 );
    CHECK( graph.nodes(0_ct) == &array );
    CHECK( graph.nodes(1_ct) == divisor );
    // TODO: support isequal for functors
    NMTOOLS_STATIC_CHECK_IS_SAME( 
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME( 
        meta::remove_cvref_t<decltype(graph.nodes(3_ct))>
        , meta::remove_cvref_t<decltype(fn::divide)>
    );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::reduce_add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(3_ct), fn::divide );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(0_ct), nmtools_tuple{2_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(1_ct), nmtools_tuple{3_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(2_ct), nmtools_tuple{3_ct} );
}

TEST_CASE("ct_digraph(reduce_add_tanh)" * doctest::test_suite("ct_digraph"))
{
    auto array = nmtools_array{1,2,3,4};
    
    auto graph = utility::ct_digraph()
        .add_node(meta::ct_v<0>,&array)
        .add_node(meta::ct_v<1>,fn::reduce_add)
        .add_node(meta::ct_v<2>,fn::tanh)
        .add_edge(meta::ct_v<0>,meta::ct_v<1>)
        .add_edge(meta::ct_v<1>,meta::ct_v<2>)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 3 );
    CHECK( graph.nodes(0_ct) == &array );
    // TODO: support isequal for functors
    NMTOOLS_STATIC_CHECK_IS_SAME( 
        meta::remove_cvref_t<decltype(graph.nodes(1_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::tanh)>
    );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(1_ct), fn::reduce_add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::tanh );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(0_ct), nmtools_tuple{1_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(1_ct), nmtools_tuple{2_ct} );
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(mutliply_tanh)" * doctest::test_suite("ct_digraph"))
{
    auto lhs = nmtools_array{1,2,3,4};
    auto rhs = nmtools_array{5,6,7,8};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(2_ct,fn::multiply)
        .add_node(3_ct,fn::tanh)
        .add_edge(0_ct,2_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(2_ct,3_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 4);
    CHECK( graph.nodes(0_ct) == &lhs );
    CHECK( graph.nodes(1_ct) == &rhs );
    // TODO: support isequal for functors
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::multiply)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(3_ct))>
        , meta::remove_cvref_t<decltype(fn::tanh)>
    );

    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::multiply );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(3_ct), fn::tanh );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(0_ct), nmtools_tuple{2_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(1_ct), nmtools_tuple{2_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(2_ct), nmtools_tuple{3_ct} );
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(mutliply_add_tanh)" * doctest::test_suite("ct_digraph"))
{
    auto lhs = nmtools_array{1,2,3,4};
    auto rhs = nmtools_array{5,6,7,8};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(2_ct,fn::multiply)
        .add_node(3_ct,fn::add)
        .add_node(4_ct,fn::tanh)
        .add_edge(0_ct,2_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(0_ct,3_ct)
        .add_edge(2_ct,3_ct)
        .add_edge(3_ct,4_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 5 );
    CHECK( graph.nodes(0_ct) == &lhs );
    CHECK( graph.nodes(1_ct) == &rhs );
    // TODO: support isequal for functors
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::multiply)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(3_ct))>
        , meta::remove_cvref_t<decltype(fn::add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(4_ct))>
        , meta::remove_cvref_t<decltype(fn::tanh)>
    );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::multiply );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(3_ct), fn::add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(4_ct), fn::tanh );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(0_ct), (nmtools_tuple{2_ct,3_ct}) );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(1_ct), nmtools_tuple{2_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(2_ct), nmtools_tuple{3_ct} );
    NMTOOLS_ASSERT_EQUAL( graph.out_edges(3_ct), nmtools_tuple{4_ct} );
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(multiply_add_tanh_add)" * doctest::test_suite("ct_digraph"))
{
    auto lhs = nmtools_array{1,2,3,4};
    auto rhs = nmtools_array{5,6,7,8};

    auto bias = nmtools_array{9,10,11,12};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&lhs)
        .add_node(1_ct,&rhs)
        .add_node(2_ct,fn::multiply)
        .add_node(3_ct,&bias)
        .add_node(4_ct,fn::add)
        .add_node(5_ct,fn::tanh)
        .add_node(6_ct,fn::add)
        .add_edge(0_ct,2_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(2_ct,4_ct)
        .add_edge(3_ct,4_ct)
        .add_edge(4_ct,5_ct)
        .add_edge(0_ct,6_ct)
        .add_edge(5_ct,6_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 7 );
    CHECK( graph.nodes(0_ct) == &lhs );
    CHECK( graph.nodes(1_ct) == &rhs );
    CHECK( graph.nodes(3_ct) == &bias );
    // TODO: support isequal for functors
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::multiply)>
    ); 
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(4_ct))>
        , meta::remove_cvref_t<decltype(fn::add)>
    ); 
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(5_ct))>
        , meta::remove_cvref_t<decltype(fn::tanh)>
    ); 
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(6_ct))>
        , meta::remove_cvref_t<decltype(fn::add)>
    );

    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::multiply );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(4_ct), fn::add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(5_ct), fn::tanh );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(6_ct), fn::add );
    

    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(0_ct)
        , (nmtools_tuple{2_ct,6_ct})
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(1_ct)
        , nmtools_tuple{2_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(2_ct)
        , nmtools_tuple{4_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(3_ct)
        , nmtools_tuple{4_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(4_ct)
        , nmtools_tuple{5_ct}
    );

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(variance)" * doctest::test_suite("ct_digraph"))
{
    auto array   = nmtools_array{1,2,3,4};
    auto divisor = 4;
    auto n_ddof  = 4;

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&array)
        .add_node(1_ct,fn::reduce_add)
        .add_node(2_ct,divisor)
        .add_node(3_ct,fn::divide)
        .add_node(4_ct,fn::subtract)
        .add_node(5_ct,fn::fabs)
        .add_node(6_ct,fn::square)
        .add_node(7_ct,fn::reduce_add)
        .add_node(8_ct,n_ddof)
        .add_node(9_ct,fn::divide)
        .add_edge(0_ct,1_ct)
        .add_edge(1_ct,3_ct)
        .add_edge(2_ct,3_ct)
        .add_edge(3_ct,4_ct)
        .add_edge(0_ct,4_ct)
        .add_edge(4_ct,5_ct)
        .add_edge(5_ct,6_ct)
        .add_edge(6_ct,7_ct)
        .add_edge(7_ct,9_ct)
        .add_edge(8_ct,9_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 10 );
    CHECK( graph.nodes(0_ct) == &array );
    CHECK( graph.nodes(2_ct) == divisor );
    CHECK( graph.nodes(8_ct) == n_ddof );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(1_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(3_ct))>
        , meta::remove_cvref_t<decltype(fn::divide)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(4_ct))>
        , meta::remove_cvref_t<decltype(fn::subtract)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(5_ct))>
        , meta::remove_cvref_t<decltype(fn::fabs)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(6_ct))>
        , meta::remove_cvref_t<decltype(fn::square)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(7_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(9_ct))>
        , meta::remove_cvref_t<decltype(fn::divide)>
    );

    NMTOOLS_ASSERT_EQUAL( graph.nodes(1_ct), fn::reduce_add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(3_ct), fn::divide );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(4_ct), fn::subtract );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(5_ct), fn::fabs );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(6_ct), fn::square );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(7_ct), fn::reduce_add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(9_ct), fn::divide );

    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(0_ct)
        , (nmtools_tuple{1_ct,4_ct})
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(1_ct)
        , nmtools_tuple{3_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(2_ct)
        , nmtools_tuple{3_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(3_ct)
        , nmtools_tuple{4_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(4_ct)
        , nmtools_tuple{5_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(6_ct)
        , nmtools_tuple{7_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(7_ct)
        , nmtools_tuple{9_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(8_ct)
        , nmtools_tuple{9_ct}
    );

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("ct_digraph(softmax)" * doctest::test_suite("ct_digraph"))
{
    auto input = nmtools_array{1,2,3,4};

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(1_ct,fn::reduce_maximum)
        .add_node(2_ct,fn::subtract)
        .add_node(3_ct,fn::exp)
        .add_node(4_ct,fn::reduce_add)
        .add_node(5_ct,fn::divide)
        .add_edge(0_ct,1_ct)
        .add_edge(1_ct,2_ct)
        .add_edge(0_ct,2_ct)
        .add_edge(2_ct,3_ct)
        .add_edge(3_ct,4_ct)
        .add_edge(4_ct,5_ct)
        .add_edge(3_ct,5_ct)
    ;

    NMTOOLS_ASSERT_EQUAL( graph.size(), 6 );
    CHECK( graph.nodes(0_ct) == &input );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(1_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_maximum)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(2_ct))>
        , meta::remove_cvref_t<decltype(fn::subtract)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(3_ct))>
        , meta::remove_cvref_t<decltype(fn::exp)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(4_ct))>
        , meta::remove_cvref_t<decltype(fn::reduce_add)>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(graph.nodes(5_ct))>
        , meta::remove_cvref_t<decltype(fn::divide)>
    );

    NMTOOLS_ASSERT_EQUAL( graph.nodes(1_ct), fn::reduce_maximum );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(2_ct), fn::subtract );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(3_ct), fn::exp );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(4_ct), fn::reduce_add );
    NMTOOLS_ASSERT_EQUAL( graph.nodes(5_ct), fn::divide );

    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(0_ct)
        , (nmtools_tuple{1_ct,2_ct})
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(1_ct)
        , nmtools_tuple{2_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(2_ct)
        , nmtools_tuple{3_ct}
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(3_ct)
        , (nmtools_tuple{4_ct,5_ct})
    );
    NMTOOLS_ASSERT_EQUAL(
        graph.out_edges(4_ct)
        , nmtools_tuple{5_ct}
    );

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

using nmtools_array;

// matmul
TEST_CASE("adjacency_matrix(case1)" * doctest::test_suite("ct_digraph"))
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

    // error on clang T_T
    // [[maybe_unused]]
    // const auto [matrix,id_map] = utility::adjacency_matrix(graph.digraph);

    auto result = utility::adjacency_matrix(graph.digraph);
    auto matrix = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_matrix = array{
        array{0,0,1,0,0,0,0,0},
        array{0,0,0,1,0,0,0,0},
        array{0,0,0,0,1,0,0,0},
        array{0,0,0,0,0,1,0,0},
        array{0,0,0,0,0,0,1,0},
        array{0,0,0,0,0,0,1,0},
        array{0,0,0,0,0,0,0,1},
        array{0,0,0,0,0,0,0,0},
    };

    auto expected_id = array{0,1,75,769,765,447,722,635};

    NMTOOLS_ASSERT_EQUAL( matrix, expected_matrix );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
}

using nmtools_tuple;

// softmax
TEST_CASE("adjacency_matrix(case2)" * doctest::test_suite("ct_digraph"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(263_ct,fn::reduce_maximum[/*axis=*/0])
        .add_node(975_ct,fn::subtract)
        .add_node(547_ct,fn::exp)
        .add_node(407_ct,fn::sum[/*axis=*/0])
        .add_node(850_ct,fn::divide)
        .add_edges(0_ct,tuple{263_ct,975_ct})
        .add_edge(263_ct,975_ct)
        .add_edge(975_ct,547_ct)
        .add_edges(547_ct,tuple{407_ct,850_ct})
        .add_edge(407_ct,850_ct)
    ;

    auto result = utility::adjacency_matrix(graph.digraph);
    auto matrix = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_matrix = array{
        array{0,1,1,0,0,0},
        array{0,0,1,0,0,0},
        array{0,0,0,1,0,0},
        array{0,0,0,0,1,1},
        array{0,0,0,0,0,1},
        array{0,0,0,0,0,0},
    };

    auto expected_id = array{0,263,975,547,407,850};

    NMTOOLS_ASSERT_EQUAL( matrix, expected_matrix );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
}

// var
TEST_CASE("adjacency_matrix(case3)" * doctest::test_suite("ct_digraph"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

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

    auto result = utility::adjacency_matrix(graph.digraph);
    auto matrix = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_matrix = array{
        array{0,0,1,0,1,0,0,0,0,0},
        array{0,0,0,1,0,0,0,0,0,0},
        array{0,0,0,1,0,0,0,0,0,0},
        array{0,0,0,0,1,0,0,0,0,0},
        array{0,0,0,0,0,1,0,0,0,0},
        array{0,0,0,0,0,0,1,0,0,0},
        array{0,0,0,0,0,0,0,1,0,0},
        array{0,0,0,0,0,0,0,0,0,1},
        array{0,0,0,0,0,0,0,0,0,1},
        array{0,0,0,0,0,0,0,0,0,0},
    };
    auto expected_id = array{0,472,470,51,428,391,591,433,435,1022};

    NMTOOLS_ASSERT_EQUAL( matrix, expected_matrix );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
}

namespace utl = nmtools::utl;

// matmul
TEST_CASE("adjacency_list(case1)" * doctest::test_suite("ct_digraph"))
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

    auto result = utility::adjacency_list(graph.digraph);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    using vector = utl::static_vector<int,8>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto expected_list = array<vector,8>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(6),
        make_vector(7),
        make_vector(),
    };

    auto expected_id = array{0,1,75,769,765,447,722,635};

    // NMTOOLS_ASSERT_EQUAL( matrix, expected_matrix );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );

    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

// softmax
TEST_CASE("adjacency_list(case2)" * doctest::test_suite("ct_digraph"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto graph = utility::ct_digraph()
        .add_node(0_ct,&input)
        .add_node(263_ct,fn::reduce_maximum[/*axis=*/0])
        .add_node(975_ct,fn::subtract)
        .add_node(547_ct,fn::exp)
        .add_node(407_ct,fn::sum[/*axis=*/0])
        .add_node(850_ct,fn::divide)
        .add_edges(0_ct,tuple{263_ct,975_ct})
        .add_edge(263_ct,975_ct)
        .add_edge(975_ct,547_ct)
        .add_edges(547_ct,tuple{407_ct,850_ct})
        .add_edge(407_ct,850_ct)
    ;

    auto result = utility::adjacency_list(graph.digraph);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    using vector = utl::static_vector<int,6>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto expected_list = array<vector,6>{
        make_vector(1,2),
        make_vector(2),
        make_vector(3),
        make_vector(4,5),
        make_vector(5),
        make_vector()
    };

    auto expected_id = array{0,263,975,547,407,850};

    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

// var
TEST_CASE("adjacency_list(case3)" * doctest::test_suite("ct_digraph"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

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

    auto result = utility::adjacency_list(graph.digraph);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    using vector = utl::static_vector<int,10>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto expected_list = array<vector,10>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(7),
        make_vector(9),
        make_vector(9),
        make_vector()
    };

    auto expected_id = array{0,472,470,51,428,391,591,433,435,1022};

    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

// edge contraction
/*=================================================================*/

// matmul
TEST_CASE("contracted_edge(case1)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,8>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,8>{
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(6),
        make_vector(7),
        make_vector(),
    };

    auto src_id_map = array{0,1,75,769,765,447,722,635};

    [[maybe_unused]]
    auto result = utility::contracted_edge(adj_list,src_id_map,tuple{75,765},765);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_list = array<vector,7>{
        make_vector(6),
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(),
        make_vector(4),

    };

    auto expected_id = array{0,1,769,447,722,635,765};

    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

// softmax
TEST_CASE("contracted_edge(case2)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,6>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,6>{
        make_vector(1,2),
        make_vector(2),
        make_vector(3),
        make_vector(4,5),
        make_vector(5),
        make_vector()
    };

    auto src_id_map = array{0,263,975,547,407,850};

    [[maybe_unused]]
    auto result = utility::contracted_edge(adj_list,src_id_map,tuple{975,547},547);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_list = array<vector,5>{
        make_vector(1,4),
        make_vector(4),
        make_vector(3),
        make_vector(),
        make_vector(2,3)
    };

    auto expected_id = array{0,263,407,850,547};

    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

TEST_CASE("contracted_edge(case3)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,10>;

    auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    auto adj_list = array<vector,10>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(6),
        make_vector(7),
        make_vector(9),
        make_vector(9),
        make_vector()
    };

    auto src_id_map = array{0,472,470,51,428,391,591,433,435,1022};

    [[maybe_unused]]
    auto result = utility::contracted_edge(adj_list,src_id_map,tuple{391,591},591);
    auto list   = nmtools::get<0>(result);
    auto id_map = nmtools::get<1>(result);

    auto expected_list = array<vector,9>{
        make_vector(2,4),
        make_vector(3),
        make_vector(3),
        make_vector(4),
        make_vector(8),
        make_vector(7),
        make_vector(7),
        make_vector(),
        make_vector(5)
    };

    auto expected_id = array{0,472,470,51,428,433,435,1022,591};

    NMTOOLS_ASSERT_EQUAL( list.size(), expected_list.size() );
    NMTOOLS_ASSERT_EQUAL( id_map, expected_id );
    for (size_t i=0; i<(size_t)list.size(); i++) {
        NMTOOLS_ASSERT_EQUAL( list[i], expected_list[i] );
    }
}

TEST_CASE("contracted_edge(case1)" * doctest::test_suite("ct_digraph"))
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

    auto fused  = fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}];
    auto result = utility::contracted_edge(graph,tuple{75_ct,765_ct},765_ct,fused);

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

    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(0_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(0_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(1_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(1_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(769_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(769_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(447_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(447_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(722_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(722_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(635_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(635_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(765_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(765_ct))>
    );

    // NMTOOLS_ASSERT_GRAPH_EQUAL( result, expected );
    CHECK( result.nodes(0_ct) == expected.nodes(0_ct) );
    CHECK( result.nodes(1_ct) == expected.nodes(1_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(769_ct), expected.nodes(769_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(447_ct), expected.nodes(447_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(722_ct), expected.nodes(722_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(635_ct), expected.nodes(635_ct) );
    NMTOOLS_ASSERT_EQUAL( result.nodes(765_ct), expected.nodes(765_ct) );
}

// matmul
TEST_CASE("adjacency_to_graph(case1)" * doctest::test_suite("ct_digraph"))
{
    using vector = utl::static_vector<int,8>;

    constexpr auto make_vector = [](auto...v){
        auto vec = vector();
        (vec.push_back(v),...);
        return vec;
    };

    constexpr auto list = array<vector,7>{
        make_vector(6),
        make_vector(2),
        make_vector(3),
        make_vector(4),
        make_vector(5),
        make_vector(),
        make_vector(4),

    };

    constexpr auto id_map = array{0,1,769,447,722,635,765};

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};
    auto lhs = na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape);
    auto rhs = na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape);

    auto node_data = nmtools_tuple{
        &lhs,
        &rhs,
        fn::transpose[/*axes=*/array{1,0}],
        fn::reshape[/*dst_shape=*/array{1,3,4}],
        fn::multiply,
        fn::sum[/*axis=*/-1],
        fn::reshape[/*dst_shape=*/array{3,3,4}] * fn::tile[/*reps=*/array{1,3}],
    };

    auto result = meta::template_reduce<list.size()>([&](auto G, auto index){
        constexpr auto I = decltype(index)::value;
        constexpr auto node_ct = meta::ct_v<nm::at(id_map,I)>;
        constexpr auto edges = nm::at(list,I);
        constexpr auto edges_ct = meta::template_reduce<nm::len(edges)>([&](auto init, auto index){
            return utility::tuple_append(init,nm::at(edges,index));
        },nmtools_tuple{});
        return G
            .add_node(node_ct,nm::at(node_data,index))
            .add_edges(node_ct,edges_ct)
        ;
    }, utility::ct_digraph());

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

    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(0_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(0_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(1_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(1_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(769_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(769_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(447_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(447_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(722_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(722_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(635_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(635_ct))>
    );
    NMTOOLS_STATIC_CHECK_IS_SAME(
        meta::remove_cvref_t<decltype(result.nodes(765_ct))>
        , meta::remove_cvref_t<decltype(expected.nodes(765_ct))>
    );
}