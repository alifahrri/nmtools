#include "nmtools/array/view/mean.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) std::declval<type>()

#ifdef NMTOOLS_DISABLE_STL
using meta::false_type, meta::true_type;
#else
using std::false_type, std::true_type;
#endif

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view::mean"))
{
    // runtime axis
    {
        using array_t    = int[3][2];
        using axis_t     = size_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = size_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = size_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = size_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = size_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // compile time axis
    // TODO: infer view::mean as hybrid ndarray whenever possible
    {
        using array_t    = int[3][2];
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = decltype(0_ct);
        // using dtype_t    = none_t;
        // using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // None axis, compile-time keepdims
    // TODO: infer view::mean as hybrid ndarray whenever possible
    {
        using array_t    = int[3][2];
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = true_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // None axis, runtime keepdims
    {
        using array_t    = int[3][2];
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
        using left_t     = meta::get_either_left_t<view_t>;
        using right_t    = meta::get_either_right_t<view_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, left_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, right_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
    }
    // TODO: fix
    #if 0
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = none_t;
        using dtype_t    = none_t;
        using keepdims_t = bool;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t),declval(dtype_t),declval(keepdims_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_either, view_t );
    }
    #endif
}

TEST_CASE("is_num" * doctest::test_suite("view::mean"))
{
    {
        using array_t    = int[3][2];
        using axis_t     = nm::none_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
    }
}

TEST_CASE("get_underlying_array_type" * doctest::test_suite("view::mean"))
{
    {
        using array_t    = int[3][2];
        using axis_t     = nm::none_t;
        // using dtype_t    = nm::none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using result_t   = meta::get_underlying_array_type_t<view_t>;
        using expected_t = nmtools_tuple<const array_t&,size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}

TEST_CASE("get_element_type" * doctest::test_suite("view::mean"))
{
    // runtime axis
    {
        using array_t    = int[3][2];
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using element_t  = meta::get_element_type_t<view_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, expected_t );
    }
    {
        using array_t    = nmtools_array<nmtools_array<int,2>,3>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using element_t  = meta::get_element_type_t<view_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,3,2>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using element_t  = meta::get_element_type_t<view_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, expected_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,6,2>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using element_t  = meta::get_element_type_t<view_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using axis_t     = size_t;
        // using dtype_t    = none_t;
        // using keepdims_t = false_type;
        using view_t     = decltype(view::mean(declval(array_t),declval(axis_t)));
        using element_t  = meta::get_element_type_t<view_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, expected_t );
    }
}