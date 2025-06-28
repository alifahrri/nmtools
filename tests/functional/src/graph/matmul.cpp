#include "nmtools/array/matmul.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;
using nm::unwrap;

TEST_CASE("matmul(case1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape = nmtools_array{3,4};
    auto rhs_shape = nmtools_array{4,3};

    auto lhs = na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape);
    auto rhs = na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape);

    auto result = view::matmulv2(lhs,rhs);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE(true, utils::to_string(graph,utils::Graphviz));
}