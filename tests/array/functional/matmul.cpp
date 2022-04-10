#include "nmtools/array/functional/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define MATMUL_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    auto result = function(left,right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_MATMUL_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    auto result = function(left)(right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_MATMUL_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function(left,right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_CURRY_MATMUL_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function(left)(right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case1);
    using namespace args;

    MATMUL_SUBCASE("case1", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case1", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case1", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case1", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case1", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case1", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case1", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case1", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case1", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case1", fn::matmul, lhs_d, rhs_d);
}

TEST_CASE("matmul(case2)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case2);
    using namespace args;

    MATMUL_SUBCASE("case2", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case2", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case2", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case2", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case2", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case2", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case2", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case2", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case2", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case2", fn::matmul, lhs_d, rhs_d);
}

TEST_CASE("matmul(case3)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case3);
    using namespace args;

    MATMUL_SUBCASE("case3", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case3", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case3", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case3", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case3", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case3", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case3", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case3", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case3", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case3", fn::matmul, lhs_d, rhs_d);
}

TEST_CASE("matmul(case4)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case4);
    using namespace args;

    MATMUL_SUBCASE("case4", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case4", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case4", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case4", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case4", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case4", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case4", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case4", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case4", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case4", fn::matmul, lhs_d, rhs_d);
}

TEST_CASE("matmul(case5)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case5);
    using namespace args;

    MATMUL_SUBCASE("case5", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case5", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case5", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case5", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case5", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case5", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case5", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case5", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case5", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case5", fn::matmul, lhs_d, rhs_d);
}

TEST_CASE("matmul(case6)" * doctest::test_suite("functional::matmul"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,matmul,case6);
    using namespace args;

    MATMUL_SUBCASE("case6", fn::matmul, lhs, rhs);
    MATMUL_SUBCASE("case6", fn::matmul, lhs_a, rhs_a);
    MATMUL_SUBCASE("case6", fn::matmul, lhs_f, rhs_f);
    MATMUL_SUBCASE("case6", fn::matmul, lhs_h, rhs_h);
    MATMUL_SUBCASE("case6", fn::matmul, lhs_d, rhs_d);

    CURRY_MATMUL_SUBCASE("case6", fn::matmul, lhs, rhs);
    CURRY_MATMUL_SUBCASE("case6", fn::matmul, lhs_a, rhs_a);
    CURRY_MATMUL_SUBCASE("case6", fn::matmul, lhs_f, rhs_f);
    CURRY_MATMUL_SUBCASE("case6", fn::matmul, lhs_h, rhs_h);
    CURRY_MATMUL_SUBCASE("case6", fn::matmul, lhs_d, rhs_d);
}