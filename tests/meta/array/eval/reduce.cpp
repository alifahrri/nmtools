#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(reduce)" * doctest::test_suite("eval"))
{
    SUBCASE("add")
    {
        {
            using view_t = view::decorator_t< view::reduce_t, view::add_t<>, int[2][3], none_t, none_t, none_t>;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = int;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::reduce_t, view::add_t<>, int[2][3], int, none_t, none_t>;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::hybrid_ndarray<int,6,1>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::reduce_t, view::add_t<>, na::hybrid_ndarray<int,6,2>, none_t, none_t, none_t >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = int;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::reduce_t, view::add_t<>, na::hybrid_ndarray<int,6,2>, int, none_t, none_t >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::hybrid_ndarray<int,6,1>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }

        // compile-time axis
        {
            using array_t = int[2][3];
            using axis_t  = decltype(0_ct);
            using view_t  = view::decorator_t< view::reduce_t, view::add_t<>, array_t, axis_t, none_t, none_t>;
            using eval_t  = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = std::array<int,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using array_t = std::array<std::array<int,3>,2>;
            using axis_t  = decltype(0_ct);
            using view_t  = view::decorator_t< view::reduce_t, view::add_t<>, array_t, axis_t, none_t, none_t>;
            using eval_t  = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = std::array<int,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using array_t = na::fixed_ndarray<int,2,3>;
            using axis_t  = decltype(0_ct);
            using view_t  = view::decorator_t< view::reduce_t, view::add_t<>, array_t, axis_t, none_t, none_t>;
            using eval_t  = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::fixed_ndarray<int,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,6,2>;
            using axis_t  = decltype(0_ct);
            using view_t  = view::decorator_t< view::reduce_t, view::add_t<>, array_t, axis_t, none_t, none_t >;
            using eval_t  = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::hybrid_ndarray<int,6,1>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using array_t = na::dynamic_ndarray<int>;
            using axis_t  = decltype(0_ct);
            using view_t  = view::decorator_t< view::reduce_t, view::add_t<>, array_t, axis_t, none_t, none_t >;
            using eval_t  = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::dynamic_ndarray<int>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
    }
}