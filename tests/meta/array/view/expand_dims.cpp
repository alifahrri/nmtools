#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/view/expand_dims.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
using namespace nm::literals;

template <typename result_t, typename expect_t>
static constexpr auto check_equal_if_not_fail(const result_t& result, const expect_t& expect)
{
    // NOTE: Outside a template, a discarded statement is fully checked. 
    if constexpr (!meta::is_fail_v<result_t>) {
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("expand_dims(case1)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(0_ct);

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("expand_dims(case2)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = decltype(nmtools_tuple{0_ct,2_ct});

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("expand_dims(case3)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_array<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("expand_dims(case4)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = na::static_vector<size_t,2>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("expand_dims(case5)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = nmtools_list<size_t>;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,1,3,2});
            check_equal_if_not_fail(fixed_dim, 5);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 5);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}

TEST_CASE("expand_dims(case6)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }

    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;
        using axis_type   = size_t;

        using view_type = view::decorator_t< view::expand_dims_t, array_type, axis_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{1,2,3,2});
            check_equal_if_not_fail(fixed_dim, 4);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 4);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}