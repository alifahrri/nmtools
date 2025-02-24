#include "nmtools/meta.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/dynamic.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/utility/at.hpp"
#include "nmtools/testing/testing.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif
#include <array>
#include <vector>
#include <initializer_list>

namespace meta = nmtools::meta;

TEST_CASE("remove_nested_array_dim_t" * doctest::test_suite("transform"))
{
    {
        using arg_t = std::array<double,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<double,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,3>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,3>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = std::array<double,1>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = std::array<std::array<double,1>,3>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,6>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::vector<double>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::vector<double>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,3>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = std::vector<double>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<double>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<double>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<double>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<double>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = std::initializer_list<double>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,3>;
        using expected_t = double;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,2>;
        using expected_t = std::initializer_list<double>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,1>;
        using expected_t = std::initializer_list<std::initializer_list<double>>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        using result_t = meta::remove_nested_array_dim_t<arg_t,0>;
        using expected_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        STATIC_CHECK_IS_SAME(result_t, expected_t);
    }
}