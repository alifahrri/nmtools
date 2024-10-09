#if __has_include(<boost/array.hpp>)
#define NMTOOLS_ENABLE_BOOST
#endif
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::none_t;

#define declval(type) meta::declval<type>()

#ifdef NMTOOLS_DISABLE_STL
using meta::false_type, meta::true_type;
#else
using std::false_type, std::true_type;
#endif


TEST_CASE("reduce" * doctest::test_suite("view"))
{
    SUBCASE("is_fixed_dim")
    {
        using op_t       = view::add_t<none_t,none_t,none_t>;
        using initial_t  = none_t;
        {
            using array_t    = int[2][3][2];
            using axis_t     = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t    = int[2][3][2];
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        {
            using array_t    = int[2][3][2];
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        // TODO: fix
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[2];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        // }

        {
            using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        }
        {
            using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = int[2];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, view_t );
        // }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        // }
    }

    SUBCASE("is_num")
    {
        using op_t      = view::add_t<none_t,none_t,none_t>;
        using initial_t = none_t;
        {
            using array_t    = int[2][3][2];
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        }
        {
            using array_t    = int[2][3][2];
            using axis_t     = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2];
        //     using axis_t     = int;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[2];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = int[2][3][2];
        //     using axis_t     = int[1];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }

        {
            using array_t    = na::fixed_ndarray<int,2,3,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        }
        {
            using array_t    = na::fixed_ndarray<int,2,3,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = int[3];
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = nmtools_array<int,3>;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = nmtools_array<int,3>;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = int[2];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }
        // {
        //     using array_t    = na::fixed_ndarray<int,2,3,2>;
        //     using axis_t     = int[1];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        // }

        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using axis_t  = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_t );
        }
        {
            using array_t = na::hybrid_ndarray<int,12,3>;
            using axis_t  = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = int[3];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = int[3];
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = nmtools_array<int,3>;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = nmtools_array<int,3>;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = int[2];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t = na::hybrid_ndarray<int,12,3>;
        //     using axis_t  = int[1];
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        // }

        {
            using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::false_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_t );
        }
        {
            using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
            using axis_t     = none_t;
            using keepdims_t = meta::true_type;
            using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = nmtools_array<int,3>;
        //     using keepdims_t = meta::false_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_t );
        // }
        // {
        //     using array_t    = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        //     using axis_t     = nmtools_array<int,3>;
        //     using keepdims_t = meta::true_type;
        //     using view_t = view::decorator_t<view::reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t,none_t>;
        //     NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_num, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_t );
        // }
    }
}

TEST_CASE("is_fixed_dim_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("ufunc")
    {
        using array_t = na::dynamic_ndarray<int>;
        using view_t  = view::decorator_t< view::ufunc_t, view::sin_t, array_t >;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, view_t );
        static_assert( !meta::is_fixed_dim_ndarray_v<array_t> );
        static_assert( !meta::is_fixed_size_ndarray_v<array_t> );
        static_assert( !meta::is_fixed_size_ndarray_v<view_t> );
    }
}

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("divide")
    {
        {
            // divide * reduce_add
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, false_type, none_t>;
            using rhs_t = size_t;
            // using view_t = decltype(view::divide(declval(lhs_t),declval(rhs_t)));
            using view_t = view::decorator_t< view::ufunc_t, view::divide_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            // divide * reduce_add
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, false_type, none_t>;
            using rhs_t = size_t;
            using view_t = decltype(view::divide(declval(lhs_t),declval(rhs_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
    SUBCASE("multiply")
    {
        {
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, false_type, none_t>;
            using rhs_t = size_t;
            using view_t = decltype(view::multiply(declval(lhs_t),declval(rhs_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
}

using namespace nm::literals;

#if 1
TEST_CASE("ufunc(case1)" * doctest::test_suite("meta::ufunc"))
{
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_array<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = decltype(nmtools_tuple{2_ct,3_ct,2_ct});
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = na::static_vector<float,12>;
        using shape_type  = na::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = nmtools_list<float>;
        using shape_type  = nmtools_list<size_t>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#ifdef NMTOOLS_ENABLE_BOOST
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::static_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::small_vector<float,12>;
        using shape_type  = boost::array<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::container::vector<float>;
        using shape_type  = boost::container::static_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
    {
        using buffer_type = boost::array<float,12>;
        using shape_type  = boost::container::small_vector<size_t,3>;
        using array_type  = na::ndarray_t<buffer_type,shape_type>;

        using view_type = decltype(view::sin(declval(array_type)));
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_shape, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_bounded_dim, view_type );
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_bounded_size, view_type );

        {
            constexpr auto fixed_shape  = meta::fixed_shape_v<view_type>;
            constexpr auto fixed_dim    = meta::fixed_dim_v<view_type>;
            constexpr auto fixed_size   = meta::fixed_size_v<view_type>;
            constexpr auto bounded_dim  = meta::bounded_dim_v<view_type>;
            constexpr auto bounded_size = meta::bounded_size_v<view_type>;
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_shape, (nmtools_array{2,3,2}));
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(fixed_size, 12);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_dim, 3);
            NMTOOLS_CHECK_EQUAL_IF_NOT_FAIL(bounded_size, 12);
        }
    }
#endif // NMTOOLS_ENABLE_BOOST
}
#endif