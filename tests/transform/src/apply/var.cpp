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

// TODO: fix compile on gcc
#if 1
TEST_CASE("apply_graph(var)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto input = na::random(array{3,4},nm::float32,gen);
    auto axis  = -1;
    auto res   = view::var(input,axis);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif