#include "nmtools/index/expand_dims.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("expand_dims(vector,vector)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_list<size_t>;
        using axes_t   = nmtools_list<size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

TEST_CASE("expand_dims(array,array)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_array<size_t,3>;
        using axes_t   = nmtools_array<size_t,3>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_array<size_t,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

TEST_CASE("expand_dims(tuple,tuple)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_tuple<size_t,size_t,size_t>;
        using axes_t   = nmtools_tuple<size_t,size_t,size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_array<size_t,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

TEST_CASE("expand_dims(hybrid_ndarray,hybrid_ndarray)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = na::hybrid_ndarray<size_t,3,1>;
        using axes_t   = na::hybrid_ndarray<size_t,3,1>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_static_vector<size_t,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

TEST_CASE("expand_dims(vector,any)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_list<size_t>;
        using axes_t   = nmtools_array<size_t,3>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using axes_t   = nmtools_tuple<size_t,size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_list<size_t>;
        using axes_t   = na::hybrid_ndarray<size_t,3,1>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

TEST_CASE("expand_dims(array;any)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_array<size_t,3>;
        using axes_t   = nmtools_list<size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using axes_t   = nmtools_tuple<size_t,size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_array<size_t,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using axes_t   = na::hybrid_ndarray<size_t,2,1>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_static_vector<size_t,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_array<size_t,3>;
        using axes_t   = nmtools_tuple<meta::ct<1>,meta::ct<2>>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_array<size_t,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}

// NOTE: no longer supported
// TODO: remove
#if 0
TEST_CASE("expand_dims(tuple,any)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = nmtools_tuple<size_t,size_t,size_t>;
        using axes_t   = nmtools_list<size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_tuple<size_t,size_t,size_t>;
        using axes_t   = nmtools_array<size_t,2>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_array<size_t,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    {
        using shape_t  = nmtools_tuple<size_t,size_t,size_t>;
        using axes_t   = na::hybrid_ndarray<size_t,2,1>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_static_vector<size_t,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}
#endif

TEST_CASE("expand_dims(hybrid_ndarray,any)" * doctest::test_suite("meta::expand_dims"))
{
    {
        using shape_t  = na::hybrid_ndarray<size_t,3,1>;
        using axes_t   = nmtools_array<size_t,3>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_static_vector<size_t,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    // TODO: disable tuple with runtime value
    #if 0
    {
        using shape_t  = na::hybrid_ndarray<size_t,3,1>;
        using axes_t   = nmtools_tuple<size_t,size_t,size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_static_vector<size_t,6>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
    #endif
    {
        using shape_t  = na::hybrid_ndarray<size_t,3,1>;
        using axes_t   = nmtools_list<size_t>;
        using result_t = meta::resolve_optype_t<nm::index::shape_expand_dims_t,shape_t,axes_t>;
        using exp_t    = nmtools_list<size_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, exp_t );
    }
}