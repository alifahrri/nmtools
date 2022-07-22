#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

// TODO: update/fix eval type deduction
TEST_CASE("tile" * doctest::test_suite("eval") * doctest::skip())
{
    {
        using view_t = view::decorator_t<
            view::tile_t, int[3], std::tuple<meta::ct<1>>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t<
            view::tile_t, int[3], std::tuple<meta::ct<1>,meta::ct<2>>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<std::array<int,6>,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t<
            view::tile_t, int[3], std::vector<int>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t<
            view::tile_t, std::vector<int>, std::tuple<meta::ct<1>,meta::ct<2>>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t<
            view::tile_t, na::fixed_ndarray<int,3>, std::tuple<meta::ct<1>,meta::ct<2>>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::fixed_ndarray<int,1,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}