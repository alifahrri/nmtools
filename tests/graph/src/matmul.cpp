#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("get_computational_graph(matmul)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::matmulv3(lhs,rhs);

    auto graph = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
    // NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(nm::get_left(unwrap(graph))->adjacency_list)>, true );
    // NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(nm::get_right(unwrap(graph))->adjacency_list)>, true );

    // constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;
    // auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    // CHECK_MESSAGE( true, graphviz_v );
    // NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph_v), true );
}

TEST_CASE("get_computational_graph(matmul-2)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto lhs_shape = array{4};
    auto rhs_shape = array{4};

    auto lhs = nm::random(lhs_shape,dtype,gen);
    auto rhs = nm::random(rhs_shape,dtype,gen);

    auto res = view::matmulv3(lhs,rhs);

    auto graph = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);
    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
    // NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(nm::get_left(unwrap(graph))->adjacency_list)>, true );
    // NMTOOLS_ASSERT_EQUAL( nm::is_constant_adjacency_list_v<decltype(nm::get_right(unwrap(graph))->adjacency_list)>, true );

    // constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;
    // auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    // CHECK_MESSAGE( true, graphviz_v );
    // NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph_v), true );
}