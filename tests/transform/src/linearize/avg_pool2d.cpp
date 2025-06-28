#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/random.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("linearize(avg_pool2d)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype = nm::float32;

    auto input = na::random(array{1,1,7,7},dtype,gen);
    auto kernel_size = array{3,3};
    auto stride = array{2,2};
    auto ceil_mode = nm::False;

    auto res = view::avg_pool2d(input,kernel_size,stride,nm::None,nm::None,ceil_mode);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}