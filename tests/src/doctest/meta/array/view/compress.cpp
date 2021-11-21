#include "nmtools/array/view/compress.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view::compress"))
{
    // None axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // None axis, constant condition
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }

    // constant condition, constant axis
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }

    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}

#if NMTOOLS_TESTING_HAS_CONSTEXPR_MATH
TEST_CASE("fixed_ndarray_shape" * doctest::test_suite("view::compress"))
{
    // constant condition, None axis
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        static_assert( meta::is_constant_index_array_v<condition_t> );
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul};
        NMTOOLS_STATIC_ASSERT_CLOSE( shape, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul};
        NMTOOLS_STATIC_ASSERT_CLOSE( shape, expected );
    }

    // constant condition, constant axis
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul,2ul};
        NMTOOLS_STATIC_ASSERT_CLOSE( shape, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul,2ul};
        NMTOOLS_STATIC_ASSERT_CLOSE( shape, expected );
    }
}
#endif // NMTOOLS_TESTING_HAS_CONSTEXPR_MATH

TEST_CASE("is_hybrid_ndarray" * doctest::test_suite("view::compress"))
{
    // None axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }

    // None axis, constant condition
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_hybrid_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, view_t );
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view::compress"))
{
    // None axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }

    // None axis, constant condition
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }

    // constant condition, constant axis
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }

    // runtime axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using condition_t = bool[5];
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
    }
}

TEST_CASE("fixed_dim" * doctest::test_suite("view::compress"))
{
    // None axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = bool[5];
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }

    // None axis, constant condition
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = nm::none_t;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 1;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }

    // constant condition, constant axis
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 2;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = decltype(std::tuple{nm::True,nm::False,nm::True});
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 2;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }

    // runtime axis
    {
        using condition_t = bool[5];
        using array_t = int[3][2];
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 2;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = bool[5];
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 2;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
    {
        using condition_t = bool[5];
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = int;
        using view_t  = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        constexpr auto dim = meta::fixed_dim_v<view_t>;
        constexpr auto expected = 2;
        NMTOOLS_STATIC_ASSERT_EQUAL( dim, expected );
    }
}