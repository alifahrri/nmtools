#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;
using namespace nm::literals;

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("broadcast_to")
    {
        {
            using shape_t = nmtools_array<size_t,2>;
            using origin_axes_t = na::hybrid_ndarray<size_t,2,1>;
            using view_t = view::decorator_t<view::broadcast_to_t, int[3][3], shape_t, origin_axes_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
            NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_dim_v<view_t>, 2 );
        }
        {
            using shape_t = nmtools_array<size_t,2>;
            using origin_axes_t = na::hybrid_ndarray<size_t,2,1>;
            using view_t = view::decorator_t<view::broadcast_to_t, int, shape_t, origin_axes_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
            NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_dim_v<view_t>, 2 );
        }
    }
}

#define declval(type) std::declval<type>()

using nmtools_tuple;

TEST_CASE("broadcast_arrays" * doctest::test_suite("view"))
{
    using lhs_t = int[2][3][2];
    using rhs_t = int;
    static_assert( meta::is_constant_index_v<decltype(2_ct,3_ct,2_ct)> );
    static_assert( meta::is_fixed_index_array_v<nmtools_array<bool,3>> );
    using broadcasted_t = decltype(view::broadcast_arrays(declval(lhs_t),declval(rhs_t)));
    constexpr auto len  = meta::len_v<broadcasted_t>;
    // static_assert( meta::len_v<broadcasted_t> == 2 );
    NMTOOLS_STATIC_ASSERT_EQUAL( len, 2 );
    using blhs_t = meta::at_t<broadcasted_t,0>;
    using brhs_t = meta::at_t<broadcasted_t,1>;
    using free_axes_t = na::hybrid_ndarray<size_t,3ul,1ul>;
    using shape_t = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
    using expected_lhs_t = view::decorator_t<view::broadcast_to_t, lhs_t, shape_t, free_axes_t>;
    using expected_rhs_t = view::decorator_t<view::broadcast_to_t, rhs_t, shape_t, none_t>;
    NMTOOLS_STATIC_CHECK_IS_SAME( blhs_t, expected_lhs_t );
    NMTOOLS_STATIC_CHECK_IS_SAME( brhs_t, expected_rhs_t );
}

#ifdef NMTOOLS_DISABLE_STL
using nmtools::meta::false_type;
using nmtools::meta::integral_constant;
#else
using std::false_type;
using std::integral_constant;
#endif

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("broadcast_to")
    {
        // reduce add, as needed by mean view
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = int[3][2];
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = nmtools_array<nmtools_array<int,2>,3>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::fixed_ndarray<int,3,2>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::hybrid_ndarray<int,6,2>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::dynamic_ndarray<int>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, broadcasted_t );
        }
    }
}