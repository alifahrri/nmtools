#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(broadcast_to)" * doctest::test_suite("eval") * doctest::may_fail())
{
    {
        using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, int [3], shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, nmtools_array<int,3>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = nmtools_list<int>;
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, nmtools_list<int>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_list<size_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = nmtools_list<int>;
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<int,3,2>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_list<size_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = nmtools_list<int>;
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, int[3][2], shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_list<size_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<int,3,1>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = nmtools_list<int>;
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, na::dynamic_ndarray<int>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_list<size_t>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
        using origin_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, na::dynamic_ndarray<int>, shape_t , origin_axes_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}