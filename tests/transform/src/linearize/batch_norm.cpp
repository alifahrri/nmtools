#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/batch_norm.hpp"
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

// batch_norm
TEST_CASE("transform_unary_fusion(batch_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<2>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm3)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<3>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm4)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<4>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm5)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<5>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm6)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<6>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(batch_norm7)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::transform_unary_fusion(fn::get_compute_graph(unwrap(res)),meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<7>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// batch_norm
TEST_CASE("linearize(batch_norm)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,2,5,5},dtype,gen);
    auto mean   = na::random(array{2},dtype,gen);
    auto var    = na::random(array{2},dtype,gen);
    auto weight = na::random(array{2},dtype,gen);
    auto bias   = na::random(array{2},dtype,gen);
    auto res    = view::batch_norm(input,mean,var,weight,bias);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}