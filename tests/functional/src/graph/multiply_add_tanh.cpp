#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/tanh.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/alias.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/tanh.hpp"
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

using namespace nmtools::literals;

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::add(lhs_array,a);
    auto c = view::tanh(b);
    
    // lhs_array duplicated because it is not aliased
    auto nodes = nmtools_tuple{
          fn::alias    // add lhs (lhs_array)
        , fn::alias    // mul lhs (lhs_array)
        , fn::alias    // mul rhs (rhs_array)
        , fn::multiply // add rhs
        , fn::add
        , fn::tanh
    };
    auto edges = nmtools_tuple{
          nmtools_tuple<>{}
        , nmtools_tuple<>{}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-4>,meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
    };

    auto graph = fn::get_graph(c);

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

TEST_CASE("multiply_add_tanh" * doctest::test_suite("functional::graph"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto a = view::multiply(lhs_array,rhs_array);
    auto b = view::add(a,rhs_array);
    auto c = view::tanh(b);
    
    // lhs_array duplicated because it is not aliased
    auto nodes = nmtools_tuple{
          fn::alias    // mul lhs (lhs_array)
        , fn::alias    // mul rhs (rhs_array)
        , fn::multiply // add lhs
        , fn::alias    // add rhs
        , fn::add
        , fn::tanh
    };
    auto edges = nmtools_tuple{
          nmtools_tuple<>{}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-2>,meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
    };

    auto graph = fn::get_graph(c);

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