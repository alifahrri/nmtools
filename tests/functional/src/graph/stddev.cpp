#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/fabs.hpp"
#include "nmtools/array/array/ufuncs/square.hpp"
#include "nmtools/array/array/ufuncs/sqrt.hpp"
#include "nmtools/array/array/sum.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufuncs/square.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/sqrt.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/arange.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;
namespace utils = nm::utils;

using namespace nmtools::literals;

TEST_CASE("stddev" * doctest::test_suite("functional::graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto divisor = 3;
    auto ddof = 2;

    auto axis = 0;
    auto a = view::reduce_add(lhs_array,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs_array);
    auto d = view::fabs(c);
    auto e = view::square(d);
    auto f = view::sum(e,axis);
    auto g = view::divide(f,ddof);
    auto h = view::sqrt(g);

    [[maybe_unused]]
    auto nodes = nmtools_tuple{
          fn::alias
        , fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims]
        , fn::alias
        , fn::divide
        , fn::alias
        , fn::subtract
        , fn::fabs
        , fn::square
        , fn::reduce_add[f.axis][nm::None][f.initial][f.keepdims]
        , fn::alias
        , fn::divide
        , fn::sqrt
    };
    [[maybe_unused]]
    auto edges = nmtools_tuple{
          nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
    };

    [[maybe_unused]] auto graph = fn::get_graph(h);
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

TEST_CASE("stddev" * doctest::test_suite("functional::get_compute_graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;

    auto lhs = view::alias(lhs_array,0_ct);
    auto divisor = view::alias(3,11_ct);
    auto ddof = view::alias(2,12_ct);

    auto a = view::reduce_add(lhs,axis);
    auto b = view::divide(a,divisor);
    auto c = view::subtract(b,lhs);
    auto d = view::fabs(c);
    auto e = view::square(d);
    auto f = view::sum(e,axis);
    auto g = view::divide(f,ddof);
    auto h = view::sqrt(g);

    auto graph = fn::get_compute_graph(h);

    auto expect = fn::compute_graph_t<>()
        .add_node(0_ct,&lhs_array)
        .add_node(11_ct,3)
        .add_node(12_ct,2)
        .add_node(1_ct,fn::node_t{fn::reduce_add[a.axis][nm::None][a.initial][a.keepdims],nmtools_tuple{0_ct}})
        .add_node(13_ct,fn::node_t{fn::divide,nmtools_tuple{1_ct,11_ct}})
        .add_node(15_ct,fn::node_t{fn::subtract,nmtools_tuple{13_ct,0_ct}})
        .add_node(16_ct,fn::node_t{fn::fabs,nmtools_tuple{15_ct}})
        .add_node(17_ct,fn::node_t{fn::square,nmtools_tuple{16_ct}})
        .add_node(18_ct,fn::node_t{fn::reduce_add[f.axis][nm::None][f.initial][f.keepdims],nmtools_tuple{17_ct}})
        .add_node(20_ct,fn::node_t{fn::divide,nmtools_tuple{18_ct,12_ct}})
        .add_node(21_ct,fn::node_t{fn::sqrt,nmtools_tuple{21_ct}})
        .add_edge(0_ct,1_ct)
        .add_edge(0_ct,15_ct)
        .add_edge(1_ct,13_ct)
        .add_edge(11_ct,13_ct)
        .add_edge(13_ct,15_ct)
        .add_edge(15_ct,16_ct)
        .add_edge(16_ct,17_ct)
        .add_edge(17_ct,18_ct)
        .add_edge(18_ct,20_ct)
        .add_edge(12_ct,20_ct)
        .add_edge(20_ct,21_ct)
    ;

    // CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
    NMTOOLS_ASSERT_GRAPH_EQUAL( graph, expect );
}