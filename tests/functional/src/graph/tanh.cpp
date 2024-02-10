#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
#include "nmtools/array/array/reshape.hpp"
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

TEST_CASE("tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto a = view::tanh(lhs_array);

    [[maybe_unused]]
    auto graph = fn::get_compute_graph(a);

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{fn::tanh,nmtools_tuple{0_ct}})
        .add_edge(0_ct,1_ct)
    ;

    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

TEST_CASE("tanh" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    [[maybe_unused]]
    auto array = view::alias(lhs_array,5_ct);
    auto a = view::tanh(array);

    [[maybe_unused]]
    auto graph = fn::get_compute_graph(a);

    [[maybe_unused]]
    auto expect = fn::compute_graph_t<>()
        .add_node(5_ct,&lhs_array)
        .add_node(6_ct,fn::node_t{fn::tanh,nmtools_tuple{5_ct}})
        .add_edge(5_ct,6_ct)
    ;

    auto operands = fn::get_operands(a);
    const auto& operand = nmtools::get<0>(operands);
    using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
    static_assert( meta::is_same_view_v<view::alias_t,operand_t> );
    constexpr auto NODE_ID = typename operand_t::id_type{};
    static_assert( NODE_ID == 5 );
    static_assert( typename decltype(array)::view_type::id_type{} == 5 );
    static_assert( typename decltype(array)::id_type{} == 5 );

    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}