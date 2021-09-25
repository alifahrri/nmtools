#include "nmtools/array/view/var.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#define declval(type) std::declval<type>()

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("is_ndarray" * doctest::test_suite("view::var"))
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int[1];
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
    {
        using array_t = int[2][3][2];
        using axis_t  = std::vector<int>;
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        // NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, view_t );
    }
}

TEST_CASE("get_element_type" * doctest::test_suite("view::var"))
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int[1];
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using elem_t  = meta::get_element_type_t<view_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( elem_t, float );
    }
}

TEST_CASE("get_underlying_array_type" * doctest::test_suite("view::var"))
{
    {
        using array_t = int[2][3][2];
        using axis_t  = int[1];
        using view_t  = decltype(view::var(declval(array_t),declval(axis_t)));
        using underlying_array_t = meta::get_underlying_array_type_t<view_t>;
        // NOTE: atm, var view is defined as:
        // mean[array,axis,...] | subtract[array,array] | fabs[array] | square[array] | sum[array] | divide[array,int]
        // hence the array of int[2][3][2] may appear twice because of subtract
        // and there will be integer because of division with N-ddof
        // this should not be a problem since underlying_array will only be used to deduce eval type at the moment
        using expected_t = std::tuple<int const (&) [2][3][2], int const (&) [2][3][2], int const, unsigned long const>;
        NMTOOLS_STATIC_CHECK_IS_SAME( underlying_array_t, expected_t );
    }
}