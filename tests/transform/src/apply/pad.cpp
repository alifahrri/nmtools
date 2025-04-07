#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/array/pad.hpp"
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

TEST_CASE("apply_graph(pad)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    int pad_width[3][2] = {
        {0,1},
        {2,3},
        {4,5},
    };

    auto res = view::pad(a,pad_width);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));
    auto operands = fn::get_operands(graph);
    auto function = fn::get_function(graph);
    auto functor  = function.functor;

    auto result = fn::apply(functor,operands);
    auto expected = res;
    NMTOOLS_ASSERT_CLOSE( result, expected );
}