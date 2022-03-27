#include "nmtools/array/view/take.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    {
        using array_t   = int[2][3][2];
        using indices_t = std::tuple<meta::ct<2>,meta::ct<2>>;
        using axis_t    = meta::ct<1>;
        using view_t    = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, view_t );
    }
    {
        using array_t   = na::dynamic_ndarray<int>;
        using indices_t = std::tuple<meta::ct<2>,meta::ct<2>>;
        using axis_t    = meta::ct<1>;
        using view_t    = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
    }
}