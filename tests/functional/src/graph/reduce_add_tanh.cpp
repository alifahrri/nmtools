#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
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

TEST_CASE("reduce_add_tanh" * doctest::test_suite("functional::graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    auto a = view::reduce_add(lhs_array,axis);
    auto b = view::tanh(a);
    
    [[maybe_unused]]
    auto nodes = nmtools_tuple{
          fn::alias
        , fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims]
        , fn::tanh
    };
    [[maybe_unused]]
    auto edges = nmtools_tuple{
          nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
    };

    [[maybe_unused]] auto graph = fn::get_graph(b);
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(graph.nodes)>, meta::len_v<decltype(nodes)> );
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(graph.edges)>, meta::len_v<decltype(edges)> );

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

    auto graph = fn::get_compute_graph(b);

    auto operands = fn::get_operands(b);
    const auto& operand = nmtools::get<0>(operands);
    using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
    static_assert( meta::is_view_v<operand_t> );
    static_assert( decltype(a)::id_type{} == 1 );
    static_assert( decltype(b)::id_type{} == 2 );
    static_assert( decltype(a)::arity == 1 );
    static_assert( decltype(b)::arity == 1 );
    static_assert( nm::len(decltype(b)::operands_ids) == 1 );
    static_assert( nm::at(decltype(b)::operands_ids,0) == 1 );

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(1_ct,fn::node_t{
            fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims]
            , nmtools_tuple{0_ct}})
        .add_node(2_ct,fn::node_t{fn::tanh,nmtools_tuple{1_ct}})
        .add_edge(0_ct,1_ct)
        .add_edge(1_ct,2_ct)
    ;

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

    auto graph = fn::get_compute_graph(b);

    auto expect = fn::compute_graph_t<>()
        .add_node(9_ct,&lhs_array)
        .add_node(10_ct,fn::node_t{
            fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims]
            , nmtools_tuple{9_ct}})
        .add_node(11_ct,fn::node_t{fn::tanh,nmtools_tuple{10_ct}})
        .add_edge(9_ct,10_ct)
        .add_edge(10_ct,11_ct)
    ;

    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}

#endif