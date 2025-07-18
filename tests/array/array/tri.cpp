#include "nmtools/array/tri.hpp"
#include "nmtools/testing/data/array/tri.hpp"
#include "nmtools/testing/doctest.hpp"

#define EYE_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,tri,case_name); \
    using namespace args; \
    auto result = nmtools::tri(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tri(case1)" * doctest::test_suite("array::tri"))
{
    EYE_SUBCASE( case1, N );
}

TEST_CASE("tri(case2)" * doctest::test_suite("array::tri"))
{
    EYE_SUBCASE( case2, N, M );
}

TEST_CASE("tri(case3)" * doctest::test_suite("array::tri"))
{
    EYE_SUBCASE( case3, N, M );
}

TEST_CASE("tri(case4)" * doctest::test_suite("array::tri"))
{
    EYE_SUBCASE( case4, N, M, k );
}

TEST_CASE("tri(case5)" * doctest::test_suite("array::tri"))
{
    EYE_SUBCASE( case5, N, M, k, dtype );
}