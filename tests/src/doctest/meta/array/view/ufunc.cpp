#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("ufunc")
    {
        using array_t = na::dynamic_ndarray<int>;
        using view_t  = view::decorator_t< view::ufunc_t, view::sin_t, array_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        static_assert( !meta::is_fixed_dim_ndarray_v<array_t> );
        static_assert( !meta::is_fixed_size_ndarray_v<array_t> );
        static_assert( !meta::is_fixed_size_ndarray_v<view_t> );
    }
}