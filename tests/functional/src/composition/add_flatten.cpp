#include "nmtools/array/functional/matmul.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/functional/flatten.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/view/full.hpp"
#include "nmtools/array/array/flatten.hpp"

#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

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

#define CURRY_BINARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
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

#define CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

NMTOOLS_TESTING_DECLARE_CASE(functional, add_flatten)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int rhs = 1;
        NMTOOLS_CAST_ARRAYS(lhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[9] = {1,2,3,4,5,6,7,8,9};
    }
}

TEST_CASE("add_flatten(case1)" * doctest::test_suite("functional::composition"))
{
    NMTOOLS_TESTING_USE_CASE(functional,add_flatten,case1);
    using namespace args;
    using namespace expect;

    {
        auto f = fn::add * fn::flatten;
        static_assert( decltype(f)::arity == 2 );
        FUNCTIONAL_SUBCASE( "case1", result, f, lhs, rhs );
        FUNCTIONAL_SUBCASE( "case1", result, f, lhs_a, rhs );
        FUNCTIONAL_SUBCASE( "case1", result, f, lhs_f, rhs );
        FUNCTIONAL_SUBCASE( "case1", result, f, lhs_h, rhs );
        FUNCTIONAL_SUBCASE( "case1", result, f, lhs_d, rhs );

        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", result, f, lhs, rhs );
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", result, f, lhs_a, rhs );
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", result, f, lhs_f, rhs );
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", result, f, lhs_h, rhs );
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", result, f, lhs_d, rhs );
    }
    {
        FUNCTIONAL_SUBCASE( "case1", result, (fn::add (fn::flatten (lhs))), rhs );
        FUNCTIONAL_SUBCASE( "case1", result, (fn::add (fn::flatten (lhs_a))), rhs );
        FUNCTIONAL_SUBCASE( "case1", result, (fn::add (fn::flatten (lhs_f))), rhs );
        FUNCTIONAL_SUBCASE( "case1", result, (fn::add (fn::flatten (lhs_h))), rhs );
        FUNCTIONAL_SUBCASE( "case1", result, (fn::add (fn::flatten (lhs_d))), rhs );
    }
}