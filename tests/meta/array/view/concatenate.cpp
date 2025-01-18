#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/view/concatenate.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
using namespace nm::literals;

TEST_CASE("get_element_type" * doctest::test_suite("view::concatenate"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = na::hybrid_ndarray<int,4,2>;
        using rhs_t  = na::hybrid_ndarray<int,2,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }

    // runtime axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }

    // compile-time axis but incompatible shape
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using element_t = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
    }
}

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view::concatenate"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::hybrid_ndarray<int,4,2>;
        using rhs_t  = na::hybrid_ndarray<int,2,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // runtime axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }

    // compile-time axis but incompatible shape
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}

TEST_CASE("is_dynamic_ndarray" * doctest::test_suite("view::concatenate"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::hybrid_ndarray<int,4,2>;
        using rhs_t  = na::hybrid_ndarray<int,2,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_t );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = nmtools_list<int>;
        using rhs_t  = nmtools_list<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }

    // runtime axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
}

TEST_CASE("fixed_shape" * doctest::test_suite("view::concatenate"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        [[maybe_unused]] constexpr auto shape = meta::fixed_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, nmtools_array{6} );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        [[maybe_unused]] constexpr auto shape = meta::fixed_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, nmtools_array{6} );
    }
    {
        using lhs_t = na::fixed_ndarray<int,2,2>;
        using rhs_t = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape = meta::fixed_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, nmtools_array{6} );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_shape_v<view_t>;
        constexpr auto expected = nmtools_array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using lhs_t  = nmtools_array<nmtools_array<int,2>,2>;
        using rhs_t  = nmtools_array<nmtools_array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_shape_v<view_t>;
        constexpr auto expected = nmtools_array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_shape_v<view_t>;
        constexpr auto expected = nmtools_array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
}

TEST_CASE("concatenate(case1)" * doctest::test_suite("meta::concatenate"))
{
    // None axis
    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = nmtools_array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = nmtools_array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs buffers are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed-shape, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = nmtools_list<size_t>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = nmtools_list<size_t>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs buffer are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = na::static_vector<size_t,6>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = na::static_vector<size_t,6>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = na::static_vector<float,12>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = na::static_vector<float,12>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = na::static_vector<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = na::static_vector<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        // should be fixed dim because axis is none
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = na::static_vector<float,12>;
        using left_shape_type   = na::static_vector<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = na::static_vector<float,12>;
        using right_shape_type  = na::static_vector<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = nmtools_list<size_t>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = nmtools_list<size_t>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        // is fixed dim because none axis flatten then concat
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        // should be bounded dim because fixed dim
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using left_buffer_type  = boost::array<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::array<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        static_assert( meta::is_fixed_size_v<left_array_type> );
        static_assert( meta::is_constant_index_v<decltype(nmtools::size<true>(meta::declval<left_array_type>()))> );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = boost::container::static_vector<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::container::static_vector<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = boost::container::small_vector<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::container::small_vector<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = nm::none_t;

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{24}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("concatenate(case2)" * doctest::test_suite("meta::concatenate"))
{
    // compile-time axis
    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = nmtools_array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = nmtools_array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // not a fixed shape because shape is runtime
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // should be fixed size because buffer is fixed size
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{4,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed-shape, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{4,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = nmtools_list<size_t>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = nmtools_list<size_t>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_array<float,12>;
        using left_shape_type   = na::static_vector<size_t,6>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_array<float,12>;
        using right_shape_type  = na::static_vector<size_t,6>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = na::static_vector<float,12>;
        using left_shape_type   = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = na::static_vector<float,12>;
        using right_shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{4,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = na::static_vector<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = na::static_vector<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
        }
    }

    {
        using left_buffer_type  = na::static_vector<float,12>;
        using left_shape_type   = na::static_vector<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = na::static_vector<float,12>;
        using right_shape_type  = na::static_vector<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = nmtools_list<float>;
        using left_shape_type   = nmtools_list<size_t>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = nmtools_list<float>;
        using right_shape_type  = nmtools_list<size_t>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using left_buffer_type  = boost::array<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::array<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = boost::container::static_vector<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::container::static_vector<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }

    {
        using left_buffer_type  = boost::container::small_vector<float,12>;
        using left_shape_type   = boost::array<size_t,3>;
        using left_array_type   = na::ndarray_t<left_buffer_type,left_shape_type>;
        using right_buffer_type = boost::container::small_vector<float,12>;
        using right_shape_type  = boost::array<size_t,3>;
        using right_array_type  = na::ndarray_t<right_buffer_type,right_shape_type>;
        using axis_type         = decltype(0_ct);

        using view_type = view::decorator_t< view::concatenate_t, left_array_type, right_array_type, axis_type >;
        // NOTE: should be fixed shape because both lhs & rhs are fixed, and axis is None (means flattened)
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 24);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 24);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}