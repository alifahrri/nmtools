#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/meta.hpp"
#include "nmtools/array/view/zeros.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

template <typename result_t, typename expect_t>
static constexpr auto check_equal_if_not_fail(const result_t& result, const expect_t& expect)
{
    // NOTE: Outside a template, a discarded statement is fully checked. 
    if constexpr (!meta::is_fail_v<result_t>) {
        NMTOOLS_ASSERT_EQUAL( result, expect );
    }
}

TEST_CASE("zeros(case1)" * doctest::test_suite("meta::zeros"))
{
    {
        using shape_type = nmtools_array<size_t,3>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = nmtools_list<size_t>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = na::static_vector<size_t,6>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 6);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using shape_type = boost::array<size_t,3>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = boost::container::static_vector<size_t,3>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
        static_assert( meta::is_ndarray_v<view_type> );
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = boost::container::small_vector<size_t,3>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
    {
        using shape_type = boost::container::vector<size_t>;
        using value_type = float;
        using view_type  = view::decorator_t< view::zeros_t, shape_type, value_type >;
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
            check_equal_if_not_fail(fixed_shape, nmtools_array{2,3,2});
            check_equal_if_not_fail(fixed_dim, 3);
            check_equal_if_not_fail(fixed_size, 12);
            check_equal_if_not_fail(bounded_dim, 3);
            check_equal_if_not_fail(bounded_size, 12);
        }
    }
#endif
}