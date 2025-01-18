#include "nmtools/meta.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nmtools::array;
namespace meta = nmtools::meta;

TEST_CASE("replace_element_type_t" * doctest::test_suite("meta"))
{
    {
        using arg0_t   = nmtools_list<double>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<arg1_t> );
    }
    {
        using arg0_t   = nmtools_list<double>;
        using arg1_t   = size_t;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<arg1_t> );
    }
    {
        using arg0_t   = nmtools_list<double>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<arg1_t> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<double>>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<arg1_t>> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<double>>;
        using arg1_t   = size_t;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<arg1_t>> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<double>>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<arg1_t>> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<nmtools_list<double>>>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<nmtools_list<arg1_t>>> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<nmtools_list<double>>>;
        using arg1_t   = size_t;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<nmtools_list<arg1_t>>> );
    }
    {
        using arg0_t   = nmtools_list<nmtools_list<nmtools_list<double>>>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, nmtools_list<nmtools_list<nmtools_list<arg1_t>>> );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<double,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<arg1_t,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<nmtools_array<double,n>,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<nmtools_array<arg1_t,n>,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<nmtools_array<nmtools_array<double,n>,n>,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<nmtools_array<nmtools_array<arg1_t,n>,n>,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<double,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<arg1_t,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 1;
        using arg0_t   = nmtools_array<int,1>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<arg1_t,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<nmtools_array<double,n>,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<nmtools_array<arg1_t,n>,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = nmtools_array<nmtools_array<nmtools_array<double,n>,n>,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = nmtools_array<nmtools_array<nmtools_array<arg1_t,n>,n>,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        using arg0_t   = na::dynamic_ndarray<double>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, na::dynamic_ndarray<arg1_t> );
    }
    {
        using arg0_t   = na::dynamic_ndarray<double>;
        using arg1_t   = size_t;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, na::dynamic_ndarray<arg1_t> );
    }
    {
        using arg0_t   = na::dynamic_ndarray<double>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        STATIC_CHECK_IS_SAME( result_t, na::dynamic_ndarray<arg1_t> );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n,n,n>;
        using arg1_t   = float;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n,n,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    {
        constexpr auto n = 7;
        using arg0_t   = na::fixed_ndarray<double,n,n,n>;
        using arg1_t   = bool;
        using result_t = meta::replace_element_type_t<arg0_t,arg1_t>;
        using expected_t = na::fixed_ndarray<arg1_t,n,n,n>;
        STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}