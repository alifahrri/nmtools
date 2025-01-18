#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/arange.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(arange)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::arange_t, int, int, int, int >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using start_t = meta::remove_cvref_t<decltype(0_ct)>;
        using stop_t  = meta::remove_cvref_t<decltype(4_ct)>;
        using view_t  = view::decorator_t< view::arange_t, start_t, stop_t, none_t, int>;
        using eval_t  = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t >;
        using shape_t = nmtools_tuple<meta::ct<4ul>>;
        using buffer_t = nmtools_array<int,4>;
        using expected_t = na::ndarray_t<buffer_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_shape, view_t );
        using view_type = typename view_t::view_type;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::has_shape, view_type );
        constexpr auto fixed_shape = meta::fixed_shape_v<view_t>;
        static_assert( !meta::is_fail_v<decltype(fixed_shape)> );
        static_assert( meta::is_integral_constant_v<start_t> );
        static_assert( meta::is_fixed_shape_v<view_t> );
    }
    {
        using start_t = meta::remove_cvref_t<decltype(0_ct)>;
        using stop_t  = meta::remove_cvref_t<decltype(4_ct)>;
        using step_t  = decltype(2_ct);
        using view_t  = view::decorator_t< view::arange_t, start_t, stop_t, step_t, int>;
        using eval_t  = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t >;
        using shape_t = nmtools_tuple<meta::ct<2ul>>;
        using buffer_t = nmtools_array<int,2>;
        using expected_t = na::ndarray_t<buffer_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}