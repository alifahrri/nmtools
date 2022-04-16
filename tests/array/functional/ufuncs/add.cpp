#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define ADD_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    auto result = function(left,right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_ADD_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    auto result = function(left)(right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_ADD_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function(left,right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONSTEXPR_CURRY_ADD_SUBCASE(subcase_name, function, left, right) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function(left)(right); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("functional::add"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,add,case1);
    using namespace args;

    ADD_SUBCASE("case1", fn::add, a,   b);
    ADD_SUBCASE("case1", fn::add, a_a, b_a);
    ADD_SUBCASE("case1", fn::add, a_f, b_f);
    ADD_SUBCASE("case1", fn::add, a_h, b_h);
    ADD_SUBCASE("case1", fn::add, a_d, b_d);

    CURRY_ADD_SUBCASE("case1", fn::add, a,   b);
    CURRY_ADD_SUBCASE("case1", fn::add, a_a, b_a);
    CURRY_ADD_SUBCASE("case1", fn::add, a_f, b_f);
    CURRY_ADD_SUBCASE("case1", fn::add, a_h, b_h);
    CURRY_ADD_SUBCASE("case1", fn::add, a_d, b_d);
}

TEST_CASE("add(case2)" * doctest::test_suite("functional::add"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,add,case2);
    using namespace args;

    ADD_SUBCASE("case2", fn::add, a,   b);
    ADD_SUBCASE("case2", fn::add, a_a, b);
    ADD_SUBCASE("case2", fn::add, a_f, b);
    ADD_SUBCASE("case2", fn::add, a_h, b);
    ADD_SUBCASE("case2", fn::add, a_d, b);

    CURRY_ADD_SUBCASE("case2", fn::add, a,   b);
    CURRY_ADD_SUBCASE("case2", fn::add, a_a, b);
    CURRY_ADD_SUBCASE("case2", fn::add, a_f, b);
    CURRY_ADD_SUBCASE("case2", fn::add, a_h, b);
    CURRY_ADD_SUBCASE("case2", fn::add, a_d, b);
}

TEST_CASE("add(case3)" * doctest::test_suite("functional::add"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,add,case3);
    using namespace args;

    ADD_SUBCASE("case3", fn::add, a, b);
    CURRY_ADD_SUBCASE("case3", fn::add, a, b);
}

TEST_CASE("add(case4)" * doctest::test_suite("functional::add"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,add,case4);
    using namespace args;

    ADD_SUBCASE("case4", fn::add, a,   b);
    ADD_SUBCASE("case4", fn::add, a_a, b);
    ADD_SUBCASE("case4", fn::add, a_f, b);
    ADD_SUBCASE("case4", fn::add, a_h, b);
    ADD_SUBCASE("case4", fn::add, a_d, b);

    CURRY_ADD_SUBCASE("case4", fn::add, a,   b);
    CURRY_ADD_SUBCASE("case4", fn::add, a_a, b);
    CURRY_ADD_SUBCASE("case4", fn::add, a_f, b);
    CURRY_ADD_SUBCASE("case4", fn::add, a_h, b);
    CURRY_ADD_SUBCASE("case4", fn::add, a_d, b);
}

TEST_CASE("constexpr_add(case1)" * doctest::test_suite("functional::add"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,constexpr_add,case1);
    using namespace args;

    CONSTEXPR_ADD_SUBCASE("case1", fn::add, a,   b);
    CONSTEXPR_ADD_SUBCASE("case1", fn::add, a_a, b_a);
    CONSTEXPR_ADD_SUBCASE("case1", fn::add, a_f, b_f);
    CONSTEXPR_ADD_SUBCASE("case1", fn::add, a_h, b_h);

    CONSTEXPR_CURRY_ADD_SUBCASE("case1", fn::add, a,   b);
    CONSTEXPR_CURRY_ADD_SUBCASE("case1", fn::add, a_a, b_a);
    CONSTEXPR_CURRY_ADD_SUBCASE("case1", fn::add, a_f, b_f);
    CONSTEXPR_CURRY_ADD_SUBCASE("case1", fn::add, a_h, b_h);
}