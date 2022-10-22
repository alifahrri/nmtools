#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/constants.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

TEST_CASE("clipped_integer(case1)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint8_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type value;
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
}

TEST_CASE("clipped_integer(case2)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint8_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type value{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
}

TEST_CASE("clipped_integer(case3)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint8_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type value = type{};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
}

TEST_CASE("clipped_integer(case4)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint8_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type value = 5;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
}

TEST_CASE("clipped_integer(case5)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3,1>;
        type value{0};
        NMTOOLS_ASSERT_EQUAL( value, 1 );
    }
    {
        using type = nm::clipped_uint8_t<3,1>;
        type value{0};
        NMTOOLS_ASSERT_EQUAL( value, 1 );
    }
    {
        using type = nm::clipped_uint16_t<3,1>;
        type value{0};
        NMTOOLS_ASSERT_EQUAL( value, 1 );
    }
    {
        using type = nm::clipped_uint32_t<3,1>;
        type value{0};
        NMTOOLS_ASSERT_EQUAL( value, 1 );
    }
    {
        using type = nm::clipped_uint64_t<3,1>;
        type value{0};
        NMTOOLS_ASSERT_EQUAL( value, 1 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type value{-1};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type value{-1};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type value{-1};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type value{-1};
        NMTOOLS_ASSERT_EQUAL( value, 0 );
    }
}

TEST_CASE("clipped_integer(case6)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3>;
        using other_t = nm::clipped_size_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint8_t<3>;
        using other_t = nm::clipped_uint8_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        using other_t = nm::clipped_uint16_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        using other_t = nm::clipped_uint32_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        using other_t = nm::clipped_uint64_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        using other_t = nm::clipped_int8_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        using other_t = nm::clipped_int16_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        using other_t = nm::clipped_int32_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        using other_t = nm::clipped_int64_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
}

TEST_CASE("clipped_integer(case7)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_uint8_t<3>;
        using other_t = nm::clipped_int8_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3>;
        using other_t = nm::clipped_int16_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3>;
        using other_t = nm::clipped_int32_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3>;
        using other_t = nm::clipped_int64_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        using other_t = nm::clipped_uint8_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        using other_t = nm::clipped_uint16_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        using other_t = nm::clipped_uint32_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        using other_t = nm::clipped_uint64_t<7,5>;
        type value;
        value = other_t{};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
}

using namespace nm::literals;

TEST_CASE("clipped_integer(case8)" * doctest::test_suite("misc"))
{
    {
        auto value = "3:[3]"_ct;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        auto value = "3:[1,3]"_ct;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        auto value = "3:[0,2]"_ct;
        NMTOOLS_ASSERT_EQUAL( value, 2 );
    }
    {
        auto value = "3:[4,5]"_ct;
        NMTOOLS_ASSERT_EQUAL( value, 4 );
    }
}

TEST_CASE("clipped_integer(case9)" * doctest::test_suite("misc"))
{
    {
        constexpr auto value = "3:[3]"_ct;
        NMTOOLS_STATIC_ASSERT_EQUAL( value, 3 );
    }
    {
        constexpr auto value = "3:[1,3]"_ct;
        NMTOOLS_STATIC_ASSERT_EQUAL( value, 3 );
    }
    {
        constexpr auto value = "3:[0,2]"_ct;
        NMTOOLS_STATIC_ASSERT_EQUAL( value, 2 );
    }
    {
        constexpr auto value = "3:[4,5]"_ct;
        NMTOOLS_STATIC_ASSERT_EQUAL( value, 4 );
    }
}

// addition with integer results in non-clipped

TEST_CASE("clipped_integer(case10)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3,1>;
        type init{0};
        auto value = init + 2;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint8_t<3,1>;
        type init{0};
        auto value = init + 2;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3,1>;
        type init{0};
        auto value = init + 2;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3,1>;
        type init{0};
        auto value = init + 2;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3,1>;
        type init{0};
        auto value = init + 2;
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type init{-1};
        auto value = init + 5;
        NMTOOLS_ASSERT_EQUAL( value, 5 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type init{-1};
        auto value = init + 5;
        NMTOOLS_ASSERT_EQUAL( value, 5 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type init{-1};
        auto value = init + 5;
        NMTOOLS_ASSERT_EQUAL( value, 5 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type init{-1};
        auto value = init + 5;
        NMTOOLS_ASSERT_EQUAL( value, 5 );
    }
}

TEST_CASE("clipped_integer(case11)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3,1>;
        type init{0};
        auto value = init + type{2};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint8_t<3,1>;
        type init{0};
        auto value = init + type{2};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint16_t<3,1>;
        type init{0};
        auto value = init + type{2};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint32_t<3,1>;
        type init{0};
        auto value = init + type{2};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_uint64_t<3,1>;
        type init{0};
        auto value = init + type{2};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type init{-1};
        auto value = init + type{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type init{-1};
        auto value = init + type{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type init{-1};
        auto value = init + type{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type init{-1};
        auto value = init + type{5};
        NMTOOLS_ASSERT_EQUAL( value, 3 );
    }
}

TEST_CASE("clipped_integer(case12)" * doctest::test_suite("misc"))
{
    {
        using type = nm::clipped_size_t<3,1>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_uint8_t<3,1>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_uint16_t<3,1>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_uint32_t<3,1>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_uint64_t<3,1>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_int8_t<3>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_int16_t<3>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_int32_t<3>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
    {
        using type = nm::clipped_int64_t<3>;
        type init{3};
        auto value = init + type{3};
        NMTOOLS_ASSERT_EQUAL( value, 6 );
    }
}