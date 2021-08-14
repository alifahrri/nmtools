#include "nmtools/array/view/concatenate.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
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
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,1>,2>;
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
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
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
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
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
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
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
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
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
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
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
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::hybrid_ndarray<int,4,2>;
        using rhs_t  = na::hybrid_ndarray<int,2,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = std::vector<int>;
        using rhs_t  = std::vector<int>;
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
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
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
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, view_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, view_t );
    }
}

TEST_CASE("fixed_ndarray_shape" * doctest::test_suite("view::concatenate"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, std::array{6} );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, std::array{6} );
    }
    {
        using lhs_t = na::fixed_ndarray<int,2,2>;
        using rhs_t = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, std::array{6} );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        constexpr auto shape    = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{3,2};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
}