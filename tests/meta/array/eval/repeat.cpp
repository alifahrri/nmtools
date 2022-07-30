#include "nmtools/array/view/repeat.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("eval(repeat)" * doctest::test_suite("eval"))
{
    {
        using array_t    = int[2][2];
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = nmtools_array<int,12>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<int,3>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = nmtools_array<int,9>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,2,2>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::fixed_ndarray<int,12>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // repeats is runtime value
    {
        using array_t    = int[2][2];
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        // TODO: support dynamic-size fixed-dim
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<int,3>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,4,2>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        using view_t     = view::decorator_t< view::repeat_t, array_t, repeats_t, axis_t >;
        using eval_t     = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}