#include "nmtools/array/view/concatenate.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
using namespace nm::literals;

TEST_CASE("eval(concatenate)" * doctest::test_suite("eval"))
{
    // None axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[2][1];
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<int,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,1>,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<int,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::fixed_ndarray<int,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = na::hybrid_ndarray<int,4,2>;
        using rhs_t  = na::hybrid_ndarray<int,2,2>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::hybrid_ndarray<int,6,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = na::dynamic_ndarray<int>;
        using rhs_t  = na::dynamic_ndarray<int>;
        using axis_t = nm::none_t;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // runtime axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_dynamic_ndarray_v<view_t> );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,2,1>;
        using axis_t = int;
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // compile-time axis
    {
        using lhs_t  = int[2][2];
        using rhs_t  = int[1][2];
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<std::array<int,2>,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = std::array<std::array<int,2>,2>;
        using rhs_t  = std::array<std::array<int,2>,1>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = std::array<std::array<int,2>,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t  = na::fixed_ndarray<int,2,2>;
        using rhs_t  = na::fixed_ndarray<int,1,2>;
        using axis_t = decltype(0_ct);
        using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::fixed_ndarray<int,3,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}