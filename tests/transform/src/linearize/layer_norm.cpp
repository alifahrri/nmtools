#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/layer_norm.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

#if 1
TEST_CASE("transform_unary_fusion(layer_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(layer_norm1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(layer_norm2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<2>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(layer_norm3)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<3>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(layer_norm4)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<4>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 0
TEST_CASE("transform_binary_fusion(layer_norm5)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto g1 = fn::transform_unary_fusion(graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(g1,meta::ct_v<5>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 0
TEST_CASE("linearize(layer_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5,2,2},dtype,gen);
    auto bias   = na::random(array{5,2,2},dtype,gen);
    auto res    = view::layer_norm(input,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif