#include "nmtools/array/matmul.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
using namespace nmtools::literals;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t   = int[3][4];
            using rhs_t   = int[4][3];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = nmtools_array<nmtools_array<int,4>,3>;
            using rhs_t   = nmtools_array<nmtools_array<int,3>,4>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = na::fixed_ndarray<int,3,4>;
            using rhs_t   = na::fixed_ndarray<int,4,3>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_static_vector<int,12*12>,nmtools_array<size_t,2>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }

        // batched
        {
            using lhs_t   = int[4][3];
            using rhs_t   = int[2][3][2];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,2*4*2>,decltype(nmtools_tuple{2_ct,4_ct,2_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,2*4*2>,decltype(nmtools_tuple{2_ct,4_ct,2_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_static_vector<int,12*12>,nmtools_array<size_t,3>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }

        // fixed lhs, hybrid rhs
        {
            using lhs_t   = int[4][3];
            using rhs_t   = na::hybrid_ndarray<int,2*3*2,3>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_static_vector<int,2*3*2*12>,nmtools_array<size_t,3>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = na::hybrid_ndarray<int,2*3*2,2>;
            using rhs_t   = int[2][3][2];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, nm::none_t >;
            using expected_t = na::ndarray_t<nmtools_static_vector<int,2*3*2*12>,nmtools_array<size_t,3>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
    }
}