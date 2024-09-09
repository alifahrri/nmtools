#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/view/conv1d.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/conv1d.hpp"
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
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,5,4};
    auto weight_shape = nmtools_array{1,5,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto result = view::conv1d(unwrap(input),unwrap(weight));
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,5,4};
    auto weight_shape = nmtools_array{1,5,3};
    auto bias_shape   = nmtools_array{1};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto result = view::conv1d(unwrap(input),unwrap(weight),unwrap(bias));
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
// striding
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,5,4};
    auto weight_shape = nmtools_array{1,5,3};
    auto bias_shape   = nmtools_array{1};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto stride = 2;

    auto result = view::conv1d(unwrap(input),unwrap(weight),unwrap(bias),stride);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
// striding + dilation
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{1,6,6};
    auto weight_shape = nmtools_array{1,6,3};
    auto bias_shape   = nmtools_array{1};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto stride   = 2;
    auto padding  = nm::None;
    auto dilation = 2;

    auto result = view::conv1d(unwrap(input),unwrap(weight),unwrap(bias),stride,padding,dilation);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

// TODO: fix runtime crash (failed unwrap?)
// batch + striding + dilation
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape  = nmtools_array{4,6,6};
    auto weight_shape = nmtools_array{4,6,3};
    auto bias_shape   = nmtools_array{1};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto stride   = 2;
    auto padding  = nm::None;
    auto dilation = 2;

    auto result = view::conv1d(unwrap(input),unwrap(weight),unwrap(bias),stride,padding,dilation);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

#if 0
// striding + padding + dilation
TEST_CASE("conv1d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,6,6};
    auto weight_shape = nmtools_array{1,6,3};
    auto bias_shape   = nmtools_array{1};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);
    auto bias   = na::reshape(na::arange(ix::product(bias_shape)),bias_shape);

    auto stride   = 2;
    auto padding  = 1;
    auto dilation = 2;

    auto result = view::conv1d(unwrap(input),unwrap(weight),unwrap(bias),stride,padding,dilation);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}
#endif