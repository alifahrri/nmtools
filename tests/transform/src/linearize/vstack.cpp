#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/array/vstack.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

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

TEST_CASE("linearize(vstack)" * doctest::test_suite("transform"))
{
    auto gen   = na::random_engine();
    auto dtype = nm::float32;

    auto lhs = na::random(array{2,3,2},dtype,gen);
    auto rhs = na::random(array{2,3,2},dtype,gen);

    auto res = view::vstack(lhs,rhs);

    auto graph = fn::get_compute_graph(nm::unwrap(res));
    auto result = fn::linearize(graph);

    // TODO: compare graph
    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}