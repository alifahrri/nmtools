#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define declval(type) meta::declval<type>()

using namespace nm::literals;

TEST_CASE("squeeze(case1)" * doctest::test_suite("meta::squeeze"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type   = decltype(view::squeeze(declval(array_type)));

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
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    // {
    //     using buffer_type = boost::array<float,12>;
    //     using shape_type  = boost::container::small_vector<size_t,3>;
    //     using array_type  = na::ndarray_t<buffer_type,shape_type>;

    //     using view_type   = decltype(view::squeeze(declval(array_type)));

    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
    //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

    //     {
    //         constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
    //         constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
    //         constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
    //         constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
    //         constexpr auto bounded_size = meta::bounded_size_v<view_type>;
    //         NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,6}));
    //         NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 2);
    //         NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
    //         NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
    //         NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
    //     }
    // }
#endif // NMTOOLS_ENABLE_BOOST
}
