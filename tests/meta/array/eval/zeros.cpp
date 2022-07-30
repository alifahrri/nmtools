#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/zeros.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(zeros)" * doctest::test_suite("eval") * doctest::may_fail())
{
    {
        using view_t = view::decorator_t< view::zeros_t, nmtools_list<int>, float >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::dynamic_ndarray<float>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{1_ct});
        using view_t = view::decorator_t< view::zeros_t, shape_t, int >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::fixed_ndarray<int,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using shape_t = decltype(nmtools_tuple{2_ct,3_ct,1_ct});
        using view_t = view::decorator_t< view::zeros_t, shape_t, int >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::fixed_ndarray<int,2,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_constant_index_array_v<shape_t> );
        static_assert( std::is_same_v< meta::make_fixed_ndarray_t<int,shape_t>, expected_t > );
    }
    {
        using shape_t = decltype(nmtools_tuple{2_ct,3_ct,4_ct,1_ct});
        using view_t = view::decorator_t< view::zeros_t, shape_t, double >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::fixed_ndarray<double,2,3,4,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}