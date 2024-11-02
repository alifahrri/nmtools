#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/array/moveaxis.hpp"
#include "nmtools/array/array/atleast_nd.hpp"
#include "nmtools/utility/random_engine.hpp"
#include "nmtools/array/view/batch_norm.hpp"
#include "nmtools/array/functional/batch_norm.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;
using nm::unwrap;

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    // TODO: support maybe type for batch_norm
    auto batch_norm = view::batch_norm(unwrap(input),unwrap(mean),unwrap(var),unwrap(weight),unwrap(bias));
    CHECK( nm::has_value(batch_norm) );
    auto graph = fn::get_compute_graph(unwrap(batch_norm));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm(test1)" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto src_axis = meta::ct_v<-1>;
    auto dst_axis = meta::ct_v<-3>;

    auto aliased  = view::aliased(input,mean,var,weight,bias);
    // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe
    [[maybe_unused]] auto a_input  = nmtools::get<0>(unwrap(aliased));
    [[maybe_unused]] auto a_mean   = nmtools::get<1>(unwrap(aliased));
    [[maybe_unused]] auto a_var    = nmtools::get<2>(unwrap(aliased));
    [[maybe_unused]] auto a_weight = nmtools::get<3>(unwrap(aliased));
    [[maybe_unused]] auto a_bias   = nmtools::get<4>(unwrap(aliased));

    auto a = view::atleast_nd(a_weight,3_ct);
    auto b = view::moveaxis(a,src_axis,dst_axis);
    auto graph = fn::get_compute_graph(unwrap(b));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm(test2)" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto src_axis = meta::ct_v<-1>;
    auto dst_axis = meta::ct_v<-3>;

    auto aliased  = view::aliased(input,mean,var,weight,bias);
    // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe
    [[maybe_unused]] auto a_input  = nmtools::get<0>(unwrap(aliased));
    [[maybe_unused]] auto a_mean   = nmtools::get<1>(unwrap(aliased));
    [[maybe_unused]] auto a_var    = nmtools::get<2>(unwrap(aliased));
    [[maybe_unused]] auto a_weight = nmtools::get<3>(unwrap(aliased));
    [[maybe_unused]] auto a_bias   = nmtools::get<4>(unwrap(aliased));

    {
        auto a = na::atleast_nd(a_mean,3_ct);
        auto aliased = view::aliased(a,a_input);
        auto a_a   = nmtools::get<0>(unwrap(aliased));
        auto input = nmtools::get<1>(unwrap(aliased));
        auto b = view::moveaxis(a_a,src_axis,dst_axis);
        auto c = view::subtract(input,b);
        auto graph = fn::get_compute_graph(unwrap(c));

        CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    }
    // TODO: fix, a has the same id as a_input
    #if 0
    {
        auto a = na::atleast_nd(a_mean,3_ct);
        auto b = view::moveaxis(a,src_axis,dst_axis);
        auto c = view::subtract(a_input,b);
        auto graph = fn::get_compute_graph(unwrap(c));

        CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    }
    #endif
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm(test3)" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto src_axis = meta::ct_v<-1>;
    auto dst_axis = meta::ct_v<-3>;

    auto aliased  = view::aliased(input,mean,var,weight,bias);
    // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe);
    [[maybe_unused]] auto a_input  = nmtools::get<0>(unwrap(aliased));
    [[maybe_unused]] auto a_mean   = nmtools::get<1>(unwrap(aliased));
    [[maybe_unused]] auto a_var    = nmtools::get<2>(unwrap(aliased));
    [[maybe_unused]] auto a_weight = nmtools::get<3>(unwrap(aliased));
    [[maybe_unused]] auto a_bias   = nmtools::get<4>(unwrap(aliased));

    auto a = view::atleast_nd(a_mean,3_ct);
    auto b = view::moveaxis(a,src_axis,dst_axis);
    auto c = view::subtract(a_input,b);
    auto graph = fn::get_compute_graph(unwrap(c));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm(test4)" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto aliased  = view::aliased(input,mean,var,weight,bias);
    // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe
    [[maybe_unused]] auto a_input  = nmtools::get<0>(unwrap(aliased));
    [[maybe_unused]] auto a_mean   = nmtools::get<1>(unwrap(aliased));
    [[maybe_unused]] auto a_var    = nmtools::get<2>(unwrap(aliased));
    [[maybe_unused]] auto a_weight = nmtools::get<3>(unwrap(aliased));
    [[maybe_unused]] auto a_bias   = nmtools::get<4>(unwrap(aliased));

    auto eps = 0.001f;

    auto src_axis = meta::ct_v<-1>;
    auto dst_axis = meta::ct_v<-3>;

    auto a = view::atleast_nd(a_mean,3_ct);
    auto b = view::moveaxis(a,src_axis,dst_axis);
    auto c = view::subtract(a_input,b);
    // var
    auto d = view::atleast_nd(a_var,3_ct);
    auto e = view::moveaxis(d,src_axis,dst_axis);
    // stddev
    auto f = view::add(e,eps);
    auto g = view::sqrt(f);
    // divided
    auto h = view::divide(c,g);

    auto graph = fn::get_compute_graph(unwrap(h));
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("batch_norm(test5)" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,2,5,5};
    auto mean_shape   = nmtools_array{2};
    auto var_shape    = nmtools_array{2};
    auto weight_shape = nmtools_array{2};
    auto bias_shape   = nmtools_array{2};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto mean   = na::reshape(na::arange(ix::product(mean_shape)),mean_shape);
    auto var    = na::reshape(na::arange(ix::product(var_shape)),var_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto aliased  = view::aliased(input,mean,var,weight,bias);
    // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe
    [[maybe_unused]] auto a_input  = nmtools::get<0>(unwrap(aliased));
    [[maybe_unused]] auto a_mean   = nmtools::get<1>(unwrap(aliased));
    [[maybe_unused]] auto a_var    = nmtools::get<2>(unwrap(aliased));
    [[maybe_unused]] auto a_weight = nmtools::get<3>(unwrap(aliased));
    [[maybe_unused]] auto a_bias   = nmtools::get<4>(unwrap(aliased));

    auto eps = 0.001f;

    auto src_axis = meta::ct_v<-1>;
    auto dst_axis = meta::ct_v<-3>;

    // mean
    auto a = view::atleast_nd(a_mean,3_ct);
    auto b = view::moveaxis(a,src_axis,dst_axis);
    // subtracted
    auto c = view::subtract(a_input,b);
    // var
    auto d = view::atleast_nd(a_var,3_ct);
    auto e = view::moveaxis(d,src_axis,dst_axis);
    // weight
    auto f = view::atleast_nd(a_weight,3_ct);
    auto g = view::moveaxis(f,src_axis,dst_axis);
    // stddev
    auto h = view::add(e,eps);
    auto i = view::sqrt(h);
    // divided
    auto j = view::divide(c,i);
    // multiplied
    auto k = view::multiply(j,g);

    auto graph = fn::get_compute_graph(unwrap(k));
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}