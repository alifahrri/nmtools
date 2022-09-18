#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("shape_matmul" * doctest::test_suite("index"))
{
    {
        using lhs_shape_t = int[2];
        using rhs_shape_t = int[2];
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = nmtools_array<int,2>;
        using rhs_shape_t = nmtools_array<int,2>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = nmtools_list<int>;
        using rhs_shape_t = nmtools_list<int>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = na::static_vector<int,2>;
        using rhs_shape_t = na::static_vector<int,2>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = na::static_vector<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = na::static_vector<int,2>;
        using rhs_shape_t = na::static_vector<int,3>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = na::static_vector<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = na::static_vector<int,3>;
        using rhs_shape_t = na::static_vector<int,2>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = na::static_vector<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using lhs_shape_t = na::static_vector<int,2>;
        using rhs_shape_t = na::static_vector<int,2>;
        using result_t    = meta::resolve_optype_t<ix::shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        // TODO: make the type unsigned
        using expect_t    = na::static_vector<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}

TEST_CASE("matmul" * doctest::test_suite("index"))
{
    {
        using indices_t   = int[2];
        using lhs_shape_t = int[2];
        using rhs_shape_t = int[2];
        using shape_t     = int[2];
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,all_t>;
        using rhs_expect_t = nmtools_tuple<all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[3];
        using lhs_shape_t = int[3];
        using rhs_shape_t = int[2];
        using shape_t     = int[3];
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,int,all_t>;
        using rhs_expect_t = nmtools_tuple<all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[3];
        using lhs_shape_t = int[2];
        using rhs_shape_t = int[3];
        using shape_t     = int[3];
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,all_t>;
        using rhs_expect_t = nmtools_tuple<int,all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t    = nmtools_array<int,2>;
        using lhs_shape_t  = nmtools_array<int,2>;
        using rhs_shape_t  = nmtools_array<int,2>;
        using shape_t      = nmtools_array<int,2>;
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,all_t>;
        using rhs_expect_t = nmtools_tuple<all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = nmtools_list<int>;
        using lhs_shape_t = nmtools_list<int>;
        using rhs_shape_t = nmtools_list<int>;
        using shape_t     = nmtools_list<int>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = nmtools_list<slice_t>;
        using rhs_expect_t = nmtools_list<slice_t>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = na::static_vector<int,2>;
        using lhs_shape_t = na::static_vector<int,2>;
        using rhs_shape_t = na::static_vector<int,2>;
        using shape_t     = na::static_vector<int,2>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = na::static_vector<slice_t,2>;
        using rhs_expect_t = na::static_vector<slice_t,2>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = na::static_vector<int,3>;
        using lhs_shape_t = na::static_vector<int,3>;
        using rhs_shape_t = na::static_vector<int,2>;
        using shape_t     = na::static_vector<int,3>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = na::static_vector<slice_t,3>;
        using rhs_expect_t = na::static_vector<slice_t,2>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[2];
        using lhs_shape_t = int[2];
        using rhs_shape_t = nmtools_array<int,2>;
        using shape_t     = nmtools_array<int,2>;
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,all_t>;
        using rhs_expect_t = nmtools_tuple<all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[3];
        using lhs_shape_t = nmtools_array<int,3>;
        using rhs_shape_t = int[2];
        using shape_t     = nmtools_array<int,3>;
        using all_t        = nmtools_tuple<nm::none_t,nm::none_t>;
        using lhs_expect_t = nmtools_tuple<int,int,all_t>;
        using rhs_expect_t = nmtools_tuple<all_t,int>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[3];
        using lhs_shape_t = nmtools_array<int,3>;
        using rhs_shape_t = na::static_vector<int,2>;
        using shape_t     = nmtools_array<int,3>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = nmtools_tuple<int,int,all_t>;
        using rhs_expect_t = na::static_vector<slice_t,2>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = int[3];
        using lhs_shape_t = nmtools_array<int,3>;
        using rhs_shape_t = nmtools_list<int>;
        using shape_t     = nmtools_array<int,3>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = nmtools_tuple<int,int,all_t>;
        using rhs_expect_t = nmtools_list<slice_t>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using indices_t   = na::static_vector<int,3>;
        using lhs_shape_t = na::static_vector<int,3>;
        using rhs_shape_t = nmtools_list<int>;
        using shape_t     = na::static_vector<int,3>;
        using all_t       = nmtools_tuple<nm::none_t,nm::none_t>;
        using slice_t     = nmtools_either<int,all_t>;
        using lhs_expect_t = na::static_vector<slice_t,3>;
        using rhs_expect_t = nmtools_list<slice_t>;
        using expect_t     = nmtools_tuple<lhs_expect_t,rhs_expect_t>;
        using result_t     = meta::resolve_optype_t<ix::matmul_t,indices_t,lhs_shape_t,rhs_shape_t,shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}