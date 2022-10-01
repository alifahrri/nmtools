#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/repeat.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_shape" * doctest::test_suite("view"))
{
    SUBCASE("repeat")
    {
        // args known at compile-time
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = nmtools_array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }

        // repeats is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = nmtools_array<int,3>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = int;
            using axis_t    = nm::none_t;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }

        // repeats is compile-time value and axis is runtime value
        {
            using array_t   = int[2][2];
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = nmtools_array<int,3>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::fixed_ndarray<int,4,2>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
        }
        {
            using array_t   = na::dynamic_ndarray<int>;
            using repeats_t = meta::ct<3>;
            using axis_t    = int;
            using view_t    = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_t );
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
            using array_t   = nmtools_array<int,3>;
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
            using array_t   = nmtools_array<int,3>;
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
            using array_t   = nmtools_array<int,3>;
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

#define declval(type) meta::declval<type>()

using namespace nm::literals;

TEST_CASE("repeat(case1)" * doctest::test_suite("meta::repeat"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 1);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        // using None axis will flatten first
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = nm::none_t;
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("repeat(case2)" * doctest::test_suite("meta::repeat"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{3,2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{6,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(3_ct);
        using axis_type    = decltype(0_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("repeat(case3)" * doctest::test_suite("meta::repeat"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,3,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 18);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 18);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,3,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 18);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 18);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,4,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 16);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 16);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 1);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        
        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using repeats_type = decltype(nmtools_tuple{2_ct,1_ct});
        using axis_type    = decltype(1_ct);
        using view_type    = decltype(view::repeat(declval(array_type),declval(repeats_type),declval(axis_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );
        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{36}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 36);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 36);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}