#include "nmtools/array/view/repeat.hpp"
#include "nmtools/array/core/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nmtools::literals;

TEST_CASE("eval(repeat)" * doctest::test_suite("eval"))
{
    {
        using array_t    = int[2][2];
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,12>,decltype(nmtools_tuple{12_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<int,3>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,9ul>,nmtools_tuple<meta::ct<9ul>>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,2,2>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,12>,decltype(nmtools_tuple{12_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using repeats_t  = meta::ct<3>;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        // axis is none so single dim
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }

    // repeats is runtime value
    {
        using array_t    = int[2][2];
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        // axis is none so single dim
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = nmtools_array<int,3>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        // axis is none so single dim
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::fixed_ndarray<int,4,2>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        // axis is none so single dim
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using array_t    = na::dynamic_ndarray<int>;
        using repeats_t  = int;
        using axis_t     = nm::none_t;
        
        using src_shape_t = decltype(nm::shape<true>(meta::declval<array_t>()));
        using src_size_t  = decltype(nm::size<true>(meta::declval<array_t>()));
        using indexer_t   = view::repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>;
        using view_t      = view::decorator_t< view::indexing_t, array_t, indexer_t>;
        
        using eval_t     = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
        // axis is none so single dim
        using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
}