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

#define declval(type) std::declval<type>()

using nmtools_tuple;

#ifdef NMTOOLS_DISABLE_STL
using nmtools::meta::false_type;
using nmtools::meta::integral_constant;
#else
using std::false_type;
using std::integral_constant;
#endif

TEST_CASE("is_fixed_shape" * doctest::test_suite("view"))
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
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = nmtools_array<nmtools_array<int,2>,3>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::fixed_ndarray<int,3,2>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::hybrid_ndarray<int,6,2>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, broadcasted_t );
        }
        {
            using op_t    = view::add_t<none_t, none_t, float, void>;
            using array_t = na::dynamic_ndarray<int>;
            using view_t  = view::decorator_t<view::reduce_t, op_t, array_t, decltype(0_ct), none_t, false_type >;
            using shape_t = nmtools_tuple<integral_constant<long unsigned int, 2> >;
            using broadcasted_t = decltype(view::broadcast_to(declval(view_t),declval(shape_t)));
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, broadcasted_t );
        }
    }
}