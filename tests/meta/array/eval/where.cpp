#include "nmtools/array/view/where.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("where" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t<
            view::where_t, int[3], int[3], int[3]
        >;
        using eval_t = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
        static_assert( meta::fixed_ndarray_dim_v<view_t> == 1 );
        using element_t = meta::get_element_type_t<view_t>;
        static_assert( std::is_same_v<element_t,int> );
    }
    {
        using view_t = view::decorator_t< view::where_t,
            na::hybrid_ndarray<int,3,1>, na::hybrid_ndarray<int,3,1>, na::hybrid_ndarray<int,3,1>
        >;
        using eval_t = meta::resolve_optype_t<na::eval_t,view_t,nm::none_t>;
        using expected_t = na::hybrid_ndarray<int,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( !meta::is_fixed_size_ndarray_v<view_t> );
        static_assert( !meta::is_fixed_size_ndarray_v<na::hybrid_ndarray<int,3,1>> );
    }
}