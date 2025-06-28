#include "nmtools/core/computational_graph.hpp"
#include "nmtools/array/bilinear.hpp"
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

TEST_CASE("get_computational_graph(bilinear)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{3,1,2,3},dtype,gen);
    auto b = na::random(array{3,1,2,4},dtype,gen);
    auto weight = na::random(array{2,3,4},dtype,gen);
    auto bias = na::random(array{2},dtype,gen);

    auto res = view::bilinear(a,b,weight,bias);

    auto tree = fn::get_computational_graph(res);

    auto graphviz = utils::to_string(unwrap(tree),utils::Graphviz);

    CHECK_MESSAGE( true, graphviz );
    NMTOOLS_ASSERT_EQUAL( nk::is_directed_acyclic_graph(tree), true );
}