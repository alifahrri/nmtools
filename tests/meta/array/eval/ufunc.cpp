#include "nmtools/core/eval.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/array/ufuncs/clip.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

#define declval(x) meta::declval<x>()

// for testing purpose
#ifdef NMTOOLS_DISABLE_STL
using nmtools::meta::false_type;
using nmtools::meta::integral_constant;
#else
using std::false_type;
using std::integral_constant;
#endif

TEST_CASE("eval(ufunc)" * doctest::test_suite("eval"))
{
    SUBCASE("sin")
    {
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, nmtools_list<int> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_list<double>,nmtools_array<size_t,1>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, nmtools_list<float> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_list<float>,nmtools_array<size_t,1>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, nmtools_array<int,4> >;
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_array<double,4>,decltype(nmtools_tuple{4_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, int[4] >;
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_array<double,4>,decltype(nmtools_tuple{4_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::fixed_ndarray<int,2,3,2> >;
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_array<double,2*3*2>,decltype(nmtools_tuple{2_ct,3_ct,2_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::hybrid_ndarray<int,1,4> >;
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_static_vector<double,1>,nmtools_array<size_t,4>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::dynamic_ndarray<int> >;
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_list<double>,nmtools_list<size_t>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
    }
    SUBCASE("add")
    {
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, nmtools_list<int>, nmtools_list<int> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_list<int>,nmtools_array<size_t,1>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, nmtools_array<int,4>, nmtools_array<int,4> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_array<int,4>,decltype(nmtools_tuple{4_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, int[4], int[4] >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_array<int,4>,decltype(nmtools_tuple{4_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, na::fixed_ndarray<int,2,3,2>, na::fixed_ndarray<int,2,3,2> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<nmtools_array<int,2*3*2>,decltype(nmtools_tuple{2_ct,3_ct,2_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        // NOTE: temporarily disabled for better deduction for constexpr
        // TODO: fix
        #if 0
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, na::hybrid_ndarray<int,1,3>, na::hybrid_ndarray<int,1,3> >;
            using eval_t = meta::resolve_optype_t<na::eval_result_t<>, view_t, none_t>;
            using expected_t = na::ndarray_t<na::static_vector<int,1>,nmtools_array<size_t,3>>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        #endif
        {
            using view_t = decltype(view::add(declval(int[3][3]),declval(int)));
            using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
            using expected_t = na::ndarray_t<nmtools_array<int,9>,decltype(nmtools_tuple{3_ct,3_ct})>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
    }
}

TEST_CASE("eval(outer_ufunc)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t<view::outer_t, view::add_t<>, int [2][3], int [3], none_t>;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,18>,decltype(nmtools_tuple{2_ct,3_ct,3_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        // static_assert( meta::is_fixed_shape_v<view_t> );
    }
    {
        using lhs_t = na::hybrid_ndarray<int, 6, 2>;
        using rhs_t = na::hybrid_ndarray<int, 3, 1>;
        using view_t = view::decorator_t< view::outer_t, view::add_t<>, lhs_t, rhs_t, none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_static_vector<int,18>,nmtools_array<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::bounded_size_v<view_t> == 18 );
        static_assert( meta::fixed_dim_v<view_t> == 3 );
        static_assert( meta::is_bounded_size_v<view_t> );
        static_assert( meta::is_bounded_size_v<lhs_t> );
        // static_assert( !meta::is_dynamic_ndarray_v<view_t> );
        // static_assert( !meta::is_dynamic_ndarray_v<lhs_t > );
    }
    {
        using lhs_t = na::ndarray_t<na::static_vector<int,6>, nmtools_array<size_t,2>>;
        using rhs_t = na::ndarray_t<na::static_vector<int,3>, nmtools_array<size_t,1>>;
        using view_t = view::decorator_t< view::outer_t, view::add_t<>, lhs_t, rhs_t, none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_static_vector<int,18>,nmtools_array<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_t = na::ndarray_t<nmtools_array<int, 6>, nmtools_static_vector<size_t,2>>;
        using rhs_t = na::ndarray_t<nmtools_array<int, 3>, nmtools_static_vector<size_t,1>>;
        using view_t = view::decorator_t< view::outer_t, view::add_t<>, lhs_t, rhs_t, none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,18>,nmtools_static_vector<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
    }
    {
        using lhs_shape_t = nmtools_tuple<nm::clipped_size_t<2>,nm::clipped_size_t<3>>;
        using lhs_t = na::ndarray_t<nmtools_array<int, 6>, lhs_shape_t>;
        using rhs_t = na::ndarray_t<nmtools_array<int, 3>, nmtools_static_vector<size_t,1>>;
        using view_t = view::decorator_t< view::outer_t, view::add_t<>, lhs_t, rhs_t, none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_result_t<>, view_t, none_t >;
        using expected_t = na::ndarray_t<nmtools_array<int,18>,nmtools_static_vector<size_t,3>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::fixed_dim_v<lhs_t> == 2 );
        static_assert( meta::bounded_dim_v<lhs_t> == 2 );
        static_assert( meta::bounded_size_v<lhs_shape_t> == 2 );
    }
}