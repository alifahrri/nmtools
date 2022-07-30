#include "nmtools/array/array/mean.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) std::declval<type>()

TEST_CASE("eval(mean)" * doctest::test_suite("eval"))
{
    // None axis
    {
        using reduced_t = view::decorator_t<view::reduce_t, view::add_t<>, int [2][3][2], nm::none_t, nm::none_t, std::false_type >;
        using view_t    = view::decorator_t<view::scalar_ufunc_t, view::divide_t, reduced_t, size_t>;
        using eval_t    = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = size_t;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_num_v<view_t> );
        static_assert( std::is_same_v<meta::get_element_type_t<size_t>,size_t> );
    }
    {
        using array_t    = int[3][2];
        using axis_t     = none_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = none_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = none_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = none_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = none_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // runtime axis
    // TODO: infer view::mean as hybrid ndarray whenever possible
    {
        using array_t    = int[3][2];
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // compile time axis
    // TODO: infer view::mean as hybrid ndarray whenever possible
    {
        using array_t    = int[3][2];
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = nmtools_array<element_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = nmtools_array<element_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::fixed_ndarray<element_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = std::false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using element_t  = float;
        using expected_t = na::dynamic_ndarray<element_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // None axis, runtime keepdims
    {
        using array_t    = int[3][2];
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        using left_t     = meta::get_either_left_t<view_t>;
        using right_t    = meta::get_either_right_t<view_t>;
        using left_eval_t    = meta::resolve_optype_t< na::eval_t, left_t, none_t >;
        using right_eval_t   = meta::resolve_optype_t< na::eval_t, right_t, none_t >;
        using left_expect_t  = float;
        using right_expect_t = nmtools_array<nmtools_array<float,1>,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( left_eval_t, left_expect_t );
        NMTOOLS_STATIC_CHECK_IS_SAME( right_eval_t, right_expect_t );
    }
    {
        using array_t    = int[3][2];
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using eval_t     = decltype(na::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        using expected_t = nmtools_either<float,nmtools_array<nmtools_array<float,1ul>,1ul>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}