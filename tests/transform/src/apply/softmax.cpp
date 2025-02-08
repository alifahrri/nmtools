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

#if 1
TEST_CASE("apply_graph(softmax)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto input = na::random(array{3,4},dtype,gen);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));

    auto function = fn::get_function(graph);
    auto operands = fn::get_operands(graph);

    auto f = function.functor;

    auto result = fn::apply(function.functor,operands);

    static_assert( meta::len_v<decltype(operands)> == 1 );
    NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 1 );

    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif