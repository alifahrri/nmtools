#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("broadcast_to(vector;vector)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(array;array)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = std::array<int,3>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(tuple;tuple)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = std::tuple<int,int,int,int>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(hybrid_ndarray;hybrid_ndarray)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(vector;any)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<int>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(array;any)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,3,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_to(array;any)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

using std::integral_constant;

TEST_CASE("broadcast_to(raw,tuple)" * doctest::test_suite("index::shape_broadcast_to"))
{
    {
        using lhs_t = int[3];
        using rhs_t = std::tuple<integral_constant<size_t,1>,integral_constant<size_t,1>,integral_constant<size_t,3>>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<size_t,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = bool[3];
        using rhs_t = std::tuple<integral_constant<size_t,3>>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<size_t,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
        {
            using res_t = meta::replace_element_type_t<exp_t,bool>;
            using rep_t = std::array<bool,1>;
            STATIC_CHECK_IS_SAME( res_t, rep_t );
        }
    }
}

TEST_CASE("broadcast_to(array,tuple)" * doctest::test_suite("index::shape_broadcast_to"))
{
    SUBCASE("integral_constant")
    {
        using lhs_t = std::array<size_t,2>;
        using rhs_t = std::tuple<integral_constant<size_t,3>,integral_constant<size_t,3>>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<size_t,2>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    SUBCASE("integral_constant")
    {
        using lhs_t = std::array<size_t,3>;
        using rhs_t = std::tuple<integral_constant<size_t,3>,integral_constant<size_t,3>,integral_constant<size_t,3>>;
        using res_t = meta::resolve_optype_t<nm::index::shape_broadcast_to_t,lhs_t,rhs_t>;
        using exp_t = std::array<size_t,3>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}