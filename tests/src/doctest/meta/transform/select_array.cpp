#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("select_array(vector;vector)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_min_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_max_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_resizeable_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_fixed_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_hybrid_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(array;array)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,7>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<meta::size_policy_min_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<meta::size_policy_max_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_resizeable_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,7>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_min_t,
            meta::select_fixed_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::array<double,3>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_max_t,
            meta::select_hybrid_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(tuple;tuple)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,7>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_min_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_max_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,std::tuple<size_t>>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_max_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_resizeable_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,7>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_min_t,
            meta::select_fixed_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::tuple<int,char,double,size_t>;
        using rhs_t = std::tuple<int,char,double>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_max_t,
            meta::select_hybrid_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(hybrid_ndarray;hybrid_ndarray)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,7,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_min_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_max_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_add_t,
            meta::select_resizeable_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,7,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_min_t,
            meta::select_fixed_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = na::hybrid_ndarray<double,3,1>;
        using tag_t = meta::select_array1d_t<
            meta::size_policy_max_t,
            meta::select_hybrid_kind_t
        >;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(vector;any)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<void,meta::select_resizeable_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_resizeable_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<void,meta::select_fixed_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<double>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<void,meta::select_hybrid_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(array;any)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_resizeable_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = na::hybrid_ndarray<double,4,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_resizeable_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = na::hybrid_ndarray<double,4,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_hybrid_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,8,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<double,4>;
        using rhs_t = na::hybrid_ndarray<double,4,1>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_fixed_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,8>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("select_array(hybrid_array;any)" * doctest::test_suite("meta::select_array"))
{
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_resizeable_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_hybrid_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::vector<double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_fixed_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = void;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_hybrid_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,8,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::array<double,4>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_fixed_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = std::array<double,8>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
     {
        using lhs_t = na::hybrid_ndarray<double,4,1>;
        using rhs_t = std::tuple<double,double,double,double>;
        using tag_t = meta::select_array1d_t<meta::size_policy_add_t,meta::select_hybrid_kind_t>;
        using res_t = meta::resolve_optype_t<tag_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<double,8,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}