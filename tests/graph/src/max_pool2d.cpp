#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace nk = nmtools::network;
namespace fn = nmtools::functional;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

TEST_CASE("get_computational_graph(max_pool2d)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();

    auto dtype = nm::float32;

    auto input = na::random(array{1,1,7,7},dtype,gen);
    auto kernel_size = array{3,3};
    auto stride = array{2,2};
    auto ceil_mode = nm::True;

    auto res = view::max_pool2d(input,kernel_size,stride,nm::None,nm::None,ceil_mode);

    auto tree = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(tree),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(tree), true );
}