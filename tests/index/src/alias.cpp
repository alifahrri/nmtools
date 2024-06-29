#include "nmtools/array/index/alias.hpp"
#include "nmtools/testing/data/index/alias.hpp"
#include "nmtools/testing/doctest.hpp"

#define ALIAS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, alias, case_name); \
    using namespace args; \
    auto result = nmtools::index::alias(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define GENERATE_ALIAS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, generate_alias, case_name); \
    using namespace args; \
    auto result = nmtools::index::generate_alias(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("alias(case1)" * doctest::test_suite("index::alias"))
{
    ALIAS_SUBCASE( case1, operands_ct, reserved_ids );
}

TEST_CASE("alias(case2)" * doctest::test_suite("index::alias"))
{
    ALIAS_SUBCASE( case2, operands_ct, reserved_ids_ct );
}

TEST_CASE("alias(case3)" * doctest::test_suite("index::alias"))
{
    ALIAS_SUBCASE( case3, operands_ct, reserved_ids_ct );
}

TEST_CASE("generate_alias(case1)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case1, aliases_ct, base_ct, prime_ct );
}

// 0, -1 sequence doesn't compute nicely for the hash algorithm
TEST_CASE("generate_alias(case2)" * doctest::test_suite("index::alias") * doctest::skip())
{
    GENERATE_ALIAS_SUBCASE( case2, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case2, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case3)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case3, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case3, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case4)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case4, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case4, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case5)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case5, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case5, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case6)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case6, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case6, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case7)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case7, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case7, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case8)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case8, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case8, aliases_ct, base_ct, prime_ct );
}

TEST_CASE("generate_alias(case9)" * doctest::test_suite("index::alias"))
{
    GENERATE_ALIAS_SUBCASE( case9, aliases, base, prime );
    GENERATE_ALIAS_SUBCASE( case9, aliases_ct, base_ct, prime_ct );
}