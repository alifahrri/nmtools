#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
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
        using lhs_t = std::vector<int>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<float>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::vector<float>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<bool>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::vector<bool>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(array;array)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<float,4>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<bool,4>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<float,4>;
        using rhs_t = std::array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<bool,4>;
        using rhs_t = std::array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(hybrid_ndarray;hybrid_ndarray)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<float,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<float,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<bool,4,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<bool,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<float,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<float,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<bool,4,1>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<bool,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

// not yet fixed, flagged to may_fail
TEST_CASE("gather(fixed_vector;fixed_vector)" * doctest::test_suite("index::gather") * doctest::may_fail(true))
{
    {
        using lhs_t = na::fixed_vector<int,4>;
        using rhs_t = na::fixed_vector<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::fixed_vector<float,4>;
        using rhs_t = na::fixed_vector<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::fixed_vector<bool,4>;
        using rhs_t = na::fixed_vector<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::fixed_vector<int,4>;
        using rhs_t = na::fixed_vector<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::fixed_vector<float,4>;
        using rhs_t = na::fixed_vector<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::fixed_vector<bool,4>;
        using rhs_t = na::fixed_vector<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::fixed_vector<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(fixed_vector;fixed_vector)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = na::dynamic_vector<int>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::dynamic_vector<float>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<float>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::dynamic_vector<bool>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<bool>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::dynamic_vector<int>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::dynamic_vector<float>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<float>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::dynamic_vector<bool>;
        using rhs_t = na::dynamic_vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = na::dynamic_vector<bool>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather(tuple;tuple)" * doctest::test_suite("index::gather"))
{
    {
        using lhs_t = std::tuple<int,int,int,int>;
        using rhs_t = std::tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<float,float,float,float>;
        using rhs_t = std::tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<float,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<bool,bool,bool,bool>;
        using rhs_t = std::tuple<int,int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<bool,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,int,int,int>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<float,float,float,float>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<float,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<bool,bool,bool,bool>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::gather_t,lhs_t,rhs_t>;
        using exp_t = std::array<bool,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("gather" * doctest::test_suite("index"))
{
    SUBCASE("integral_constant")
    {
        using vector_t  = std::tuple<std::integral_constant<size_t,10>>;
        using indices_t = na::hybrid_ndarray<size_t,1,1>;
        using result_t  = meta::resolve_optype_t<nm::index::gather_t,vector_t,indices_t>;
        using expected_t = na::hybrid_ndarray<size_t,1,1>;
        static_assert( meta::is_constant_index_array_v<vector_t> && meta::is_hybrid_index_array_v<indices_t> );
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}