#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "testing/testing.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif
#include <array>
#include <vector>
#include <initializer_list>

namespace meta = nmtools::meta;

TEST_CASE("nested_array_dim_v" * doctest::test_suite("transform"))
{
    {
        using arg_t = std::array<double,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::array<std::array<double,3>,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,3>,2>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==3);
    }
    {
        using arg_t = std::vector<double>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==3);
    }
    {
        using arg_t = std::initializer_list<double>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==1);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<double>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==2);
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<std::initializer_list<double>>>;
        constexpr auto result = meta::nested_array_dim_v<arg_t>;
        LOG_TYPEINFO(arg_t);
        STATIC_CHECK(result==3);
    }
}