#include "nmtools/index/choose.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

TEST_CASE("choose(array,array)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_array<size_t,4>;
        using arr_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(vector,vector)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(tuple,tuple)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_tuple<size_t,size_t,size_t,size_t>;
        using arr_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,4>;
        // static_assert( meta::is_constant_index_array_v<ind_t> );
        // static_assert( meta::is_constant_index_array_v<arr_t> );
        static_assert( meta::is_fixed_index_array_v<ind_t> );
        static_assert( meta::is_fixed_index_array_v<arr_t> );
        static_assert( meta::fixed_index_array_size_v<ind_t> == 4 );
        static_assert( std::is_same_v<meta::make_fixed_ndarray_t<int,nmtools_tuple<meta::ct<4>>>,na::fixed_ndarray<int,4>> );
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(vector,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = nmtools_tuple<size_t,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        #ifdef __EMSCRIPTEN__
            using exp_t = nmtools_list<int>;
            NMTOOLS_STATIC_CHECK_IS_SAME( res_t, exp_t );
        #else
            using exp_t = nmtools_list<long>;
            NMTOOLS_STATIC_CHECK_IS_SAME( res_t, exp_t );
        #endif
    }
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = nmtools_tuple<size_t,int,int,int,nmtools_list<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = meta::error::INDEX_CHOOSE_UNSUPPORTED<ind_t,arr_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_list<size_t>;
        using arr_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(array,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_array<size_t,4>;
        using arr_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_array<size_t,4>;
        using arr_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_array<size_t,3>;
        using arr_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_array<size_t,3>;
        using arr_t = nmtools_tuple<int,int,nmtools_tuple<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = meta::error::INDEX_CHOOSE_UNSUPPORTED<ind_t,arr_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_array<size_t,3>;
        using arr_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(tuple,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = nmtools_tuple<size_t,size_t,size_t,size_t>;
        using arr_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_tuple<size_t,size_t,size_t>;
        using arr_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = nmtools_tuple<size_t,size_t,size_t>;
        using arr_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(hybrid_ndarray,hybrid_ndarray)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = na::hybrid_ndarray<int,5,1>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_static_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(hybrid,raw)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = na::hybrid_ndarray<size_t,3,1>;
        using arr_t = int[3];
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_static_vector<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("choose(hybrid_ndarray,any)" * doctest::test_suite("meta::choose"))
{
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_static_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = nmtools_array<int,5>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_static_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = nmtools_static_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using ind_t = na::hybrid_ndarray<size_t,4,1>;
        using arr_t = nmtools_tuple<int,int,int,nmtools_tuple<int>>;
        using res_t = meta::resolve_optype_t<nm::index::choose_t,ind_t,arr_t>;
        using exp_t = meta::error::INDEX_CHOOSE_UNSUPPORTED<ind_t,arr_t>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}