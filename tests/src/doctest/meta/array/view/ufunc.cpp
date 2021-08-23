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

#define declval(type) std::declval<type>()

TEST_CASE("ufunc" * doctest::test_suite("view"))
{
    SUBCASE("get_operands_type")
    {
        using array_t = int[2][3];
        using shape_t = std::array<unsigned long, 1>;
        using free_axes_t = nmtools::array::hybrid_ndarray<unsigned long, 1, 1>;
        using keepdims_t  = std::integral_constant<bool, false>;
        using reduced_t   = view::decorator_t<view::reduce_t, view::add_t<>, array_t, unsigned long, nmtools::none_t, keepdims_t >;
        using lhs_t = view::decorator_t<view::broadcast_to_t, reduced_t, shape_t, free_axes_t >;
        using rhs_t = view::decorator_t<view::broadcast_to_t, size_t, shape_t, none_t>;
        using operands_t = view::detail::get_operands_type_t<lhs_t,rhs_t>;
        using expected_t = std::tuple<const lhs_t, const rhs_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( operands_t, expected_t );
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

TEST_CASE("is_num" * doctest::test_suite("view::ufunc"))
{
    {
        using lhs_t  = view::decorator_t<view::broadcast_to_t, int, nm::none_t, nm::none_t>;
        using rhs_t  = view::decorator_t<view::broadcast_to_t, int, nm::none_t, nm::none_t>;
        using view_t = view::decorator_t<view::scalar_ufunc_t, view::add_t<>, lhs_t, rhs_t >;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
    }
    {
        using lhs_t  = view::decorator_t<view::broadcast_to_t, int, nm::none_t, nm::none_t>;
        using rhs_t  = view::decorator_t<view::broadcast_to_t, int, nm::none_t, nm::none_t>;
        using op_t   = view::add_t<>;
        using view_t = decltype(view::ufunc(declval(op_t),declval(lhs_t),declval(rhs_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, view_t );
    }
}

TEST_CASE("is_fixed_size_ndarray" * doctest::test_suite("view"))
{
    SUBCASE("divide")
    {
        {
            // divide * reduce_add
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, std::false_type>;
            using rhs_t = size_t;
            // using view_t = decltype(view::divide(declval(lhs_t),declval(rhs_t)));
            using view_t = view::decorator_t< view::ufunc_t, view::divide_t, lhs_t, rhs_t >;
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
        {
            // divide * reduce_add
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, std::false_type>;
            using rhs_t = size_t;
            using view_t = decltype(view::divide(declval(lhs_t),declval(rhs_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
    SUBCASE("multiply")
    {
        {
            using lhs_t = view::decorator_t<view::reduce_t, view::add_t<none_t,none_t,float>, int[3][2], size_t, none_t, std::false_type>;
            using rhs_t = size_t;
            using view_t = decltype(view::multiply(declval(lhs_t),declval(rhs_t)));
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, view_t );
        }
    }
}