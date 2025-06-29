#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/pad.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("unary(pad)" * doctest::test_suite("transform"))
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

    auto graph = fn::get_computational_graph(res);


}