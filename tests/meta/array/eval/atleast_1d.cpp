#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/atleast_1d.hpp"
#include "nmtools/array/ndarray/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(atleast_1d)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::atleast_1d_t, int >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<int,1>,nmtools_tuple<meta::ct<1ul>>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_shape_v<view_t> );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, nmtools_list<int> >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, nmtools_array<int,3> >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<int,3>,decltype(nmtools_tuple{3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, int[3] >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<int,3>,decltype(nmtools_tuple{3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        // TODO: fix
        // static_assert( meta::is_fixed_shape_v<view_t> );
    }
    // fixed-shape, dynamic buffer
    {
        using view_t = view::decorator_t< view::atleast_1d_t, na::ndarray_t<nmtools_list<float>,nmtools_array<size_t,3>> >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_list<float>,nmtools_array<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    // fixed-shape, fixed buffer
    {
        using view_t = view::decorator_t< view::atleast_1d_t, na::ndarray_t<nmtools_array<float,3>,nmtools_array<size_t,3>> >;
        using eval_t = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<float,3>,nmtools_array<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    // constant-shape, dynamic-buffer
    {
        using array_type = na::ndarray_t<nmtools_array<float,12>,decltype(nmtools_tuple{2_ct,3_ct,2_ct}) >;
        using view_t     = view::decorator_t< view::atleast_1d_t, array_type >;
        using eval_t     = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<float,12>,decltype(nmtools_tuple{2_ct,3_ct,2_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    // fixed-dim, fixed-buffer
    {
        using array_type = na::ndarray_t<nmtools_array<float,12>,nmtools_array<size_t,3>>;
        using view_t     = view::decorator_t< view::atleast_1d_t, array_type >;
        using eval_t     = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<float,12>,nmtools_array<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    // constant-shape, fixed-buffer
    {
        using array_type = na::ndarray_t<nmtools_array<float,12>,decltype(nmtools_tuple{2_ct,3_ct,2_ct})>;
        using view_t     = view::decorator_t< view::atleast_1d_t, array_type >;
        using eval_t     = meta::resolve_optype_t<na::eval_result_t, view_t, none_t>;
        using expected_t = na::ndarray_t<nmtools_array<float,12>,decltype(nmtools_tuple{2_ct,3_ct,2_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}