#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

#define declval(type) std::declval<type>()

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view::reduce"))
{
    // reduce add, as needed by mean view
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = std::array<std::array<int,2>,3>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}

TEST_CASE("fixed_ndarray_shape" * doctest::test_suite("view::reduce"))
{
    // reduce add, as needed by mean view
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = std::array<std::array<int,2>,3>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        constexpr auto shape = meta::fixed_ndarray_shape_v<view_t>;
        constexpr auto expected = std::array{2ul};
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view::reduce"))
{
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = int[3][2];
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::fixed_ndarray<int,3,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = std::array<std::array<int,2>,3>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::hybrid_ndarray<int,6,2>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
    }
    {
        using op_t    = view::add_t<none_t, none_t, float, void>;
        using array_t = na::dynamic_ndarray<int>;
        using axis_t  = decltype(0_ct);
        using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, axis_t, none_t, std::false_type >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
    }
}