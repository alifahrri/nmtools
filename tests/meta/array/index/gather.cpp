#include "nmtools/index/gather.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("gather(vector;vector)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = nmtools_list<int>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_list<float>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<float>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_list<bool>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<bool>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(array;array)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = nmtools_array<int,4>;
        using rhs_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<float,4>;
        using rhs_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<bool,4>;
        using rhs_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<int,4>;
        using rhs_t = nmtools_array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<float,4>;
        using rhs_t = nmtools_array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<bool,4>;
        using rhs_t = nmtools_array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(hybrid_ndarray;hybrid_ndarray)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<float,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<bool,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<float,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<bool,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_static_vector<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(tuple;tuple)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = nmtools_tuple<int,int,int,int>;
        using rhs_t = nmtools_tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_tuple<float,float,float,float>;
        using rhs_t = nmtools_tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_tuple<bool,bool,bool,bool>;
        using rhs_t = nmtools_tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_tuple<int,int,int,int>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_tuple<float,float,float,float>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_tuple<bool,bool,bool,bool>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

using nm::index::gather_t;
using namespace nm::literals;
using nmtools_tuple;

#ifdef NMTOOLS_DISABLE_STL
using meta::integral_constant;
#else
using std::integral_constant;
#endif

TEST_CASE("gather" * doctest::test_suite("index"))
{
    {
        using vector_t  = nmtools_tuple<integral_constant<size_t,10>>;
        using indices_t = na::hybrid_ndarray<size_t,1,1>;
        using result_t  = meta::resolve_optype_t<nm::index::gather_t,vector_t,indices_t>;
        using expected_t = nmtools_static_vector<size_t,1>;
        static_assert( meta::is_constant_index_array_v<vector_t> && meta::is_hybrid_index_array_v<indices_t> );
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }

    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using indices_t = decltype(nmtools_tuple{0_ct,1_ct,2_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using indices_t = decltype(nmtools_tuple{1_ct,0_ct,2_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{2_ct,1_ct,3_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using indices_t = decltype(nmtools_tuple{1_ct,2_ct,0_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{2_ct,3_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using indices_t = decltype(nmtools_tuple{2_ct,0_ct,1_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{3_ct,1_ct,2_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct});
        using indices_t = decltype(nmtools_tuple{2_ct,1_ct,0_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{3_ct,2_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using vector_t  = decltype(nmtools_tuple{1_ct,2_ct,3_ct,4_ct,5_ct});
        using indices_t = decltype(nmtools_tuple{2_ct,1_ct,0_ct});
        using result_t  = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
        using expect_t  = decltype(nmtools_tuple{3_ct,2_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}