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

namespace meta = nmtools::meta;

TEST_CASE("get_element_type_t" * doctest::test_suite("meta"))
{
    {
        using arg_t = double[3];
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = double[3][2];
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = double[3][2][1];
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::array<double,3>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::array<std::array<double,2>,3>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::array<std::array<std::array<double,1>,2>,3>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::array<std::array<std::array<std::array<double,1>,2>,3>,4>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::vector<double>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::array<bool,3>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, bool );
    }
    {
        using arg_t = std::vector<bool>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, bool );
    }
    {
        using arg_t = std::vector<std::vector<bool>>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, bool );
    }
    {
        using arg_t = std::vector<std::vector<std::vector<double>>>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::vector<std::vector<std::vector<std::vector<double>>>>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::initializer_list<double>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
    {
        using arg_t = std::initializer_list<std::initializer_list<double>>;
        using result_t = meta::get_element_type_t<arg_t>;
        LOG_TYPEINFO(arg_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
}