#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

#define declval(x) std::declval<x>()

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
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = nmtools_list<double>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, nmtools_list<float> >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = nmtools_list<float>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, nmtools_array<int,4> >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = nmtools_array<double,4>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, int[4] >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = nmtools_array<double,4>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::fixed_ndarray<int,2,3,2> >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::fixed_ndarray<double,2,3,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::hybrid_ndarray<int,1,4> >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::hybrid_ndarray<double,1,4>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
            static_assert( meta::is_hybrid_ndarray_v<view_t> );
        }
        {
            using view_t = view::decorator_t< view::ufunc_t, view::sin_t, na::dynamic_ndarray<int> >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::dynamic_ndarray<double>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
    }
    SUBCASE("add")
    {
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, nmtools_list<int>, nmtools_list<int> >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = nmtools_list<int>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, nmtools_array<int,4>, nmtools_array<int,4> >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = nmtools_array<int,4>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, int[4], int[4] >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = nmtools_array<int,4>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, na::fixed_ndarray<int,2,3,2>, na::fixed_ndarray<int,2,3,2> >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = na::fixed_ndarray<int,2,3,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using op_t   = view::add_t<>;
            using view_t = view::decorator_t< view::ufunc_t, op_t, na::hybrid_ndarray<int,1,3>, na::hybrid_ndarray<int,1,3> >;
            using eval_t = meta::resolve_optype_t<na::eval_t, view_t, none_t>;
            using expected_t = na::hybrid_ndarray<int,1,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
            using free_axes_t = na::hybrid_ndarray<size_t, 2, 1>;
            using view_t = view::decorator_t< view::ufunc_t, view::add_t<>,
                view::decorator_t< view::broadcast_to_t, int [3][3], shape_t , free_axes_t >,
                view::decorator_t< view::broadcast_to_t, int [3], shape_t , free_axes_t >
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = nmtools_array<nmtools_array<int,3>,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using shape_t = nmtools_array<size_t,2>;
            using free_axes_t = na::hybrid_ndarray<size_t, 2, 1>;
            using lhs_t = view::decorator_t< view::broadcast_to_t, int [3][3], shape_t , free_axes_t >;
            using rhs_t = view::decorator_t< view::broadcast_to_t, int, shape_t , free_axes_t >;
            using view_t = view::decorator_t<
                view::ufunc_t, view::add_t<>, lhs_t, rhs_t
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::dynamic_ndarray<int>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using shape_t = decltype(nmtools_tuple{3_ct,3_ct});
            using free_axes_t = na::hybrid_ndarray<size_t, 2, 1>;
            using view_t = view::decorator_t< view::ufunc_t, view::add_t<>,
                view::decorator_t< view::broadcast_to_t, int [3][3], shape_t , free_axes_t >,
                view::decorator_t< view::broadcast_to_t, int, shape_t , free_axes_t >
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = nmtools_array<nmtools_array<int,3>,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
    }
    SUBCASE("clip")
    {
        {
            using view_t = view::decorator_t< view::ufunc_t, view::clip_t,
                view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,6,2>,  nmtools_array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >,
                view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,12,3>, nmtools_array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >,
                view::decorator_t< view::broadcast_to_t, na::hybrid_ndarray<int,1,1>,  nmtools_array<size_t,3>, na::hybrid_ndarray<size_t,3,1> >
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            // NOTE: broadcast_to view can't infer hybrid_ndarray for now 
            // because shape array with maximum number of elements is not supported yet
            // using expected_t = na::hybrid_ndarray<int,12,3>;
            using expected_t = na::dynamic_ndarray<int>;
            static_assert( !meta::is_hybrid_ndarray_v<view_t> );
            static_assert(  meta::is_dynamic_ndarray_v<view_t> );
            static_assert( !meta::is_fixed_size_ndarray_v<view_t> );
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        {
            using shape_t = nmtools_tuple<integral_constant<size_t, 3>, integral_constant<size_t, 2> >;
            using origin_axes_t = nmtools::array::hybrid_ndarray<size_t, 2, 1>;
            using view_t = view::decorator_t< view::ufunc_t, view::clip_t,
                view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<float,3,2>, shape_t, origin_axes_t >,
                view::decorator_t< view::broadcast_to_t, na::fixed_ndarray<float,2>, shape_t, origin_axes_t >,
                view::decorator_t< view::broadcast_to_t, float, shape_t, origin_axes_t >
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = na::fixed_ndarray<float,3,2>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
            static_assert( meta::is_ndarray_v<view_t> );
            static_assert( meta::is_fixed_size_ndarray_v<view_t> );
        }
        // TODO: fix
        #if 0
        {
            using shape_t = nmtools_tuple<integral_constant<size_t, 3>, integral_constant<size_t, 2> >;
            using origin_axes_t = nmtools::array::hybrid_ndarray<size_t, 2, 1>;
            using view_t = view::decorator_t< view::ufunc_t, view::clip_t,
                view::decorator_t< view::broadcast_to_t, float[3][2], shape_t, origin_axes_t >,
                view::decorator_t< view::broadcast_to_t, float[2], shape_t, origin_axes_t >,
                view::decorator_t< view::broadcast_to_t, float, shape_t, origin_axes_t >
            >;
            using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
            using expected_t = nmtools_array<nmtools_array<float,2>,3>;
            NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        }
        #endif
    }
}

TEST_CASE("eval(outer_ufunc)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t<view::outer_t, view::add_t<>, int [2][3], int [3]>;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = nmtools_array<nmtools_array<nmtools_array<int, 3ul>, 3ul>, 2ul>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        // static_assert( meta::is_fixed_size_ndarray_v<view_t> );
    }
    {
        using lhs_t = na::hybrid_ndarray<int, 6, 2>;
        using rhs_t = na::hybrid_ndarray<int, 3, 1>;
        using view_t = view::decorator_t< view::outer_t, view::add_t<>, lhs_t, rhs_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::hybrid_ndarray<int, 18, 3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::hybrid_ndarray_max_size_v<view_t> == 18 );
        static_assert( meta::fixed_dim_v<view_t> == 3 );
        static_assert( meta::is_hybrid_ndarray_v<view_t> );
        static_assert( meta::is_hybrid_ndarray_v<lhs_t> );
        // static_assert( !meta::is_dynamic_ndarray_v<view_t> );
        // static_assert( !meta::is_dynamic_ndarray_v<lhs_t > );
    }
}