#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/ufuncs/maximum.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/exp.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/functional/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nm::view;

// NOTE: fail because exp is not properly aliased
// TODO: fix
TEST_CASE("softmax" * doctest::test_suite("functional::graph") * doctest::may_fail())
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto axis = 0;
    
    auto a = view::reduce_maximum(lhs_array,axis);
    auto b = view::subtract(a,lhs_array);
    auto c = view::exp(b);
    auto d = view::reduce_add(c,axis);
    auto e = view::divide(d,c);

    [[maybe_unused]]
    auto nodes = nmtools_tuple{
        fn::alias
        , fn::reduce_maximum[a.axis][nm::None][a.initial][a.keepdims]
        , fn::alias
        , fn::subtract
        , fn::exp
        , fn::reduce_add[d.axis][nm::None][d.initial][d.keepdims]
        , fn::divide
    };

    [[maybe_unused]]
    auto edges = nmtools_tuple{
        nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple<>{}
        , nmtools_tuple{meta::ct_v<(int)-1>,meta::ct_v<(int)-2>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>}
        , nmtools_tuple{meta::ct_v<(int)-1>,meta::ct_v<(int)-2>}
    };

    [[maybe_unused]] auto graph = fn::get_graph(e);
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(graph.nodes)>, meta::len_v<decltype(nodes)> );
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(graph.edges)>, meta::len_v<decltype(edges)> );
    NMTOOLS_TESTING_LOG_TYPEINFO( graph );

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