#include "nmtools/array/view/decorator.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/view/atleast_1d.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"
#include "nmtools/array/view/where.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/view/flip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nmtools::literals;

TEST_CASE("get_underlying_array_type(ufunc)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t  = view::decorator_t< view::ufunc_t, view::sin_t, std::vector<int> >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        // the underlying array may be ptr to allow copy
        using expected_t = std::tuple<const std::vector<int>*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using shape_t = decltype(std::tuple{3_ct,3_ct});
        using free_axes_t = na::hybrid_ndarray<size_t, 2, 1>;
        using view_t = view::decorator_t< view::ufunc_t, view::add_t<>,
            view::decorator_t< view::broadcast_to_t, int [3][3], shape_t , free_axes_t >,
            view::decorator_t< view::broadcast_to_t, int [3], shape_t , free_axes_t >
        >;
        using array_t = meta::get_underlying_array_type_t< view_t >;
        using expected_t = std::tuple<const int(&)[3][3], const int(&)[3]>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using shape_t = decltype(std::tuple{3_ct,3_ct});
        using free_axes_t = na::hybrid_ndarray<size_t, 2, 1>;
        using view_t = view::decorator_t< view::ufunc_t, view::add_t<>,
            view::decorator_t< view::broadcast_to_t, int [3][3], shape_t , free_axes_t >,
            view::decorator_t< view::broadcast_to_t, int, shape_t , free_axes_t >
        >;
        using array_t = meta::get_underlying_array_type_t< view_t >;
        // based on new (default) policy, bounded array is taken as const ref while scalar is copied
        using expected_t = std::tuple<const int(&)[3][3], const int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(outer)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t = view::decorator_t<view::outer_t, view::add_t<>, int [2][3], int [3]>;
        using array_t = meta::get_underlying_array_type_t< view_t >;
        using expected_t = std::tuple<const int(&)[2][3], const int(&)[3]>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(atleast_1d)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t  = view::decorator_t< view::atleast_1d_t, int >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = const int;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using view_t  = view::decorator_t< view::atleast_1d_t, std::vector<int> >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = const std::vector<int>*; // ptr because now view take ptr when possible to allow copy
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(broadcast_to)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using shape_t = decltype(std::tuple{3_ct,3_ct});
        using free_axes_t = na::hybrid_ndarray<size_t, 2, 1> ;
        using view_t = view::decorator_t< view::broadcast_to_t, int [3], shape_t , free_axes_t >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = const int(&)[3];
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(flip)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t  = view::decorator_t< view::flip_t, std::vector<int>, nm::none_t >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = const std::vector<int>&;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::flip_t, na::fixed_ndarray<int,2,2,2>, nm::none_t >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = const na::fixed_ndarray<int,2,2,2>&;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(clip)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t = view::decorator_t< view::ufunc_t, view::clip_t,
            view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,6,2>,  std::array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >,
            view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,12,3>, std::array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >,
            view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,1,1>,  std::array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >
        >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = std::tuple<const na::hybrid_ndarray<int,6,2>*, const na::hybrid_ndarray<int,12,3>*, const na::hybrid_ndarray<int,1,1>*>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        using a0_t = meta::remove_cvref_pointer_t<meta::at_t<array_t,0>>;
        static_assert( meta::is_hybrid_ndarray_v<a0_t> );
        using a1_t = meta::remove_cvref_pointer_t<meta::at_t<array_t,1>>;
        static_assert( meta::is_hybrid_ndarray_v<a1_t> );
        using a2_t = meta::remove_cvref_pointer_t<meta::at_t<array_t,2>>;
        static_assert( meta::is_hybrid_ndarray_v<a2_t> );
    }
    {
        using shape_t = std::tuple<std::integral_constant<size_t, 3>, std::integral_constant<size_t, 2> >;
        using origin_axes_t = nmtools::array::hybrid_ndarray<size_t, 2, 1>;
        using view_t = view::decorator_t< view::ufunc_t, view::clip_t,
            view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<float,3,2>, shape_t, origin_axes_t >,
            view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<float,2>, shape_t, origin_axes_t >,
            view::decorator_t< view::broadcast_to_t, float, shape_t, origin_axes_t >
        >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = std::tuple<const na::fixed_ndarray<float,3,2>*, const na::fixed_ndarray<float,2>*, const float>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}

TEST_CASE("get_underlying_array_type(where)" * doctest::test_suite("get_underlying_array_type"))
{
    {
        using view_t = view::decorator_t<
            view::where_t, int[3], int[3], int[3]
        >;
        using array_t = meta::get_underlying_array_type_t<view_t>;
        using expected_t = std::tuple<const int(&)[3],const int(&)[3],const int(&)[3]>;
        NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
    }
}