#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/view/layer_norm.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/batch_norm.hpp"
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

TEST_CASE("layer_norm" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape = nmtools_array{1,2,5,5};
    auto gamma_shape = nmtools_array{2,5,5};
    auto beta_shape  = nmtools_array{2,5,5};

    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto gamma = na::reshape(na::arange(ix::product(gamma_shape)),gamma_shape);
    auto beta  = na::reshape(na::arange(ix::product(beta_shape)),beta_shape);

    // TODO: support maybe type for layer_norm
    auto layer_norm = view::layer_norm(unwrap(input),unwrap(gamma),unwrap(beta));
    auto graph = fn::get_compute_graph(unwrap(layer_norm));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz));
}
