#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/arange.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(arange)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::arange_t, int, int, int, int >;
        using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using start_t = meta::remove_cvref_t<decltype(0_ct)>;
        using stop_t  = meta::remove_cvref_t<decltype(4_ct)>;
        using view_t  = view::decorator_t< view::arange_t, start_t, stop_t, none_t, int>;
        using eval_t  = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
        using expected_t = na::fixed_ndarray<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
    }
}