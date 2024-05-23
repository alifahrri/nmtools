#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/functional/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nmtools::literals;

namespace utils = nmtools::utils;

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_compute_graph") * doctest::may_fail())
{
    auto lhs_shape = nmtools_array{12};
    auto lhs_array = na::arange(12);

    auto a = view::broadcast_to(lhs_array,lhs_shape);

    [[maybe_unused]]
    auto graph = nm::unwrap(fn::get_compute_graph(a));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{fn::broadcast_to[lhs_shape],nmtools_tuple{0_ct}})
        .add_edge(0_ct,1_ct)
    ;

    // TODO: support comparison of maybe graph
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape = nmtools_array{12};
    auto lhs_array = na::arange(12);

    auto a = view::broadcast_to(lhs_array,lhs_shape);

    [[maybe_unused]]
    auto graph = nm::unwrap(fn::get_compute_graph(a));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{fn::indexing[nm::unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_edge(0_ct,1_ct)
    ;

    // TODO: support comparison of maybe graph
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}