#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/broadcast_to.hpp"
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

TEST_CASE("get_computational_graph(broadcast_to)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto inp_shape = array{4};
    auto dst_shape = array{3,4};

    auto input = na::random(inp_shape,dtype,gen);

    auto res = view::broadcast_to(input,dst_shape);

    auto tree = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(tree),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(tree), true );
}