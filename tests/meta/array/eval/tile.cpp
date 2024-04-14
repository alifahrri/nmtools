#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

// TODO: update/fix eval type deduction
TEST_CASE("tile" * doctest::test_suite("eval") * doctest::skip())
{
    {
        using array_type = int[3];
        using src_shape_type = decltype(nm::shape<true>(meta::declval<array_type>()));
        using reps_type = nmtools_tuple<meta::ct<1>>;
        using view_t = view::decorator_t<
            view::indexing_t, array_type, view::tile_t<src_shape_type,reps_type>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_type = int[3];
        using src_shape_type = decltype(nm::shape<true>(meta::declval<array_type>()));
        using reps_type = nmtools_tuple<meta::ct<1>,meta::ct<2>>;
        using view_t = view::decorator_t<
            view::indexing_t, array_type, view::tile_t<src_shape_type,reps_type>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = nmtools_array<nmtools_array<int,6>,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_type = int[3];
        using src_shape_type = decltype(nm::shape<true>(meta::declval<array_type>()));
        using reps_type = nmtools_list<int>;
        using view_t = view::decorator_t<
            view::indexing_t, array_type, view::tile_t<src_shape_type,reps_type>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_type = nmtools_list<int>;
        using src_shape_type = decltype(nm::shape<true>(meta::declval<array_type>()));
        using reps_type = nmtools_tuple<meta::ct<1>,meta::ct<2>>;
        using view_t = view::decorator_t<
            view::indexing_t, array_type, view::tile_t<src_shape_type,reps_type>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_type = na::fixed_ndarray<int,3>;
        using src_shape_type = decltype(nm::shape<true>(meta::declval<array_type>()));
        using reps_type = nmtools_tuple<meta::ct<1>,meta::ct<2>>;
        using view_t = view::decorator_t<
            view::indexing_t, array_type, view::tile_t<src_shape_type,reps_type>
        >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
        using expected_t = na::fixed_ndarray<int,1,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}