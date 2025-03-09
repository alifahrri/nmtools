#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/var.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

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

// var
TEST_CASE("transform_unary_fusion(var)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// var
TEST_CASE("transform_binary_fusion(var1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto src_graph = fn::get_compute_graph(unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(var2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto src_graph = fn::get_compute_graph(unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<2>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(var3)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto src_graph = fn::get_compute_graph(unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);

    auto result = fn::transform_binary_fusion(graph,meta::ct_v<3>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// var
TEST_CASE("linearize(var)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}