#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/view/instance_norm.hpp"
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

// TODO: fix runtime crash (failed unwrap?)
TEST_CASE("instance_norm" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape = nmtools_array{1,2,5,5};
    auto gamma_shape = nmtools_array{2,5,5};
    auto beta_shape  = nmtools_array{2,5,5};

    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto gamma = na::reshape(na::arange(ix::product(gamma_shape)),gamma_shape);
    auto beta  = na::reshape(na::arange(ix::product(beta_shape)),beta_shape);

    // TODO: support maybe type for instance_norm
    auto instance_norm = view::instance_norm(unwrap(input),unwrap(gamma),unwrap(beta), 2_ct);
    auto graph = fn::get_compute_graph(unwrap(instance_norm));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz));
}
