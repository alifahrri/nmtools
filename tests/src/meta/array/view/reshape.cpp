#include "nmtools/array/view/reshape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    // shape is known at compile time
    {
        using array_t = int[2][3][2];
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t = na::fixed_ndarray<int,2,3,2>;
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t = na::hybrid_ndarray<int,12,3>;
        using shape_t = std::tuple<meta::ct<12>>;
        using view_t  = view::reshape_t<array_t,shape_t>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}

TEST_CASE("reshape" * doctest::test_suite("view"))
{
    SUBCASE("fixed_dim")
    {
        {
            using array_t = int[2][3][2];
            using shape_t = std::tuple<meta::ct<12>>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using shape_t = std::tuple<meta::ct<12>>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using shape_t = std::tuple<meta::ct<12>>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using shape_t = std::tuple<meta::ct<12>>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        {
            using array_t = int[2][3][2];
            using shape_t = nmtools_array<int,1>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using shape_t = nmtools_array<int,1>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using shape_t = nmtools_array<int,1>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using shape_t = nmtools_array<int,1>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }

        // Not fixed dim
        {
            using array_t = int[2][3][2];
            using shape_t = std::vector<int>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using shape_t = std::vector<int>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using shape_t = std::vector<int>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using shape_t = std::vector<int>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
    }

    SUBCASE("hybrid_ndarray_max_size")
    {
        {
            using array_t = int[2][3][2];
            using shape_t = std::array<int,3>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            constexpr auto max_size = meta::hybrid_ndarray_max_size_v<view_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index, decltype(max_size) );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3,2>;
            using shape_t = std::array<int,3>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            constexpr auto max_size = meta::hybrid_ndarray_max_size_v<view_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index, decltype(max_size) );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using shape_t = std::array<int,3>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            constexpr auto max_size = meta::hybrid_ndarray_max_size_v<view_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_index, decltype(max_size) );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using shape_t = std::array<int,3>;
            using view_t  = view::decorator_t<view::reshape_t,array_t,shape_t>;
            constexpr auto max_size = meta::hybrid_ndarray_max_size_v<view_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fail, decltype(max_size) );
        }
    }
}