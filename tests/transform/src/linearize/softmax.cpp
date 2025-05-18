#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/softmax.hpp"
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

// disabled to make compilation a little bit faster
#if 1
TEST_CASE("transform_unary_fusion(softmax)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(softmax1)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<1>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_binary_fusion(softmax2)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto src_graph = fn::get_compute_graph(nm::unwrap(res));
    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<2>);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

TEST_CASE("linearize(softmax)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}