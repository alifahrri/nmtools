#include "nmtools/array/view/take.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("take" * doctest::test_suite("eval"))
{
    {
        using array_t    = int[2][3][2];
        using indices_t  = std::tuple<meta::ct<2>,meta::ct<1>>;
        using axis_t     = meta::ct<1>;
        using view_t     = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using eval_t     = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = std::array<std::array<std::array<int,2>,2>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = int[2][3][2];
        using indices_t  = std::tuple<meta::ct<2>,meta::ct<1>>;
        using axis_t     = int;
        using view_t     = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using eval_t     = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,2,3,2>;
        using indices_t  = std::tuple<meta::ct<2>,meta::ct<1>>;
        using axis_t     = meta::ct<1>;
        using view_t     = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using eval_t     = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = na::fixed_ndarray<int,2,2,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using indices_t  = std::tuple<meta::ct<2>,meta::ct<1>>;
        using axis_t     = meta::ct<1>;
        using view_t     = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using eval_t     = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::hybrid_ndarray<int,12,3>;
        using indices_t  = std::tuple<meta::ct<2>,meta::ct<1>>;
        using axis_t     = meta::ct<1>;
        using view_t     = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using eval_t     = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        // TODO: infer as hybrid_ndarray
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}