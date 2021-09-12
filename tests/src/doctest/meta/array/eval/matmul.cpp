#include "nmtools/array/view/matmul.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("matmul")
    {
        {
            using lhs_t   = int[3][4];
            using rhs_t   = int[4][3];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = std::array<std::array<int,3>,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = std::array<std::array<int,4>,3>;
            using rhs_t   = std::array<std::array<int,3>,4>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = std::array<std::array<int,3>,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = na::fixed_ndarray<int,3,4>;
            using rhs_t   = na::fixed_ndarray<int,4,3>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::fixed_ndarray<int,3,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::hybrid_ndarray<int,12*12,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }

        // batched
        {
            using lhs_t   = int[4][3];
            using rhs_t   = int[2][3][2];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = std::array<std::array<std::array<int,2>,4>,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::fixed_ndarray<int,4,3>;
            using rhs_t  = na::fixed_ndarray<int,2,3,2>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::fixed_ndarray<int,2,4,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t  = na::hybrid_ndarray<int,12,2>;
            using rhs_t  = na::hybrid_ndarray<int,12,3>;
            using view_t = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::hybrid_ndarray<int,12*12,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }

        // fixed lhs, hybrid rhs
        {
            using lhs_t   = int[4][3];
            using rhs_t   = na::hybrid_ndarray<int,2*3*2,3>;
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::hybrid_ndarray<int,2*3*2*12,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
        {
            using lhs_t   = na::hybrid_ndarray<int,2*3*2,2>;
            using rhs_t   = int[2][3][2];
            using view_t  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
            using array_t = meta::resolve_optype_t< na::eval_t, view_t, nm::none_t >;
            using expected_t = na::hybrid_ndarray<int,2*3*2*12,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( array_t, expected_t );
        }
    }
}