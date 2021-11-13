#include "nmtools/array/view/matmul.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

namespace nmtools 
{
    struct Foo {};

    inline constexpr auto foo = Foo {};
}

// static_assert( std::is_same_v<decltype(std::get<0>(std::declval<std::tuple<nm::elipsis_t,nm::elipsis_t>>())),nm::elipsis_t> );
// static_assert( std::is_same_v<decltype(std::get<0>(meta::declval<std::tuple<nm::elipsis_t,nm::elipsis_t>>())),nm::elipsis_t> );
// static_assert( std::is_same_v<decltype(nm::get<0>(meta::declval<std::tuple<nm::elipsis_t,nm::elipsis_t>>())),nm::elipsis_t> );
// static_assert( std::is_same_v<decltype(std::get<0>(std::declval<std::tuple<nm::Foo,nm::Foo>>())),nm::Foo> );

// static_assert( std::is_same_v<meta::expr::template_get<std::tuple<nm::elipsis_t,nm::elipsis_t>,meta::index_sequence<0>>,nm::elipsis_t> );
// static_assert( std::is_same_v<meta::expr::template_get<std::tuple<nm::Foo,nm::Foo>,meta::index_sequence<0>>,nm::elipsis_t> );

// static_assert( meta::has_template_get_v<std::tuple<int,int>,0> );
// static_assert( meta::has_template_get_v<const std::tuple<int,int>,0> );
// static_assert( meta::has_template_get_v<const std::tuple<int,int>&,0> );
// static_assert( meta::has_template_get_v<const std::tuple<std::array<int,1>,int>&,0> );
// static_assert( meta::has_template_get_v<std::tuple<nm::elipsis_t,nm::elipsis_t>,0> );
// static_assert( meta::has_template_get_v<std::tuple<const nm::elipsis_t&,const nm::elipsis_t&>,0> );
// static_assert( meta::has_template_get_v<const std::tuple<nm::elipsis_t,nm::elipsis_t>&,0> );
// static_assert( meta::has_template_get_v<std::tuple<nm::Foo,nm::Foo>,0> );
// static_assert( meta::has_template_get_v<std::tuple<decltype(nm::foo),decltype(nm::foo)>,0> );
// static_assert( meta::has_template_get_v<const std::tuple<nm::Foo,nm::Foo>&,0> );
// static_assert( meta::has_template_get_v<const std::tuple<decltype(nm::foo),decltype(nm::foo)>&,0> );

TEST_CASE("is_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = std::array<std::array<int,4>,3>;
            using rhs_t  = std::array<std::array<int,3>,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,3,4>;
            using rhs_t  = na::fixed_ndarray<int,4,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[4][3];
            using rhs_t  = int[2][3][2];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,1,4,3>;
            using rhs_t  = na::fixed_ndarray<int,3,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,3>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
    }
}

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = std::array<std::array<int,4>,3>;
            using rhs_t  = std::array<std::array<int,3>,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,3,4>;
            using rhs_t  = na::fixed_ndarray<int,4,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[4][3];
            using rhs_t  = int[2][3][2];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,1,4,3>;
            using rhs_t  = na::fixed_ndarray<int,3,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,3>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
}

TEST_CASE("get_element_type" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = std::array<std::array<int,4>,3>;
            using rhs_t  = std::array<std::array<int,3>,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,3,4>;
            using rhs_t  = na::fixed_ndarray<int,4,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }

        // batched
        {
            using lhs_t  = int[4][3];
            using rhs_t  = int[2][3][2];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }

        // batched
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,1,4,3>;
            using rhs_t  = na::fixed_ndarray<int,3,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,3>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using elem_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, int );
        }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = std::array<std::array<int,4>,3>;
            using rhs_t  = std::array<std::array<int,3>,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,3,4>;
            using rhs_t  = na::fixed_ndarray<int,4,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[4][3];
            using rhs_t  = int[2][3][2];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        // batched
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,1,4,3>;
            using rhs_t  = na::fixed_ndarray<int,3,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,3>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
    }
}

TEST_CASE("has_funcnd" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::matmul_t< lhs_t, rhs_t >;
            constexpr auto has_funcnd = meta::has_funcnd_v<view_t,size_t,size_t>;
            NMTOOLS_STATIC_ASSERT_EQUAL( has_funcnd, true );
        }
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::matmul_t< lhs_t, rhs_t >;
            constexpr auto has_funcnd = meta::has_funcnd_v<view_t,size_t,size_t,size_t>;
            NMTOOLS_STATIC_ASSERT_EQUAL( has_funcnd, true );
        }
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t<view::matmul_t, lhs_t, rhs_t >;
            constexpr auto has_funcnd = meta::has_funcnd_v<view_t,size_t,size_t,size_t>;
            NMTOOLS_STATIC_ASSERT_EQUAL( has_funcnd, true );
        }
    }
}