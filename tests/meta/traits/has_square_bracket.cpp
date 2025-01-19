/**
 * @file has_square_bracket.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

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

namespace meta = nmtools::meta;

TEST_CASE("has_square_bracket_v" * doctest::test_suite("traits"))
{
    {
        using arg_t = double;
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(!result);
    }
    {
        using arg_t = double[1];
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
    {
        using arg_t = double[1][2][3];
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
    {
        using arg_t = std::vector<double>;
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
    {
        using arg_t = std::vector<std::vector<double>>;
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
    {
        using arg_t = std::array<double,3>;
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
    {
        using arg_t = std::array<std::array<double,1>,3>;
        constexpr auto result = meta::has_square_bracket_v<arg_t,size_t>;
        STATIC_CHECK(result);
    }
}