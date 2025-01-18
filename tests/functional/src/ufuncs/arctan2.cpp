#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_BINARY_SUBCASE(subcase_name, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan2(case1)" * doctest::test_suite("functional::arctan2"))
{
    NMTOOLS_TESTING_USE_CASE(view, arctan2, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arctan2, a, b );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan2, a_a, b_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan2, a_f, b_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan2, a_h, b_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan2, a_d, b_d );

    CURRY_BINARY_SUBCASE( "case1", fn::arctan2, a, b );
    CURRY_BINARY_SUBCASE( "case1", fn::arctan2, a_a, b_a );
    CURRY_BINARY_SUBCASE( "case1", fn::arctan2, a_f, b_f );
    CURRY_BINARY_SUBCASE( "case1", fn::arctan2, a_h, b_h );
    CURRY_BINARY_SUBCASE( "case1", fn::arctan2, a_d, b_d );
}