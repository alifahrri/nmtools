#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nmtools::literals;
using nmtools::unwrap;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

namespace utils = nmtools::utils;

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_compute_graph") * doctest::may_fail())
{
    auto lhs_shape = nmtools_array{12};
    auto lhs_array = na::arange(12);

    auto a = view::broadcast_to(lhs_array,lhs_shape);

    auto a_id = get_node_id(a);

    [[maybe_unused]]
    auto graph = nm::unwrap(fn::get_compute_graph(a));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::broadcast_to[lhs_shape],nmtools_tuple{0_ct}})
        .add_edge(0_ct,a_id)
    ;

    // TODO: support comparison of maybe graph
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape = nmtools_array{12};
    auto lhs_array = na::arange(12);

    auto a = view::broadcast_to(lhs_array,lhs_shape);

    auto a_id = get_node_id(a);

    [[maybe_unused]]
    auto graph = nm::unwrap(fn::get_compute_graph(a));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::indexing[nm::unwrap(a).attributes()],nmtools_tuple{0_ct}})
        .add_edge(0_ct,a_id)
    ;

    // TODO: support comparison of maybe graph
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}