#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/view/pooling.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nmtools::literals;

#define declval(type) meta::declval<type>()

#if 1
TEST_CASE("pooling(case1)" * doctest::test_suite("meta::pooling"))
{
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = nmtools_array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = na::static_vector<float,16>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,16>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,16>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::array<float,16>;
        using shape_type  = boost::container::small_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = decltype(nmtools_tuple{3_ct,3_ct});
        using stride      = decltype(nmtools_tuple{2_ct,2_ct});
        using ceil_mode   = decltype(nm::True);
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("pooling(case2)" * doctest::test_suite("meta::pooling"))
{
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = nmtools_array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        // should be fixed dim still, because kernel_size, stride, ceil_mode doesn't change dim of the resulting shape
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        // kernel_size, stride, ceil_mode may change dim of the resulting shape
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_array<float,16>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = na::static_vector<float,16>;
        using shape_type  = decltype(nmtools_tuple{1_ct,1_ct,4_ct,4_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,16>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,16>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
    {
        using buffer_type = boost::array<float,16>;
        using shape_type  = boost::container::small_vector<size_t,4>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using kernel_size = nmtools_array<size_t,2>;
        using stride      = nmtools_array<size_t,2>;
        using ceil_mode   = bool;
        using view_type   = decltype(view::avg_pool2d(declval(array_type),declval(kernel_size),declval(stride),declval(ceil_mode)));
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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{1,1,2,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 4);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 4);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}
#endif