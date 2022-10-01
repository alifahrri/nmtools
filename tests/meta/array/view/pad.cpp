#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/view/pad.hpp"
#include "nmtools/array/ndarray.hpp"
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
            using array_t     = nmtools_array<nmtools_array<int,2>,3>;
            using pad_width_t = nmtools_array<int,4>;
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

TEST_CASE("is_fixed_shape" * doctest::test_suite("view"))
{
    using namespace nmtools::literals;
    SUBCASE("pad")
    {
        {
            using array_t = int[3][2];
            using pad_width_t = decltype(nmtools_tuple{1_ct,2_ct,0_ct,0_ct});
            using value_t = float;
            using view_t  = view::decorator_t< view::pad_t, array_t, pad_width_t, value_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_t );
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

#define declval(type) meta::declval<type>()

using namespace nm::literals;

TEST_CASE("pad(case1)" * doctest::test_suite("meta::pad"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, ((nmtools_array{2,7,2})));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, ((nmtools_array{2,7,2})));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = decltype(nmtools_tuple{0_ct,2_ct,0_ct,0_ct,2_ct,0_ct});
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("pad(case2)" * doctest::test_suite("meta::pad"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 6);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // NOTE: can't know the fixed size because we don't know the src shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using pad_width_type = nmtools_array<size_t,6>;
        using view_type = decltype(view::pad(declval(array_type),declval(pad_width_type)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,7,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 28);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 28);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

#if 0
TEST_CASE("pad(case1)" * doctest::test_suite("meta::pad"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,6>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
    }
#endif // NMTOOLS_ENABLE_BOOST
}
#endif