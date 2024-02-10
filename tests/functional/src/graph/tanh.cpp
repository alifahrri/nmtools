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

TEST_CASE("tanh" * doctest::test_suite("functional::graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto a = view::tanh(lhs_array);
    
    [[maybe_unused]]
    auto nodes = nmtools_tuple{
          fn::alias
        , fn::tanh
    };
    [[maybe_unused]]
    auto edges = nmtools_tuple{
          nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-1>}
    };

    [[maybe_unused]] auto graph = fn::get_graph(a);
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(nodes)>, meta::len_v<decltype(graph.nodes)> );
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(edges)>, meta::len_v<decltype(graph.edges)> );

    {
        constexpr auto M = meta::len_v<decltype(graph.nodes)>;
        constexpr auto N = meta::len_v<decltype(nodes)>;
        constexpr auto LEN = M > N ? N : M;
        meta::template_for<LEN>([&](auto i){
            auto expect = nm::at(nodes,i);
            auto result = nm::at(graph.nodes,i);
            using expect_t = decltype(expect);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
        });
    }

    {
        constexpr auto M = meta::len_v<decltype(graph.edges)>;
        constexpr auto N = meta::len_v<decltype(edges)>;
        constexpr auto LEN = M > N ? N : M;
        meta::template_for<LEN>([&](auto i){
            auto expect = nm::at(edges,i);
            auto result = nm::at(graph.edges,i);
            using expect_t = decltype(expect);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
        });
    }
}

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