#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/atleast_1d.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(atleast_1d)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::atleast_1d_t, int >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::fixed_ndarray<int,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, std::vector<int> >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = std::vector<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, std::array<int,3> >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using view_t = view::decorator_t< view::atleast_1d_t, int[3] >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
    }
}