#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/view/group_norm.hpp"
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
TEST_CASE("group_norm" * doctest::test_suite("functional::get_compute_graph") * doctest::skip())
{
    auto input_shape = nmtools_array{1,2,5,5};
    auto gamma_shape = nmtools_array{2,5,5};
    auto beta_shape  = nmtools_array{2,5,5};

    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto gamma = na::reshape(na::arange(ix::product(gamma_shape)),gamma_shape);
    auto beta  = na::reshape(na::arange(ix::product(beta_shape)),beta_shape);

    auto num_groups = 1;
    auto axis = nmtools_array{-3,-2,-1};

    // TODO: support maybe type for group_norm
    auto group_norm = view::group_norm(unwrap(input),num_groups,unwrap(gamma),unwrap(beta),axis);
    auto graph = fn::get_compute_graph(unwrap(group_norm));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz));
}
