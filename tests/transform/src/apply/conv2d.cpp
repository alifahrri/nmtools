#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/conv2d.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

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

#if 1
TEST_CASE("apply_graph(conv2d)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype  = nm::float32;
    auto input  = na::random(array{1,1,4,4},dtype,gen);
    auto weight = na::random(array{1,1,3,3},dtype,gen);

    auto res = view::conv2d(input,weight);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif