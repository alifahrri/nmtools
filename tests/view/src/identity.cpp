#include "nmtools/array/identity.hpp"
#include "nmtools/testing/data/array/identity.hpp"
#include "nmtools/testing/doctest.hpp"

#define IDENTITY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, identity, case_name ); \
    using namespace args; \
    auto result = nmtools::view::identity(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("identity(case1)" * doctest::test_suite("view::identity"))
{
    IDENTITY_SUBCASE( case1, n );
}

TEST_CASE("identity(case2)" * doctest::test_suite("view::identity"))
{
    IDENTITY_SUBCASE( case2, n );
}

TEST_CASE("identity(case3)" * doctest::test_suite("view::identity"))
{
    IDENTITY_SUBCASE( case3, n, dtype );
}