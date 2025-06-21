#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/reshape.hpp"
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

TEST_CASE("get_computational_graph(reshape)" * doctest::test_suite("transform"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto src_shape = array{12};
    auto dst_shape = array{3,4};

    auto input = na::random(src_shape,dtype,gen);

    auto res = view::reshape(input,dst_shape);

    auto tree = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(tree),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(tree), true );
}