#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("flatten")
    {
        {
            using view_t = view::decorator_t< view::flatten_t, int[2][3][2] >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, std::array<int,3> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::fixed_ndarray<int,2,3,2> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::dynamic_ndarray<int> >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::hybrid_ndarray<int,12,3> >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("flatten")
    {
        {
            using view_t = view::decorator_t< view::flatten_t, int[2][3][2] >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, std::array<int,3> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::fixed_ndarray<int,2,3,2> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::hybrid_ndarray<int,12,3> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using view_t = view::decorator_t< view::flatten_t, na::dynamic_ndarray<int> >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
    }
}