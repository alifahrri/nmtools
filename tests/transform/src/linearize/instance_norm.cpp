#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/instance_norm.hpp"
#include "nmtools/array/random.hpp"
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

#if 1
TEST_CASE("transform_unary_fusion(instance_norm_2d)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<2>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d3)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<3>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d4)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<4>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d5)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<5>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d6)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<6>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("transform_binary_fusion(instance_norm_2d7)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<7>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

#if 1
TEST_CASE("linearize(instance_norm_2d)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,5,2,2},dtype,gen);
    auto weight = na::random(array{5},dtype,gen);
    auto bias   = na::random(array{5},dtype,gen);
    auto res    = view::instance_norm_2d(input,weight,bias);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif