// #define NMTOOLS_NODE_MAX_LEN (128)
// #define NMTOOLS_NODE_MAX_COMPOSITION (128)
// #define NMTOOLS_NODE_ATTRIBUTE_MAX_KEY_LEN (128)
// #define NMTOOLS_NODE_ATTRIBUTE_MAX_VALUE_STRING_LEN (128)
// #define NMTOOLS_NODE_ATTRIBUTE_MAX_INDEX_ARRAY_LEN (128)
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/layer_norm.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("get_computational_graph(layer_norm)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();

    auto dtype  = nm::float32;
    auto input  = nm::random(array{1,5,2,2},dtype,gen);
    auto weight = nm::random(array{5,2,2},dtype,gen);
    auto bias   = nm::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph), true );
    NMTOOLS_ASSERT_EQUAL( nm::meta::is_constant_adjacency_list_v<decltype(unwrap(graph).adjacency_list)>, true );
}

TEST_CASE("get_computational_graph(layer_normv)" * doctest::test_suite("transform"))
{
    auto gen = nm::random_engine();

    auto dtype  = nm::float32;
    auto input  = nm::random(array{1,5,2,2},dtype,gen);
    auto weight = nm::random(array{5,2,2},dtype,gen);
    auto bias   = nm::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_computational_graph(res);

    constexpr auto graph_v = nm::meta::to_value_v<decltype(unwrap(graph))>;
    auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz_v );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(graph_v), true );
}