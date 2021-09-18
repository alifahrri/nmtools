#include "nmtools/array/view/pad.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

TEST_CASE("is_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("pad")
    {
        {
            using array_t     = int[3][2];
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using array_t     = float[3][2];
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using array_t     = std::array<std::array<int,2>,3>;
            using pad_width_t = std::array<int,4>;
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using array_t     = na::fixed_ndarray<int,3,2>;
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using array_t     = na::hybrid_ndarray<int,3,2>;
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        {
            using array_t     = na::dynamic_ndarray<int>;
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
    }
}

TEST_CASE("get_element_type" * doctest::test_suite("view"))
{
    SUBCASE("pad")
    {
        {
            using array_t     = int[3][2];
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            using element_t = meta::get_element_type_t<view_t>;
            NMTOOLS_STATIC_CHECK_IS_SAME( element_t, int );
        }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("pad")
    {
        {
            using array_t     = int[3][2];
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
    }
}

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    using namespace nmtools::literals;
    SUBCASE("pad")
    {
        {
            using array_t = int[3][2];
            using pad_width_t = decltype(std::tuple{1_ct,2_ct,0_ct,0_ct});
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
    }
}

TEST_CASE("fixed_dim" * doctest::test_suite("view"))
{
    SUBCASE("pad")
    {
        {
            using array_t     = int[3][2];
            using pad_width_t = int[4];
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            constexpr auto dim = meta::fixed_dim_v<view_t>;
            NMTOOLS_STATIC_ASSERT_EQUAL( dim, 2 );
        }
    }
}