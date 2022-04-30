// use has_include so we don't have to relies on cmake logic to look for boost
#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("is_fixed_shape(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, array_type );
    }
    {
        using array_type = ::boost::array<float,12>;
        constexpr auto fixed_shape = meta::fixed_shape_v<array_type>;
        using fixed_shape_t = decltype(fixed_shape);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index_array, fixed_shape_t );
        if constexpr (meta::is_index_array_v<fixed_shape_t>) {
            NMTOOLS_ASSERT_EQUAL( fixed_shape, (nmtools_array{12}) );
        }
    }
    {
        using array_type = ::boost::array<float,12>;
        constexpr auto fixed_shape = meta::fixed_shape_v<array_type>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index_array, decltype(fixed_shape)& );
    }

    {
        using array_type = ::boost::container::static_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, array_type );
    }
}

TEST_CASE("is_fixed_dim(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;    
        constexpr auto fixed_dim = meta::fixed_dim_v<array_type>;
        using fixed_dim_t = decltype(fixed_dim);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, fixed_dim_t );
        if constexpr (meta::is_num_v<fixed_dim_t>) {
            NMTOOLS_ASSERT_EQUAL( fixed_dim, 1 );
        }
    }
    {
        using array_type = ::boost::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, array_type );
    }
}

TEST_CASE("is_fixed_size(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        constexpr auto fixed_size = meta::fixed_size_v<array_type>;
        using fixed_size_t = decltype(fixed_size);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, fixed_size_t );
        if constexpr (meta::is_num_v<fixed_size_t>) {
            NMTOOLS_ASSERT_EQUAL( fixed_size, 12 );
        }
    }
    {
        using array_type = ::boost::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, array_type );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, array_type );
    }
}

TEST_CASE("bounded_dim(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        constexpr auto bounded_dim = meta::bounded_dim_v<array_type>;
        using bounded_dim_t = decltype(bounded_dim);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, bounded_dim_t );
        // static_assert( meta::is_num_v<bounded_dim_t> );
        if constexpr (meta::is_num_v<bounded_dim_t>) {
            NMTOOLS_ASSERT_EQUAL( bounded_dim, 1 );
        }
    }
    {
        using array_type = ::boost::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
    {
        // has max dim because is fixed dim
        using array_type = ::boost::container::small_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, array_type );
    }
}

TEST_CASE("bounded_size(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        constexpr auto bounded_size = meta::bounded_size_v<array_type>;
        using bounded_size_t = decltype(bounded_size);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, bounded_size_t );
        NMTOOLS_ASSERT_EQUAL( bounded_size, 12 );
    }
    {
        using array_type = ::boost::array<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, array_type );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, array_type );
    }
}

TEST_CASE("resize_dim(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        using result_t   = meta::resize_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_size(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, result_t );
        NMTOOLS_ASSERT_EQUAL( meta::fixed_size_v<result_t>, 2 );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        using result_t   = meta::resize_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_bounded_size(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, result_t );
        NMTOOLS_ASSERT_EQUAL( meta::bounded_size_v<result_t>, 2 );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        using result_t   = meta::resize_bounded_size_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

TEST_CASE("resize_bounded_dim(case1)" * doctest::test_suite("meta::boost"))
{
    {
        using array_type = ::boost::array<float,12>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::static_vector<float,12>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
    {
        using array_type = ::boost::container::small_vector<float,12>;
        using result_t   = meta::resize_bounded_dim_t<array_type,2>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, result_t );
    }
}

#endif