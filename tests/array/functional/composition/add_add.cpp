#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"

NMTOOLS_TESTING_DECLARE_CASE(functional, add_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {1,2,3};
        inline int c[1][1][1] = {{{4}}};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
        NMTOOLS_CAST_ARRAYS(c)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1][3][3] = {
            {
                { 5, 7, 9},
                { 8,10,12},
                {11,13,15},
            }
        };
    }
}

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace view = nm::view;
namespace meta = nm::meta;

#define FUNCTIONAL_SUBCASE(subcase_name, expect, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CURRY_TERNARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, a, b, c) \
SUBCASE(subcase_name) \
{ \
    auto result = function (a) (b) (b); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CONSTEXPR_FUNCTIONAL_SUBCASE(subcase_name, expect, function, ...) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CONSTEXPR_CURRY_TERNARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, a, b, c) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (a) (b) (c); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("add_flatten(case1)" * doctest::test_suite("functional::composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(functional,add_add,case1);
    using namespace args;
    using namespace expect;

    {
        auto f = fn::add * fn::add;
        static_assert( decltype(f)::arity == 3 );
        FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );

        CURRY_TERNARY_FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        CURRY_TERNARY_FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        CURRY_TERNARY_FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        CURRY_TERNARY_FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
        CURRY_TERNARY_FUNCTIONAL_SUBCASE( "case1", result, f, a, b, c );
    }
}