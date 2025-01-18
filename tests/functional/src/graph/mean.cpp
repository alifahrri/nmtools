#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/functional/mean.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/utility/has_value.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

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

TEST_CASE("mean(test1)" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto divisor = 3;

    auto axis = 0;
    auto a = nm::unwrap(view::reduce_add(lhs_array,axis));
    auto b = view::divide(a,divisor);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    // TODO: use the same function as decorator to get the operand ids
    auto divisor_id = meta::ct_v<decltype(a_id)::value+2>;

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims],nmtools_tuple{0_ct}})
        .add_node(divisor_id,divisor)
        .add_node(b_id,fn::node_t{fn::divide,nmtools_tuple{a_id,divisor_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
        .add_edge(divisor_id,b_id)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph, utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("mean" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0_ct;
    auto a = view::mean(lhs_array,axis);

    auto graph = fn::get_compute_graph(a);

    // TODO: support maybe type for to_string for graph
    CHECK_MESSAGE( nm::has_value(a), utils::to_string(unwrap(graph),utils::Graphviz) );
}