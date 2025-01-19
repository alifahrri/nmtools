#include "nmtools/array/matmul.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/dynamic.hpp"
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
            using lhs_t  = nmtools_array<nmtools_array<int,4>,3>;
            using rhs_t  = nmtools_array<nmtools_array<int,3>,4>;
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

TEST_CASE("is_fixed_shape" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t  = int[3][4];
            using rhs_t  = int[4][3];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = nmtools_array<nmtools_array<int,4>,3>;
            using rhs_t  = nmtools_array<nmtools_array<int,3>,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,3,4>;
            using rhs_t  = na::fixed_ndarray<int,4,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }

        // batched
        {
            using lhs_t  = int[4][3];
            using rhs_t  = int[2][3][2];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }

        // batched
        {
            using lhs_t  = int[1][4][3];
            using rhs_t  = int[3][4];
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,1,4,3>;
            using rhs_t  = na::fixed_ndarray<int,3,4>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,3>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
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
            using lhs_t  = nmtools_array<nmtools_array<int,4>,3>;
            using rhs_t  = nmtools_array<nmtools_array<int,3>,4>;
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
            using lhs_t  = nmtools_array<nmtools_array<int,4>,3>;
            using rhs_t  = nmtools_array<nmtools_array<int,3>,4>;
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