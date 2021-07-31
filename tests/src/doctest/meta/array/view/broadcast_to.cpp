#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("broadcast_to")
    {
        {
            using shape_t = std::array<size_t,2>;
            using origin_axes_t = na::hybrid_ndarray<size_t,2,1>;
            using view_t = view::decorator_t<view::broadcast_to_t, int[3][3], shape_t, origin_axes_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
            NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_dim_v<view_t>, 2 );
        }
        {
            using shape_t = std::array<size_t,2>;
            using origin_axes_t = na::hybrid_ndarray<size_t,2,1>;
            using view_t = view::decorator_t<view::broadcast_to_t, int, shape_t, origin_axes_t >;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
            NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_dim_v<view_t>, 2 );
        }
    }
}