#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/atleast_2d.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(atleast_2d)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::atleast_2d_t, int >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::fixed_ndarray<int,1,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_2d_t, std::vector<int> >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_2d_t, std::array<int,3> >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = std::array<std::array<int,3>,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        using array_t = std::array<int,3>;
    }
    {
        using view_t = view::decorator_t< view::atleast_2d_t, int[3] >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = std::array<std::array<int,3>,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_2d_t, na::fixed_ndarray<int,3> >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::fixed_ndarray<int,1,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}