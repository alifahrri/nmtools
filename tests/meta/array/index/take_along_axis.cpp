#include "nmtools/array/index/take_along_axis.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("shape_take_along_axis" * doctest::test_suite("index::take_along_axis"))
{
    SUBCASE("case1")
    {
        using shape_t   = int[3];
        using indices_t = int[3];
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case2")
    {
        using shape_t   = nmtools_array<int,3>;
        using indices_t = nmtools_array<int,3>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case3")
    {
        using shape_t   = nmtools_list<int>;
        using indices_t = nmtools_list<int>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case4")
    {
        using shape_t   = na::fixed_ndarray<int,3>;
        using indices_t = na::fixed_ndarray<int,3>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = na::fixed_ndarray<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case5")
    {
        using shape_t   = na::hybrid_ndarray<int,3,1>;
        using indices_t = na::hybrid_ndarray<int,3,1>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = na::hybrid_ndarray<int,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case6")
    {
        using shape_t   = utl::array<int,3>;
        using indices_t = utl::array<int,3>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = utl::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );       
    }
    SUBCASE("case7")
    {
        using shape_t   = int[3];
        using indices_t = int[1];
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::shape_take_along_axis_t,shape_t,indices_t,axis_t>;
        using expect_t  = meta::error::SHAPE_TAKE_ALONG_AXIS_INVALID_DIM<shape_t,indices_t,axis_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}

// TODO: remove, unused
TEST_CASE("take_along_axis" * doctest::test_suite("index::take_along_axis"))
{
    SUBCASE("case1")
    {
        using dst_indices_t = size_t[3];
        using shape_t   = int[3];
        using indices_t = int[1][1][2];
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::take_along_axis_t,dst_indices_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case2")
    {
        using dst_indices_t = nmtools_array<size_t,3>;
        using shape_t   = nmtools_array<int,3>;
        using indices_t = int[1][1][2];
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::take_along_axis_t,dst_indices_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case3")
    {
        using dst_indices_t = na::fixed_ndarray<int,3>;
        using shape_t   = na::fixed_ndarray<int,3>;
        using indices_t = na::fixed_ndarray<int,1,1,2>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::take_along_axis_t,dst_indices_t,shape_t,indices_t,axis_t>;
        using expect_t  = na::fixed_ndarray<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case4")
    {
        using dst_indices_t = na::hybrid_ndarray<int,3,1>;
        using shape_t   = na::hybrid_ndarray<int,3,1>;
        using indices_t = na::hybrid_ndarray<int,2,3>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::take_along_axis_t,dst_indices_t,shape_t,indices_t,axis_t>;
        using expect_t  = na::hybrid_ndarray<int,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    SUBCASE("case5")
    {
        using dst_indices_t = nmtools_list<int>;
        using shape_t   = nmtools_list<int>;
        using indices_t = na::dynamic_ndarray<int>;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<ix::take_along_axis_t,dst_indices_t,shape_t,indices_t,axis_t>;
        using expect_t  = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}