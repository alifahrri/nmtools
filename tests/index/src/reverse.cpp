#include "nmtools/index/reverse.hpp"
#include "nmtools/testing/data/index/reverse.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nm::literals;

#define CONSTEXPR_REVERSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_reverse, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::reverse(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define REVERSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reverse, case_name); \
    using namespace args; \
    auto result = nmtools::index::reverse(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define REVERSE_EXPECTED_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reverse, case_name); \
    using namespace args; \
    auto result = nmtools::index::reverse(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("reverse(case1)" * doctest::test_suite("index::reverse"))
{
    REVERSE_SUBCASE( case1, indices );
    REVERSE_SUBCASE( case1, indices_a );
    REVERSE_SUBCASE( case1, indices_f );
    REVERSE_SUBCASE( case1, indices_v );
    REVERSE_SUBCASE( case1, indices_h );

    REVERSE_SUBCASE( case1, indices_ct );
    REVERSE_SUBCASE( case1, indices_a );
    REVERSE_SUBCASE( case1, indices_f );
    REVERSE_SUBCASE( case1, indices_v );
    REVERSE_SUBCASE( case1, indices_h );

    REVERSE_SUBCASE( case1, indices_nl1 );

    REVERSE_EXPECTED_SUBCASE( case1, expected_nl2, indices_nl2 );
}

TEST_CASE("reverse(case2)" * doctest::test_suite("index::reverse"))
{
    REVERSE_SUBCASE( case2, indices );
    REVERSE_SUBCASE( case2, indices_a );
    REVERSE_SUBCASE( case2, indices_f );
    REVERSE_SUBCASE( case2, indices_v );
    REVERSE_SUBCASE( case2, indices_h );

    REVERSE_SUBCASE( case2, indices_ct );
    REVERSE_SUBCASE( case2, indices_a );
    REVERSE_SUBCASE( case2, indices_f );
    REVERSE_SUBCASE( case2, indices_v );
    REVERSE_SUBCASE( case2, indices_h );

    REVERSE_EXPECTED_SUBCASE( case2, expected_nl1, indices_nl1 );
    REVERSE_EXPECTED_SUBCASE( case2, expected_nl2, indices_nl2 );

    REVERSE_SUBCASE( case2, indices_mx1 );
    REVERSE_SUBCASE( case2, indices_mx2 );
}

TEST_CASE("reverse(case3)" * doctest::test_suite("index::reverse"))
{
    REVERSE_SUBCASE( case3, indices );
    REVERSE_SUBCASE( case3, indices_a );
    REVERSE_SUBCASE( case3, indices_f );
    REVERSE_SUBCASE( case3, indices_v );
    REVERSE_SUBCASE( case3, indices_h );

    REVERSE_SUBCASE( case3, indices_ct );
    REVERSE_SUBCASE( case3, indices_a );
    REVERSE_SUBCASE( case3, indices_f );
    REVERSE_SUBCASE( case3, indices_v );
    REVERSE_SUBCASE( case3, indices_h );

    REVERSE_EXPECTED_SUBCASE( case3, expected_nl1, indices_nl1 );
    REVERSE_EXPECTED_SUBCASE( case3, expected_nl2, indices_nl2 );
    REVERSE_EXPECTED_SUBCASE( case3, expected_nl3, indices_nl3 );

    REVERSE_SUBCASE( case3, indices_mx1 );
    REVERSE_SUBCASE( case3, indices_mx2 );
    REVERSE_SUBCASE( case3, indices_mx3 );
}

TEST_CASE("reverse(case1)" * doctest::test_suite("index::constexpr_reverse"))
{
    CONSTEXPR_REVERSE_SUBCASE( case1, indices );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_h );

    CONSTEXPR_REVERSE_SUBCASE( case1, indices_ct );

    CONSTEXPR_REVERSE_SUBCASE( case1, indices );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case1, indices_h );
}

TEST_CASE("reverse(case2)" * doctest::test_suite("index::constexpr_reverse"))
{
    CONSTEXPR_REVERSE_SUBCASE( case2, indices );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_h );

    CONSTEXPR_REVERSE_SUBCASE( case2, indices_ct );

    CONSTEXPR_REVERSE_SUBCASE( case2, indices );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case2, indices_h );
}

TEST_CASE("reverse(case3)" * doctest::test_suite("index::constexpr_reverse"))
{
    CONSTEXPR_REVERSE_SUBCASE( case3, indices );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_h );

    CONSTEXPR_REVERSE_SUBCASE( case3, indices_ct );

    CONSTEXPR_REVERSE_SUBCASE( case3, indices );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_a );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_f );
    CONSTEXPR_REVERSE_SUBCASE( case3, indices_h );
}