#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("broadcast_shape(vector;vector)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = nmtools_list<int>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;array)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = nmtools_array<int,3>;
        using rhs_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(tuple;tuple)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = nmtools_tuple<int,int,int,int>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,4>;
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
        using lhs_t = nmtools_list<int>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_list<int>;
        using rhs_t = nmtools_array<int,3>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_list<int>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;any)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = nmtools_array<int,4>;
        using rhs_t = nmtools_tuple<int,int,int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_array<int,4>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<int,4>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = nmtools_array<int,4>;
        using rhs_t = na::hybrid_ndarray<int,3,1>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

TEST_CASE("broadcast_shape(array;any)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = nmtools_list<int>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = nmtools_list<int>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
    {
        using lhs_t = na::hybrid_ndarray<int,3,1>;
        using rhs_t = nmtools_array<int,4>;
        using res_t = meta::resolve_optype_t<nm::index::broadcast_shape_t,lhs_t,rhs_t>;
        using exp_t = na::hybrid_ndarray<int,4,1>;
        STATIC_CHECK_IS_SAME( res_t, exp_t );
    }
}

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

using nm::index::broadcast_shape_t;
using namespace nm::literals;
using nmtools_tuple;

TEST_CASE("broadcast_shape" * doctest::test_suite("index"))
{
    {
        using ashape_t = decltype(nmtools_tuple{5_ct,4_ct});
        using bshape_t = decltype(nmtools_tuple{1_ct});
        using result_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;
        using expected_t = decltype(nmtools_tuple{5_ct,4_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using ashape_t = decltype(nmtools_tuple{5_ct,4_ct});
        using bshape_t = decltype(nmtools_tuple{1_ct});
        using result_t = meta::resolve_optype_t<broadcast_shape_t,bshape_t,ashape_t>;
        using expected_t = decltype(nmtools_tuple{5_ct,4_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using ashape_t = decltype(nmtools_tuple{5_ct,4_ct});
        using bshape_t = decltype(nmtools_tuple{4_ct});
        using result_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;
        using expected_t = decltype(nmtools_tuple{5_ct,4_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using ashape_t = decltype(nmtools_tuple{8_ct,1_ct,6_ct,1_ct});
        using bshape_t = decltype(nmtools_tuple{7_ct,1_ct,5_ct});
        using result_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;
        using expected_t = decltype(nmtools_tuple{8_ct,7_ct,6_ct,5_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}