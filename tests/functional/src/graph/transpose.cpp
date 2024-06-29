#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/functional/transpose.hpp"
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
using meta::ct_v;

using nmtools::unwrap;

#define get_node_id(a) \
[&](){ \
    using array_type = decltype(unwrap(a)); \
    using view_type  = typename array_type::view_type; \
    constexpr auto view_vtype = meta::as_value_v<view_type>; \
    constexpr auto node_id    = meta::generate_view_id(array_type::operands_ids,view_vtype); \
    return node_id; \
}()

TEST_CASE("transpose" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = nm::unwrap(na::reshape(lhs_buffer,lhs_shape));

    auto a = view::transpose(lhs_array);

    auto a_id = get_node_id(a);

    [[maybe_unused]]
    auto graph = nm::unwrap(fn::get_compute_graph(a));

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::transpose,nmtools_tuple{0_ct}})
        .add_edge(0_ct,a_id)
    ;

    // TODO: support comparison of maybe graph
    NMTOOLS_ASSERT_GRAPH_EQUAL( nm::unwrap(graph), expect );
}