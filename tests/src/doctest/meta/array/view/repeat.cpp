#include "nmtools/array/view/repeat.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("repeat")
    {
        // args known at compile-time
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }

        // repeats is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }

        // repeats is compile-time value and axis is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("repeat")
    {
        // args known at compile-time
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        // repeats is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        // repeats is compile-time value and axis is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = std::array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
    }
}