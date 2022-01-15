#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>
#include <initializer_list>

namespace meta = nmtools::meta;

TEST_CASE("nested_array_dim_v" * doctest::test_suite("transform"))
{
    {
        using arg_t = std::array<double,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==3);
    }
    {
        using arg_t = std::vector<double>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==3);
    }
    {
        using arg_t = std::initializer_list<double>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<double>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        STATIC_CHECK(result==3);
    }
    {
        using arg_t = double[2][3][2];
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( result, 3 );
    }
}