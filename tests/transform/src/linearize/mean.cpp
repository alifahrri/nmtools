#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/var.hpp"
#include "nmtools/array/layer_norm.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"

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

TEST_CASE("transform_unary_fusion(mean)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{2,3,2},nm::float32,gen);
    auto axis  = 1;
    auto res   = view::mean(input,axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(mean2)" * doctest::test_suite("transform"))
{
    auto input    = na::reshape(na::arange(12,nm::int32),array{2,3,2});
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto keepdims = nm::True;
    auto res      = view::mean(input,axis,dtype,keepdims);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

#if 0
TEST_CASE("transform_unary_fusion(mean2)" * doctest::test_suite("transform"))
{
    int8_t input[2][3][2] = {
        {
            {0,1},
            {2,3},
            {4,5},
        },
        {
            { 6, 7},
            { 8, 9},
            {10,11},
        }
    };
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto keepdims = nm::False;
    auto res      = view::mean(input,axis,dtype,keepdims);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(mean3)" * doctest::test_suite("transform"))
{
    int input[2][3][2] = {
        {
            {0,1},
            {2,3},
            {4,5},
        },
        {
            { 6, 7},
            { 8, 9},
            {10,11},
        }
    };
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto keepdims = nm::True;
    auto res      = view::mean(input,axis,dtype,keepdims);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}
#endif

TEST_CASE("transform_binary_fusion(mean)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{2,3,2},nm::float32,gen);
    auto axis  = 1;
    auto res   = view::mean(input,axis);

    auto src_graph = fn::get_compute_graph(unwrap(res));

    auto graph = fn::transform_unary_fusion(src_graph,meta::ct_v<-1>);
    auto result = fn::transform_binary_fusion(graph,meta::ct_v<1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(mean_subtract)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = view::aliased(na::random(array{2,3,2},nm::float32,gen));
    auto axis  = 1;
    auto res   = view::subtract(input,view::mean(input,axis,nm::None,nm::True));

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(mean_subtract_var)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto epsilon = 1e-5;

    auto input = view::aliased(na::random(array{2,3,2},nm::float32,gen));
    auto axis  = 1;
    auto shift = view::subtract(input,view::mean(input,axis,nm::None,nm::True));
    auto var   = view::var(input,axis,nm::None,0,nm::True);
    auto std   = view::sqrt(view::add(var,epsilon));
    auto norm  = view::divide(shift,std);
    auto res   = norm;

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

TEST_CASE("transform_unary_fusion(mean_subtract_var)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input  = na::random(array{1,5,2,2},nm::float32,gen);
    auto weight = na::random(array{5,2,2},nm::float32,gen);
    auto bias   = na::random(array{5,2,2},nm::float32,gen);

    auto epsilon = 1e-5;

    {
        auto aliased  = view::aliased(input,weight,bias);
        auto a_input  = nmtools::get<0>(aliased);
        auto a_weight = nmtools::get<1>(aliased);
        auto a_bias   = nmtools::get<2>(aliased);

        auto wb_shape = nm::shape<true>(weight);

        auto axis  = nmtools::index::layer_norm_axis(wb_shape);
        auto dtype = nm::None;
        auto ddof  = 0;
        auto keepdims = nm::True;

        auto shift = view::subtract(a_input,view::mean(a_input,axis,dtype,keepdims));
        auto var   = view::var(a_input,axis,dtype,ddof,keepdims);
        auto std   = view::sqrt(view::add(var,epsilon));
        auto norm  = view::divide(shift,std);
        auto res   = view::add(view::multiply(norm,a_weight),a_bias);

        auto graph = fn::get_compute_graph(unwrap(res));

        auto result = fn::transform_unary_fusion(graph,meta::ct_v<-1>);

        // TODO: compare graph

        CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
        CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
    }

    {
        auto res   = view::layer_norm(input,weight,bias);
        auto graph = fn::get_compute_graph(unwrap(res));
        CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    }
}