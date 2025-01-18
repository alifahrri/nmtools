#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
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

#if 1
namespace utils = nmtools::utils;

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    auto a = view::reduce_add(lhs_array,axis);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto operands = nm::unwrap(fn::get_operands(b));
    const auto& operand = nmtools::get<0>(operands);
    using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
    static_assert( meta::is_view_v<operand_t> );
    // static_assert( decltype(nm::unwrap(a))::id_type{} == 1 );
    // static_assert( decltype(nm::unwrap(b))::id_type{} == 2 );
    static_assert( decltype(nm::unwrap(a))::arity == 1 );
    static_assert( decltype(nm::unwrap(b))::arity == 1 );
    static_assert( nm::len(decltype(nm::unwrap(b))::operands_ids) == 1 );
    // static_assert( nm::at(decltype(nm::unwrap(b))::operands_ids,0) == 1 );

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(a_id,fn::node_t{
            fn::reduce_add[nm::unwrap(a).axis][nm::None][nm::unwrap(a).initial][nm::unwrap(a).keepdims]
            , nmtools_tuple{0_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(0_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: handle comparison of maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    auto array = view::alias(lhs_array,9_ct);
    auto a = view::reduce_add(array,axis);
    auto b = view::tanh(a);

    auto a_id = get_node_id(a);
    auto b_id = get_node_id(b);

    auto graph = nm::unwrap(fn::get_compute_graph(b));

    auto expect = fn::compute_graph_t<>()
        .add_node(9_ct,&lhs_array)
        .add_node(a_id,fn::node_t{
            fn::reduce_add[nm::unwrap(a).axis][nm::None][nm::unwrap(a).initial][nm::unwrap(a).keepdims]
            , nmtools_tuple{9_ct}})
        .add_node(b_id,fn::node_t{fn::tanh,nmtools_tuple{a_id}})
        .add_edge(9_ct,a_id)
        .add_edge(a_id,b_id)
    ;

    // TODO: handle comparison of maybe type
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

#endif