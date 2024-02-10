#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

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
    CHECK_MESSAGE( true, utils::to_string(graph) );
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
    CHECK_MESSAGE( true, utils::to_string(graph) );
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
    CHECK_MESSAGE( true, utils::to_string(graph) );
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

    CHECK_MESSAGE( true, utils::to_string(graph) );
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

    CHECK_MESSAGE( true, utils::to_string(graph) );
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

    CHECK_MESSAGE( true, utils::to_string(graph) );
}