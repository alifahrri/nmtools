#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("broadcast_shape(vector;vector)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;array)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = std::array<int,3>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(tuple;tuple)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = std::tuple<int,int,int,int>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(hybrid_ndarray;hybrid_ndarray)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = na::hybrid_ndarray<int,4,1>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(vector;any)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<int>;
        using rhs_t = std::array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::vector<int>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;any)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = std::array<int,4>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;any)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,4,1>;
        using rhs_t = std::tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = std::vector<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = std::vector<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = std::array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}