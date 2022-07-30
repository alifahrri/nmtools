#include "nmtools/array/view/var.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define declval(type) std::declval<type>()

// TODO: fix eval for more generic array
TEST_CASE("eval(var)" * doctest::test_suite("eval") * doctest::may_fail())
{
    // none axis
    {
        using array_t = int[2][3][2];
        using axis_t  = nm::none_t;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using eval_t  = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        using axis_t  = nm::none_t;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using eval_t  = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t = na::fixed_ndarray<int,2,3,2>;
        using axis_t  = nm::none_t;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using eval_t  = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t = na::hybrid_ndarray<int,12,3>;
        using axis_t  = nm::none_t;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using eval_t  = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = float;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // reduce on axis 1
    {
        using array_t = int[2][3][2];
        using axis_t  = meta::ct<1>;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using eval_t  = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = nmtools_array<nmtools_array<float,2>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}